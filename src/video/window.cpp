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

#include "video/window.h"
#include "common/common.h"
#include "config.h"

static SDL_Renderer* createRenderer(SDL_Window* window) {
    i32 index{-1};
    u32 flags{SDL_RENDERER_TARGETTEXTURE};
    SDL_Renderer* renderer{SDL_CreateRenderer(window, index, flags)};
    if (!renderer) {
        PANIC("Couldn't create window renderer: {}", SDL_GetError());
    }

    // Important: Set the "logical size" of the rendering context.
    // At the same time this also defines the aspect ratio that is
    // preserved while scaling and stretching the texture into the
    // window.
    SDL_RenderSetLogicalSize(renderer, 320, 240);

    // Blank out the full screen area in case there is any junk in
    // the borders that won't otherwise be overwritten.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return renderer;
}

static SDL_Window* createWindow() {
    const char* title{PACKAGE_STRING};
    i32 x{SDL_WINDOWPOS_CENTERED};
    i32 y{SDL_WINDOWPOS_CENTERED};
    i32 w{0};
    i32 h{0};
    u32 flags{SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN_DESKTOP};
    SDL_Window* window{SDL_CreateWindow(title, x, y, w, h, flags)};
    if (!window) {
        PANIC("Couldn't create window: {}", SDL_GetError());
    }
    SDL_SetWindowMinimumSize(window, 320, 240);
    return window;
}

Window::Window()
    : window{createWindow()}
    , renderer{createRenderer(window)} {
}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
}
