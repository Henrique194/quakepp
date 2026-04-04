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

#include "render.h"

#define MAX_GLTEXTURES 1024

//
// OpenGL representation of the picture.
//
struct GLPic {
    // OpenGL texture ID.
    int texnum;
    // Texture start coordinates.
    float sl, tl;
    // Texture end coordinates.
    float sh, th;
};

//
// Global texture registry.
// It prevents loading the same texture twice.
//
struct GLTexture {
    int texnum;
    char identifier[64];
    int width;
    int height;
    bool mipmap;
};

class GLContext {
  public:
    explicit GLContext(SDL_Window* window);
    ~GLContext();

    void begin(u32 mode);
    void bindTexture(u32 target, u32 texture);
    void color4f(float red, float green, float blue, float alpha);
    void enable(u32 cap);
    void end();
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
    SDL_GLContext ctx{};
};

class GL1Renderer: public Renderer {
  public:
    static RendererResult create(SDL_Window* window);
    GL1Renderer(SDL_Window* window);
    ~GL1Renderer() override = default;

    void present() override;
    void setLogicalSize(u32 width, u32 height) override;
    void drawTransPic(u32 x, u32 y, QPic* pic) override;
    int loadPicTexture(QPic& pic) override;

  private:
    void drawPic(int x, int y, QPic* pic);

    //
    // Avoid binding an OpenGL texture twice.
    //
    void bindTexture(u32 tex);

    GLTexture* findTexture(const char* identifier, int width, int height);

    int loadTexture(
        const char* identifier,
        const QPic& pic,
        bool mipmap,
        bool alpha
    );

    void upload8(const QPic& pic, bool mipmap, bool alpha);
    void upload32(const u32* data, int width, int height, bool mipmap, bool alpha);

    SDL_Window* window{};
    GLContext gl;
    u32 current_tex{U32_MAX};
    GLTexture gltextures[MAX_GLTEXTURES]{};
    int numgltextures{0};

    float gl_picmip{0};
    float gl_max_size{1024};
    int gl_solid_format{3};
    int gl_alpha_format{4};
    int gl_filter_min;
    int gl_filter_max;
    int texture_extension_number{1};
};
