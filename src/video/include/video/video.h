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

#include "common/ptr.h"
#include "common/types.h"
#include "renderer/renderer.h"
#include <SDL_video.h>

class Video {
  public:
    static void init();
    static void shutdown();

    Video();
    ~Video();

    void frame();

    i32 getWidth() const;
    i32 getHeight() const;
    void setMode(i32 mode);

    void drawPic(const char* name, i32 x, i32 y);
    void getPicSize(const char* name, i32& w, i32& h);

  private:
    void enableAspectCorrection();
    void disableAspectCorrection();

    SDL_Window* window;
    Box<Renderer> renderer;
    i32 width;
    i32 height;
};

extern Box<Video> video;
