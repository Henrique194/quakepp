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
#include <memory>

#define MAX_GLTEXTURES 1024

//
// Quake picture format (.lmp).
//
struct QPic {
    int width;
    int height;
    byte data[4]; // variably sized
};

//
// OpenGL representation of the picture.
//
struct GLPic {
    // OpenGL texture ID.
    int texnum;
    // Texture start coordinates.
    float sl, tl;
    // tTexture end coordinates.
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

class Renderer {
  public:
    static void init();
    static void shutdown();
    void drawTransPic(u32 x, u32 y, QPic* pic);
    int loadPicTexture(QPic* pic);

  private:
    void setLogicalSize(u32 width, u32 height);
    void drawPic(int x, int y, QPic* pic);

    //
    // Avoid binding an OpenGL texture twice.
    //
    void bindTexture(u32 tex);

    GLTexture* findTexture(const char* identifier, int width, int height);

    int loadTexture(
        const char* identifier,
        int width,
        int height,
        byte* data,
        bool mipmap,
        bool alpha
    );

    u32 current_tex{U32_MAX};
    GLTexture gltextures[MAX_GLTEXTURES]{};
    int numgltextures{0};
};

extern std::unique_ptr<Renderer> renderer;
