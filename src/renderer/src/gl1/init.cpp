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

RendererResult GL1Renderer::create(SDL_Window* window) {
    auto ctx{GLContext::create(window)};
    if (!ctx) {
        return std::unexpected{ctx.error()};
    }
    return make_box<GL1Renderer>(window, std::move(*ctx));
}

GL1Renderer::GL1Renderer(SDL_Window* window, GLContext&& ctx)
    : window{window}
    , gl{std::move(ctx)}
{
    setGL2D();
}

void GL1Renderer::setGL2D() {
    gl.enable(GL_ALPHA_TEST);
    gl.alphaFunc(GL_GREATER, 0.666f);
    gl.color4f(1, 1, 1, 1);
}
