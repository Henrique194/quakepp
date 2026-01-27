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

#include <format>
#include <stdexcept>
#include <SDL_assert.h>

//
// Macro for signaling unrecoverable errors.
//
#define PANIC(fmt, ...)                                                        \
    throw std::runtime_error {                                                 \
        std::format("[{}] " fmt, SDL_FUNCTION __VA_OPT__(, ) __VA_ARGS__)      \
    }

#define Q_ASSERT(cond)                                                         \
    if (!(cond)) {                                                             \
        PANIC("assertion failed: " #cond);                                     \
    }

#ifdef PARANOID
#define Q_DEBUG_ASSERT Q_ASSERT
#else
#define Q_DEBUG_ASSERT(cond)
#endif
