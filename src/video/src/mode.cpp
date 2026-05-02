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

#include "video/video.h"
#include <SDL_video.h>

static constexpr i32 LOGICAL_WIDTH = 320;
static constexpr i32 LOGICAL_HEIGHT = 240;

i32 Video::getWidth() const {
    return width;
}

i32 Video::getHeight() const {
    return height;
}

void Video::setMode(i32 mode) {
    int w;
    int h;
    SDL_GetWindowSizeInPixels(window, &w, &h);
    width = (i32) w;
    height = (i32) h;
    enableAspectCorrection();
}

void Video::enableAspectCorrection() {
    renderer->setLogicalSize(LOGICAL_WIDTH, LOGICAL_HEIGHT);
}

void Video::disableAspectCorrection() {
    renderer->setLogicalSize(0, 0);
}
