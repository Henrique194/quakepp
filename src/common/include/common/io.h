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

#include "assert.h"
#include "types.h"
#include <expected>
#include <string_view>
#include <SDL_rwops.h>

class File {
  public:
    // Seek from the beginning of data.
    static constexpr int SeekSet = RW_SEEK_SET;
    // Seek relative to current read point.
    static constexpr int SeekCur = RW_SEEK_CUR;
    // Seek relative to the end of data.
    static constexpr int SeekEnd = RW_SEEK_END;

    static std::expected<File, const char*> open(
        std::string_view path,
        std::string_view mode
    ) {
        File file{path, mode};
        if (!file.stream) {
            return std::unexpected{SDL_GetError()};
        }
        return file;
    }

    File(File&& other) noexcept
        : stream{other.stream}
    {
        other.stream = nullptr;
    }

    File(const File&) = delete;

    ~File() {
        if (stream) {
            SDL_RWclose(stream);
            stream = nullptr;
        }
    }

    std::expected<size_t, const char*> read(u8* buffer, size_t size) {
        Q_ASSERT(stream != nullptr);
        SDL_ClearError();
        size_t bytes_read{SDL_RWread(stream, buffer, 1, size)};
        if (const char* error{SDL_GetError()}; *error) {
            return std::unexpected{error};
        }
        return bytes_read;
    }

    std::expected<size_t, const char*> write(const u8* buffer, size_t size) {
        Q_ASSERT(stream != nullptr);
        SDL_ClearError();
        size_t bytes_written{SDL_RWwrite(stream, buffer, 1, size)};
        if (const char* error{SDL_GetError()}; *error) {
            return std::unexpected{error};
        }
        return bytes_written;
    }

    std::expected<i64, const char*> tell() {
        Q_ASSERT(stream != nullptr);
        SDL_ClearError();
        i64 pos{SDL_RWtell(stream)};
        if (pos < 0) {
            return std::unexpected{SDL_GetError()};
        }
        return pos;
    }

    std::expected<i64, const char*> seek(i64 offset, int whence) {
        Q_ASSERT(stream != nullptr);
        SDL_ClearError();
        i64 pos{SDL_RWseek(stream, offset, whence)};
        if (pos < 0) {
            return std::unexpected{SDL_GetError()};
        }
        return pos;
    }

    std::expected<i64, const char*> size() {
        Q_ASSERT(stream != nullptr);
        SDL_ClearError();
        i64 size{SDL_RWsize(stream)};
        if (size < 0) {
            return std::unexpected{SDL_GetError()};
        }
        return SDL_RWsize(stream);
    }

    File& operator=(const File&) = delete;

    File& operator=(File&& other) noexcept {
        if (stream) {
            SDL_RWclose(stream);
        }
        stream = other.stream;
        other.stream = nullptr;
        return *this;
    }

  private:
    File(std::string_view path, std::string_view mode)
        : stream{SDL_RWFromFile(path.data(), mode.data())} {
    }

    SDL_RWops* stream;
};
