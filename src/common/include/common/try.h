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

#include "concat.h"
#include <expected>
#include <SDL_assert.h>

//
// Unwraps a std::expected<T, E> or propagates its error by
// returning std::unexpected<E> from the current function.
//
// This macro behaves similarly to Rust's '?' operator.
//
// Supported forms:
//
//   TRY(expr)
//     - Evaluates 'expr'.
//     - If it contains an error, returns it immediately.
//     - Otherwise, discards the value.
//
//     TRY(lhs, expr)
//       - Evaluates 'expr'.
//       - If it contains an error, returns it immediately.
//       - Otherwise, moves the contained value into 'lhs'.
//
// Notes:
//   - The enclosing function must return std::expected<..., E>.
//   - 'expr' is evaluated exactly once.
//
#define TRY(...)                                                               \
    GET_TRY_MACRO(__VA_ARGS__, TRY_ASSIGN, TRY_CHECK)(__VA_ARGS__)

//
// Selects the appropriate macro based on argument count.
//
#define GET_TRY_MACRO(_1, _2, NAME, ...) NAME

#define TRY_CHECK(failable)                                                    \
    {                                                                          \
        auto _result{(failable)};                                              \
        if (!_result) {                                                        \
            return std::unexpected{_result.error()};                           \
        }                                                                      \
    }

#define TRY_ASSIGN(lhs, failable)                                              \
    TRY_ASSIGN_INNER(CONCAT(_result, SDL_LINE), lhs, failable)

#define TRY_ASSIGN_INNER(_result, lhs, failable)                               \
    auto _result{(failable)};                                                  \
    if (!_result) {                                                            \
        return std::unexpected{_result.error()};                               \
    }                                                                          \
    auto lhs{std::move(*_result)}
