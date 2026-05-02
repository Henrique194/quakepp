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
#include "common/assert.h"
#include <SDL_stdinc.h>

void GL1Renderer::drawPic(const char* name, i32 x, i32 y) {
    Image* img{findPic(name)};
    if (!img) {
        PANIC("Can't find pic \"{}\"", name);
    }
    bindImage(img);
    gl.begin(GL_QUADS);
    gl.texCoord2f(img->sl, img->tl);
    gl.vertex2f(x, y);
    gl.texCoord2f(img->sh, img->tl);
    gl.vertex2f(x + img->width, y);
    gl.texCoord2f(img->sh, img->th);
    gl.vertex2f(x + img->width, y + img->height);
    gl.texCoord2f(img->sl, img->th);
    gl.vertex2f(x, y + img->height);
    gl.end();
}

void GL1Renderer::getPicSize(const char* name, i32& w, i32& h) {
    Image* img{findPic(name)};
    if (!img) {
        w = -1;
        h = -1;
        return;
    }
    w = img->width;
    h = img->height;
}

Image* GL1Renderer::findPic(const char* name) {
    static char fullname[MAX_QPATH];
    SDL_snprintf(fullname, MAX_QPATH, "gfx/%s.lmp", name);
    return findImage(fullname, ImageType::Pic);
}
