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

#include "filesystem/search_dir.h"
#include <format>
#include <ranges>

SearchDir::SearchDir(std::string_view path)
    : path{path}
{
    for (u32 i = 0;; i++) {
        std::string pak_path{std::format("{}/pak{}.pak", path, i)};
        auto pak{PakFile::open(std::move(pak_path))};
        if (!pak) {
            break;
        }
        paks.push_back(std::move(*pak));
    }
}

ResultIO<File> SearchDir::openFile(std::string_view name) {
    // Search in PAK files first.
    // Also use reverse order so PAK files with
    // higher number have higher priority.
    for (auto& pak : paks | std::views::reverse) {
        if (auto file{pak.openFile(name)}) {
            return file;
        }
    }
    // Try searching it in the OS directory.
    std::string file_path{std::format("{}/{}", path, name)};
    return File::open(file_path, "rb");
}
