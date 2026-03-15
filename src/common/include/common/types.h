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

#include <SDL_stdinc.h>

#define I8_MAX  SDL_MAX_SINT8
#define I16_MAX SDL_MAX_SINT16
#define I32_MAX SDL_MAX_SINT32
#define I64_MAX SDL_MAX_SINT64

#define U8_MAX  SDL_MAX_UINT8
#define U16_MAX SDL_MAX_UINT16
#define U32_MAX SDL_MAX_UINT32
#define U64_MAX SDL_MAX_UINT64

#define I8_MIN  SDL_MIN_SINT8
#define I16_MIN SDL_MIN_SINT16
#define I32_MIN SDL_MIN_SINT32
#define I64_MIN SDL_MIN_SINT64

#define U8_MIN  SDL_MIN_UINT8
#define U16_MIN SDL_MIN_UINT16
#define U32_MIN SDL_MIN_UINT32
#define U64_MIN SDL_MIN_UINT64

typedef Uint8 byte;

typedef Uint8 u8;
typedef Uint16 u16;
typedef Uint32 u32;
typedef Uint64 u64;

typedef Sint8 i8;
typedef Sint16 i16;
typedef Sint32 i32;
typedef Sint64 i64;
