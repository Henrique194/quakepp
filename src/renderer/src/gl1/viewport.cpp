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

#include "renderer/gl1.h"
#include "video/video.h"
#include <glad/glad.h>

void GL1Renderer::setLogicalSize(u32 width, u32 height) {
    int logical_w = (int) width;
    int logical_h = (int) height;
    int real_w = (int) video->getWidth();
    int real_h = (int) video->getHeight();
    float want_aspect = (float) logical_w / logical_h;
    float real_aspect = (float) real_w / real_h;
    SDL_Rect viewport{};
    if (SDL_fabs(want_aspect - real_aspect) < 0.0001) {
        // Aspect ratios are the same.
        viewport.w = real_w;
        viewport.h = real_h;
    } else if (want_aspect > real_aspect) {
        // Wider aspect ratio, so letterbox it.
        float scale = (float) real_w / logical_w;
        viewport.x = 0;
        viewport.w = real_w;
        viewport.h = (int) SDL_floor(logical_h * scale);
        viewport.y = (real_h - viewport.h) / 2;
    } else {
        // Narrower aspect ratio, so use side-bars.
        float scale = (float) real_h / logical_h;
        viewport.y = 0;
        viewport.h = real_h;
        viewport.w = (int) SDL_floor(logical_w * scale);
        viewport.x = (real_w - viewport.w) / 2;
    }
    gl.enable(GL_TEXTURE_2D);
    gl.matrixMode(GL_PROJECTION);
    gl.loadIdentity();
    gl.viewport(viewport.x, viewport.y, viewport.w, viewport.h);
    gl.ortho(0, 320, 200, 0, 0, 1);
    gl.matrixMode(GL_MODELVIEW);
}
