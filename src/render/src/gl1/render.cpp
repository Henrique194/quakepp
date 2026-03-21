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

#include "render/gl1.h"
#include "common/assert.h"
#include "window/window.h"
#include <glad/glad.h>

void GL1Renderer::present() {
    SDL_GL_SwapWindow(sdl_window);
}

void GL1Renderer::setLogicalSize(u32 width, u32 height) {
    int logical_w = (int) width;
    int logical_h = (int) height;
    int real_w = (int) window->getWidth();
    int real_h = (int) window->getHeight();
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
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(viewport.x, viewport.y, viewport.w, viewport.h);
    glOrtho(0, 320, 200, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}

void GL1Renderer::drawTransPic(u32 x, u32 y, QPic* pic) {
    auto width{window->getWidth()};
    auto height{window->getHeight()};
    if ((x + pic->width) > width || (y + pic->height) > height) {
        PANIC("bad coordinates");
    }
    drawPic(x, y, pic);
}

void GL1Renderer::drawPic(int x, int y, QPic* pic) {
    GLPic* gl = (GLPic*) pic->data;
    glColor4f(1, 1, 1, 1);
    bindTexture(gl->texnum);
    glBegin(GL_QUADS);
    glTexCoord2f(gl->sl, gl->tl);
    glVertex2f(x, y);
    glTexCoord2f(gl->sh, gl->tl);
    glVertex2f(x + pic->width, y);
    glTexCoord2f(gl->sh, gl->th);
    glVertex2f(x + pic->width, y + pic->height);
    glTexCoord2f(gl->sl, gl->th);
    glVertex2f(x, y + pic->height);
    glEnd();
}
