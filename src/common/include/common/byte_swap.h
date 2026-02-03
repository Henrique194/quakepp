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

#include <SDL_endian.h>

//
// Byteswap functions.
//
#define Q_Swap16    SDL_Swap16
#define Q_Swap32    SDL_Swap32
#define Q_Swap64    SDL_Swap64
#define Q_SwapFloat SDL_SwapFloat

//
// Byteswap item from the specified endianness to the native endianness.
//
#define Q_Swap16LE    SDL_SwapLE16
#define Q_Swap32LE    SDL_SwapLE32
#define Q_Swap64LE    SDL_SwapLE64
#define Q_SwapFloatLE SDL_SwapFloatLE
#define Q_Swap16BE    SDL_SwapBE16
#define Q_Swap32BE    SDL_SwapBE32
#define Q_Swap64BE    SDL_SwapBE64
#define Q_SwapFloatBE SDL_SwapFloatBE
