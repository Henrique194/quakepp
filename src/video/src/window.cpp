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
#include "common/assert.h"
#include "common/types.h"
#include "config.h"
#include <glad/glad.h>

static void setGLAttributes() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
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

static SDL_GLContext createGLContext(SDL_Window* window) {
    SDL_GLContext ctx{SDL_GL_CreateContext(window)};
    if (!ctx) {
        PANIC("Couldn't create GL context: {}", SDL_GetError());
    }
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        PANIC("Couldn't load GL functions");
    }
    return ctx;
}

Window::Window() {
    setGLAttributes();
    window = createWindow();
    ctx = createGLContext(window);
}

Window::~Window() {
    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(window);
    ctx = nullptr;
    window = nullptr;
}
