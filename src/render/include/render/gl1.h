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

class GL1Renderer: public Renderer {
  public:
    static RendererResult create(SDL_Window* sdl_window);
    ~GL1Renderer() override;
    void present() override;
    void setLogicalSize(u32 width, u32 height) override;
    void drawTransPic(u32 x, u32 y, QPic* pic) override;
    int loadPicTexture(QPic* pic) override;

  private:
    void drawPic(int x, int y, QPic* pic);

    //
    // Avoid binding an OpenGL texture twice.
    //
    void bindTexture(u32 tex);

    GLTexture* findTexture(const char* identifier, int width, int height);

    int loadTexture(
        const char* identifier,
        const QPic* pic,
        bool mipmap,
        bool alpha
    );

    SDL_Window* sdl_window{};
    SDL_GLContext ctx{};
    u32 current_tex{U32_MAX};
    GLTexture gltextures[MAX_GLTEXTURES]{};
    int numgltextures{0};
};
