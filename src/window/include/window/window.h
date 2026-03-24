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
#include "render/render.h"
#include <memory>
#include <SDL_video.h>

class Window {
  public:
    static void init();
    static void shutdown();
    void update();
    u32 getWidth();
    u32 getHeight();

    void setLogicalSize(u32 width, u32 height);
    void drawTransPic(u32 x, u32 y, QPic* pic);
    int loadPicTexture(QPic& pic);

  private:
    SDL_Window* sdl_window{};
    std::unique_ptr<Renderer> renderer{};
    u32 width{3456};
    u32 height{2168};
};

extern std::unique_ptr<Window> window;
