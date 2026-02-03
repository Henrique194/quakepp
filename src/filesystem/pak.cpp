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

#include "filesystem/pak.h"
#include "common/byte_swap.h"
#include "common/try.h"
#include <format>

static ResultIO<PakHeader> parseHeader(File& file) {
    PakHeader header{};
    TRY(file.read(&header, sizeof(header)));
    header.dir_ofs = Q_Swap32LE(header.dir_ofs);
    header.dir_len = Q_Swap32LE(header.dir_len);
    return header;
}

static ResultIO<PakDirectory> parseDirectory(
    File& file,
    const PakHeader& header
) {
    i32 size_entry(sizeof(PakEntry));
    i32 num_entries{header.dir_len / size_entry};
    PakDirectory dir{num_entries};

    TRY(file.seek(header.dir_ofs, File::SeekSet));
    TRY(file.read(&dir.entries[0], header.dir_len));

    for (i32 i = 0; i < num_entries; i++) {
        PakEntry& entry{dir.entries[i]};
        dir.entry_map.try_emplace(entry.name, i);
        entry.file_len = Q_Swap32LE(entry.file_len);
        entry.file_pos = Q_Swap32LE(entry.file_pos);
    }

    return dir;
}

ResultIO<PakFile> PakFile::open(std::string&& path) {
    TRY(file, File::open(path, "rb"));
    TRY(header, parseHeader(file));
    TRY(dir, parseDirectory(file, header));
    return PakFile{std::move(path), std::move(dir)};
}

ResultIO<File> PakFile::openFile(std::string_view name) {
    const PakEntry* entry{findEntry(name)};
    if (!entry) {
        return std::unexpected{"Couldn't find file in PAK"};
    }
    TRY(file, File::open(path, "rb"));
    TRY(file.seek(entry->file_pos, File::SeekSet));
    return file;
}

const PakEntry* PakFile::findEntry(std::string_view name) {
    auto it{dir.entry_map.find(name)};
    if (it == dir.entry_map.end()) {
        return nullptr;
    }
    return &dir.entries[it->second];
}
