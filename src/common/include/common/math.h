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
#include <cmath>

struct Vec3 {
    float x{0};
    float y{0};
    float z{0};

    [[nodiscard]]
    float length() const {
        return sqrtf(length_squared());
    }

    [[nodiscard]]
    float length_squared() const {
        return this->dot(*this);
    }

    [[nodiscard]]
    float dot(const Vec3& v) const {
        return (x * v.x) + (y * v.y) + (z * v.z);
    }

    [[nodiscard]]
    Vec3 cross(const Vec3& v) const {
        return Vec3{y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    [[nodiscard]]
    Vec3 normalize() const {
        Vec3 normalized{(1.0f / length()) * *this};
        Q_DASSERT(normalized.is_finite());
        return normalized;
    }

    [[nodiscard]]
    Vec3 fast_renormalize() const {
        // Numerically approximate the inverse square
        // root by a Taylor series around 1.
        return *this * (0.5f * (3.0f - length_squared()));
    }

    [[nodiscard]]
    bool is_finite() const {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }

    Vec3 operator+(const Vec3& v) const {
        return Vec3{x + v.x, y + v.y, z + v.z};
    }

    void operator+=(const Vec3& v) {
        *this = *this + v;
    }

    Vec3 operator-(const Vec3& v) const {
        return *this + (-v);
    }

    void operator-=(const Vec3& v) {
        *this = *this - v;
    }

    Vec3 operator-() const {
        return Vec3{-x, -y, -z};
    }

    Vec3 operator*(float scale) const {
        return Vec3{x * scale, y * scale, z * scale};
    }

    friend Vec3 operator*(float scale, const Vec3& v) {
        return v * scale;
    }

    void operator*=(float scale) {
        *this = *this * scale;
    }
};

