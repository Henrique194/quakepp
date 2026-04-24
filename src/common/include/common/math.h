/*
 * Copyright (C) Henrique Barateli, <henriquejb194@gmail.com>, et al.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#pragma once

#include "common/assert.h"
#include <array>
#include <cmath>

template<size_t N>
requires(N > 0)
class Vec {
  public:
    Vec() = default;

    template<typename... Args, typename = std::enable_if_t<sizeof...(Args) == N>>
    Vec(Args... args)
        : data{static_cast<float>(args)...} {
    }

    float& x() {
        return data[0];
    }

    [[nodiscard]]
    float x() const {
        return data[0];
    }

    template<size_t M = N>
    requires(M > 1)
    float& y() {
        return data[1];
    }

    template<size_t M = N>
    requires(M > 1)
    [[nodiscard]]
    float y() const {
        return data[1];
    }

    template<size_t M = N>
    requires(M > 2)
    float& z() {
        return data[2];
    }

    template<size_t M = N>
    requires(M > 2)
    [[nodiscard]]
    float z() const {
        return data[2];
    }

    [[nodiscard]]
    float dot(const Vec& v) const {
        float result{0};
        for (size_t i = 0; i < N; ++i) {
            result += data[i] * v[i];
        }
        return result;
    }

    template<size_t M = N>
    requires(M == 2)
    float perp_dot(const Vec& v) const {
        return (x() * v.y()) - (y() * v.x());
    }

    template<size_t M = N>
    requires(M == 3)
    Vec cross(const Vec& v) const {
        float x_val{y() * v.z() - z() * v.y()};
        float y_val{z() * v.x() - x() * v.z()};
        float z_val{x() * v.y() - y() * v.x()};
        return Vec{x_val, y_val, z_val};
    }

    [[nodiscard]]
    float length() const {
        return std::sqrtf(length_squared());
    }

    [[nodiscard]]
    float length_squared() const {
        return dot(*this);
    }

    [[nodiscard]]
    Vec normalize() const {
        Vec normalized{(1.0f / length()) * *this};
        Q_DASSERT(normalized.is_finite());
        return normalized;
    }

    [[nodiscard]]
    Vec fast_renormalize() const {
        // Numerically approximate the inverse square
        // root by a Taylor series around 1.
        return *this * (0.5f * (3.0f - length_squared()));
    }

    [[nodiscard]]
    bool is_finite() const {
        for (size_t i = 0; i < N; ++i) {
            if (!std::isfinite(data[i])) {
                return false;
            }
        }
        return true;
    }

    float& operator[](size_t i) {
        Q_DASSERT(i < N);
        return data[i];
    }

    float operator[](size_t i) const {
        Q_DASSERT(i < N);
        return data[i];
    }

    Vec operator+(const Vec& v) const {
        Vec result{};
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] + v[i];
        }
        return result;
    }

    void operator+=(const Vec& v) {
        *this = *this + v;
    }

    Vec operator-(const Vec& v) const {
        return *this + (-v);
    }

    void operator-=(const Vec& v) {
        *this = *this - v;
    }

    Vec operator-() const {
        Vec result{};
        for (size_t i = 0; i < N; ++i) {
            result[i] = -data[i];
        }
        return result;
    }

    Vec operator*(float scale) const {
        Vec result{};
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] * scale;
        }
        return result;
    }

    friend Vec operator*(float scale, const Vec& v) {
        return v * scale;
    }

    void operator*=(float scale) {
        *this = *this * scale;
    }

  private:
    std::array<float, N> data;
};

using Vec2 = Vec<2>;
using Vec3 = Vec<3>;
