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

#include "filesystem/filesystem.h"
#include "common/byte_swap.h"
#include "common/try.h"
#include <ranges>

//
// Game directory to look in by default.
//
static constexpr const char* default_dir = "./id1";

std::unique_ptr<FileSys> file_sys;

void FileSys::init() {
    file_sys = std::make_unique<FileSys>();
    file_sys->addGameDir(default_dir);
}

void FileSys::shutdown() {
    file_sys = nullptr;
}

void FileSys::addGameDir(std::string_view dir) {
    game_dir = dir;
    search_dirs.emplace_back(dir);
}

ResultIO<File> FileSys::openFile(std::string_view name) {
    // Use reverse order so most recent added
    // directory has higher priority.
    for (auto& dir : search_dirs | std::views::reverse) {
        if (auto file{dir.openFile(name)}) {
            return file;
        }
    }
    return std::unexpected{"Couldn't open file"};
}

ResultIO<QPic> FileSys::loadPicture(std::string_view name) {
    TRY(file, openFile(name));
    TRY(len, file.size());
    i32 width{0};
    i32 height{0};
    std::vector<byte> data(len - 8);
    TRY(file.read(&width, 4));
    TRY(file.read(&height, 4));
    TRY(file.read(data.data(), data.size()));
    return QPic{Q_Swap32LE(width), Q_Swap32LE(height), data};
}
