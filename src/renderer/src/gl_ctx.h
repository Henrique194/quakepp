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
#include <expected>
#include <SDL_video.h>
#include <glad/glad.h>

class GLContext {
  public:
    static std::expected<GLContext, const char*> create(SDL_Window* window);

    GLContext() = default;
    GLContext(GLContext&& other);
    ~GLContext();

    void alphaFunc(u32 func, float ref);
    void begin(u32 mode);
    void bindTexture(u32 target, u32 texture);
    void color4f(float red, float green, float blue, float alpha);
    void enable(u32 cap);
    void end();
    void genTextures(i32 n, u32* textures);
    void loadIdentity();
    void matrixMode(u32 mode);
    void ortho(
        double left,
        double right,
        double bottom,
        double top,
        double zNear,
        double zFar
    );
    void texCoord2f(float s, float t);
    void texImage2D(
        u32 target,
        i32 level,
        i32 internal_format,
        i32 width,
        i32 height,
        i32 border,
        u32 format,
        u32 type,
        const void* pixels
    );
    void texParameterf(u32 target, u32 pname, float param);
    void vertex2f(float x, float y);
    void viewport(i32 x, i32 y, i32 width, i32 height);

  private:
    GLContext(SDL_GLContext ctx);

    SDL_GLContext ctx{nullptr};
};
