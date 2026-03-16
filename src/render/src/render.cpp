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

#include "render/render.h"
#include "common/assert.h"
#include "window/window.h"
#include <glad/glad.h>

std::unique_ptr<Renderer> renderer;

void Renderer::setLogicalSize(u32 width, u32 height) {
    glClearColor(1, 0, 0, 0);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.666);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glShadeModel(GL_FLAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float scale = std::min(width / 320.0f, height / 240.0f);
    glOrtho(0, width / scale, height / scale, 0, -99999, 99999);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(1.0f, 1.2f, 1.0f);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}

void Renderer::init() {
    renderer = std::make_unique<Renderer>();
    renderer->setLogicalSize(window->getWidth(), window->getHeight());
}

void Renderer::shutdown() {
    renderer = nullptr;
}

void Renderer::drawTransPic(u32 x, u32 y, QPic* pic) {
    auto width{window->getWidth()};
    auto height{window->getHeight()};
    if ((x + pic->width) > width || (y + pic->height) > height) {
        PANIC("bad coordinates");
    }
    drawPic(x, y, pic);
}

void Renderer::drawPic(int x, int y, QPic* pic) {
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
