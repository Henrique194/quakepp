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

#include "menu/menu.h"
#include "video/video.h"

void Menu::frame() {
    calcScale();
    draw();
}

void Menu::calcScale() {
    i32 i{video->getWidth() / 320};
    i32 j{video->getHeight() / 240};
    if (i > j) {
        i = j;
    }
    if (i < 1) {
        i = 1;
    }
    scale = (float) i;
}

void Menu::draw() {
    i32 w;
    i32 h;

    drawPic("qplaque", 16, 4);

    video->getPicSize("ttl_main", w, h);
    drawPic("ttl_main", (320 - w) / 2, 4);

    drawPic("mainmenu", 72, 32);

    drawPic("menudot1", 54, 32);
}

void Menu::drawPic(const char* name, i32 x, i32 y) {
    video->drawPic(name, x, y);
}
