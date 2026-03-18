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

#include "window/window.h"
#include "common/assert.h"
#include "config.h"
#include <glad/glad.h>
#include <SDL.h>

std::unique_ptr<Window> window;

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
    SDL_Window* sdl_window{SDL_CreateWindow(title, x, y, w, h, flags)};
    if (!sdl_window) {
        PANIC("Couldn't create window: {}", SDL_GetError());
    }
    SDL_SetWindowMinimumSize(sdl_window, 320, 240);
    return sdl_window;
}

void Window::init() {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        PANIC("Couldn't initialize video system: {}", SDL_GetError());
    }
    window = std::make_unique<Window>();
    window->sdl_window = createWindow();
    auto renderer{GL1Renderer::create(window->sdl_window)};
    if (!renderer) {
        PANIC("Couldn't create renderer: {}", renderer.error());
    }
    window->renderer = std::move(*renderer);
    window->setLogicalSize(window->getWidth(), window->getHeight());
}

void Window::shutdown() {
    SDL_DestroyWindow(window->sdl_window);
    window = nullptr;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

u32 Window::getWidth() {
    return width;
}

u32 Window::getHeight() {
    return height;
}

void Window::update() {
    renderer->present();
}

void Window::setLogicalSize(u32 width, u32 height) {
    renderer->setLogicalSize(width, height);
}

void Window::drawTransPic(u32 x, u32 y, QPic* pic) {
    renderer->drawTransPic(x, y, pic);
}

int Window::loadPicTexture(QPic* pic) {
    return renderer->loadPicTexture(pic);
}
