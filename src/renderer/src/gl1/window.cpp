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

#include "gl1.h"
#include "video/video.h"
#include <SDL_stdinc.h>

struct Viewport {
    i32 x;
    i32 y;
    i32 w;
    i32 h;
};

static Viewport getViewport(i32 width, i32 height) {
    float logical_w{(float) width};
    float logical_h{(float) height};
    i32 real_w{video->getWidth()};
    i32 real_h{video->getHeight()};
    float want_aspect{logical_w / logical_h};
    float real_aspect{(float) real_w / real_h};
    if (SDL_fabs(want_aspect - real_aspect) < 0.0001) {
        // Aspect ratios are the same.
        return Viewport{.x = 0, .y = 0, .w = real_w, .h = real_h};
    }
    if (want_aspect > real_aspect) {
        // Wider aspect ratio, so letterbox it.
        float scale{(float) real_w / logical_w};
        i32 h{(i32) SDL_floor(logical_h * scale)};
        i32 y{(real_h - h) / 2};
        return Viewport{.x = 0, .y = y, .w = real_w, .h = h};
    }
    // Narrower aspect ratio, so use side-bars.
    float scale = (float) real_h / logical_h;
    i32 w{(i32) SDL_floor(logical_w * scale)};
    i32 x{(real_w - w) / 2};
    return Viewport{.x = x, .y = 0, .w = w, .h = real_h};
}

void GL1Renderer::setLogicalSize(i32 w, i32 h) {
    Viewport viewport{getViewport(w, h)};
    gl.enable(GL_TEXTURE_2D);
    gl.matrixMode(GL_PROJECTION);
    gl.loadIdentity();
    gl.viewport(viewport.x, viewport.y, viewport.w, viewport.h);
    gl.ortho(0, 320, 200, 0, 0, 1);
    gl.matrixMode(GL_MODELVIEW);
}

void GL1Renderer::present() {
    SDL_GL_SwapWindow(window);
}
