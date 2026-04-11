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
#include <glad/glad.h>

RendererResult GL1Renderer::create(SDL_Window* window) {
    return std::make_unique<GL1Renderer>(window);
}

GL1Renderer::GL1Renderer(SDL_Window* window)
    : window{window}
    , gl{window}
    , gl_filter_min{GL_NEAREST}
    , gl_filter_max{GL_NEAREST}{
}
