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

#include "common/types.h"
#include "common/io.h"
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#pragma pack(push, 1)
struct PakHeader {
    char id[4]{};
    i32 dir_ofs{};
    i32 dir_len{};
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PakEntry {
    char name[56]{};
    i32 file_pos{};
    i32 file_len{};
};
#pragma pack(pop)

struct PakDirectory {
    std::vector<PakEntry> entries;
    std::unordered_map<std::string_view, i32> entry_map;

    PakDirectory(i32 num_entries)
        : entries(num_entries)
    {
        entry_map.reserve(num_entries);
    }
};

//
// A PAK file is Quake's container file format. It is a simple
// uncompressed archive format (collection of folders and files)
// which preserves file paths.
//
// Typically, a PAK file contains these kinds of files:
//   - *.wav: 16-bit RIFF WAVE audio files.
//   - *.bsp: Quake map files using Binary Space Partitioning (BSP).
//   - *.mdl: Alias models used to rendering 3D entities.
//   - *.spr: Sprite files (2D asset for in-game entities).
//   - *.dat: Compiled QuakeC bytecode (entity and game logic).
//   - *.rc:  Text files that contains only settings and definitions.
//   - *.cfg: Text files defining default key bindings and configuration.
//   - *.lmp: Lump files (palette, colormap, HUD/UI graphics, etc.).
//   - *.wad: WAD2 files (almost identical to DOOM's PWAD/IWAD format).
//
class PakFile {
  public:
    static ResultIO<PakFile> open(std::string&& path);
    ResultIO<File> openFile(std::string_view name);

  private:
    PakFile(std::string&& path, PakDirectory&& dir)
        : path{std::move(path)}
        , dir{std::move(dir)} {
    }
    const PakEntry* findEntry(std::string_view name);

    std::string path;
    PakDirectory dir;
};
