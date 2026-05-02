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

#include "renderer/renderer.h"
#include "gl_ctx.h"
#include "common/types.h"
#include <vector>

inline constexpr u32 MAX_QPATH = 64;

enum class ImageType {
    Skin,
    Sprite,
    Wall,
    Pic,
    Sky,
};

struct Image {
    char name[MAX_QPATH];
    ImageType type;
    u32 reg_seq;
    i32 width;
    i32 height;
    u32 tex_num;
    float sl;
    float tl;
    float sh;
    float th;
};

class GL1Renderer: public Renderer {
  public:
    static RendererResult create(SDL_Window* window);

    GL1Renderer(SDL_Window* window, GLContext&& ctx);
    ~GL1Renderer() override = default;

    void present() override;
    void setLogicalSize(i32 w, i32 h) override;

    void drawPic(const char* name, i32 x, i32 y) override;
    void getPicSize(const char* name, i32& w, i32& h) override;

  private:
    void setGL2D();

    SDL_Window* window;
    GLContext gl;

  private:
    Image* findPic(const char* name);

    Image* findImage(const char* name, ImageType type);
    Image* loadImage(const char* name, ImageType type);
    void bindImage(Image* img);
    static bool hasMipMap(Image* img);

    u32 reg_seq{0};
    u32 current_tex{U32_MAX};
    std::vector<Image> images;

  private:
    void uploadImage(Image* img, byte* data);
    void uploadImage32bit(Image* img, u32* data);
    void getScaledSize(i32 w, i32 h, i32& scaled_w, i32& scaled_h) const;
    i32 getTexFormat(Image* img, const byte* data) const;
    void setTexFilter(bool mipmap);
    static void resampleTex(const u32* in, i32 in_w, i32 in_h, u32* out, i32 out_w, i32 out_h);
    void uploadTex(i32 level, i32 format, i32 w, i32 h, const void* data);
    void genMipMaps(i32 format, i32 w, i32 h, byte* data);
    static void genMipMap(i32 w, i32 h, byte* in);

    float gl_picmip{0};
    float gl_max_size{1024};
    i32 alpha_format{GL_RGBA};
    i32 solid_format{GL_RGB};
    i32 filter_min{GL_NEAREST};
    i32 filter_max{GL_NEAREST};
};
