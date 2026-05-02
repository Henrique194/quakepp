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

#include "fs/fs.h"
#include "common/assert.h"
#include "common/byte_swap.h"
#include "common/try.h"

ResultIO<QPic> FileSys::loadPicture(std::string_view name) {
    TRY(file, openFile(name));
    TRY(len, file.size());

    QPic pic{};
    auto num_pixels{len - 8};
    pic.pixels.resize(num_pixels);

    TRY(file.read(&pic.width, 4));
    TRY(file.read(&pic.height, 4));
    TRY(file.read(pic.pixels.data(), num_pixels));
    pic.width = Q_Swap32LE(pic.width);
    pic.height = Q_Swap32LE(pic.height);

#ifdef PARANOID
    // Check if the given dimension matches actual size.
    if (pic.width * pic.height != num_pixels) {
        PANIC("Lump picture has wrong dimension.");
    }
#endif

    return pic;
}
