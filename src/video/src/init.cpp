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

#include "video/video.h"
#include "common/assert.h"
#include "config.h"
#include <SDL.h>

Box<Video> video;

void Video::init() {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        PANIC("Couldn't initialize video system: {}", SDL_GetError());
    }
    video = make_box<Video>();
    video->setMode(0);
}

void Video::shutdown() {
    video = nullptr;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

static SDL_Window* createWindow() {
    const char* title{PACKAGE_STRING};
    int x{SDL_WINDOWPOS_CENTERED};
    int y{SDL_WINDOWPOS_CENTERED};
    int w{0};
    int h{0};
    u32 flags{
        SDL_WINDOW_FULLSCREEN_DESKTOP
        | SDL_WINDOW_ALLOW_HIGHDPI
        | SDL_WINDOW_OPENGL
    };
    SDL_Window* window{SDL_CreateWindow(title, x, y, w, h, flags)};
    if (!window) {
        PANIC("Couldn't create window: {}", SDL_GetError());
    }
    SDL_SetWindowMinimumSize(window, 320, 240);
    return window;
}

static Box<Renderer> createRenderer(SDL_Window* window) {
    auto type{RenderType::GL1};
    auto result{Renderer::create(type, window)};
    if (!result) {
        PANIC("Couldn't create renderer: {}", result.error());
    }
    return std::move(*result);
}

Video::Video()
    : window{createWindow()}
    , renderer{createRenderer(window)}
    , width{0}
    , height{0} {
}

Video::~Video() {
    // We need to shut down renderer first,
    // because it depends on the SDL window.
    renderer = nullptr;
    SDL_DestroyWindow(window);
}
