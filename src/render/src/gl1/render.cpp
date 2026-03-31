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
#include "video/video.h"
#include <glad/glad.h>

void GL1Renderer::present() {
    SDL_GL_SwapWindow(window);
}

void GL1Renderer::drawTransPic(u32 x, u32 y, QPic* pic) {
    auto width{video->getWidth()};
    auto height{video->getHeight()};
    if ((x + pic->width) > width || (y + pic->height) > height) {
        PANIC("bad coordinates");
    }
    drawPic(x, y, pic);
}

void GL1Renderer::drawPic(int x, int y, QPic* pic) {
    const GLPic* gl_pic = (GLPic*) pic->data.data();
    bindTexture(gl_pic->texnum);
    gl.begin(GL_QUADS);
    gl.color4f(1, 1, 1, 1);
    gl.texCoord2f(gl_pic->sl, gl_pic->tl);
    gl.vertex2f(x, y);
    gl.texCoord2f(gl_pic->sh, gl_pic->tl);
    gl.vertex2f(x + pic->width, y);
    gl.texCoord2f(gl_pic->sh, gl_pic->th);
    gl.vertex2f(x + pic->width, y + pic->height);
    gl.texCoord2f(gl_pic->sl, gl_pic->th);
    gl.vertex2f(x, y + pic->height);
    gl.end();
}
