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
#include "common/assert.h"
#include "common/byte_swap.h"
#include "common/try.h"
#include "common/types.h"
#include "filesystem/filesystem.h"
#include "render/gl1.h"
#include "window/window.h"

std::unique_ptr<Menu> menu;

void Menu::init() {
    menu = std::make_unique<Menu>();
}

void Menu::shutdown() {
    menu = nullptr;
}


//
// max length of a quake game pathname
//
#define MAX_QPATH 64

struct CachePic {
    char name[MAX_QPATH];
    QPic pic;
    byte padding[32]; // for appended glpic
};

#define MAX_CACHED_PICS 128
static CachePic menu_cachepics[MAX_CACHED_PICS];
static int menu_numcachepics = 0;


static QPic* Draw_CachePic(const char* path) {
    for (int i = 0; i < menu_numcachepics; i++) {
        CachePic* pic = &menu_cachepics[i];
        if (!strcmp(path, pic->name)) {
            return &pic->pic;
        }
    }
    if (menu_numcachepics == MAX_CACHED_PICS) {
        PANIC("menu_numcachepics == MAX_CACHED_PICS");
    }
    CachePic* pic = &menu_cachepics[menu_numcachepics];
    pic->pic.data = std::vector<byte>(32);
    menu_numcachepics++;

    //
    // load the pic from disk
    //
    auto dat{file_sys->loadPicture(path)};
    if (!dat) {
        PANIC("Draw_CachePic: failed to load {}", path);
    }
    QPic qpic = std::move(*dat);

    strcpy(pic->name, path);
    pic->pic.width = qpic.width;
    pic->pic.height = qpic.height;

    GLPic* gl = (GLPic*) pic->pic.data.data();
    gl->texnum = window->loadPicTexture(qpic);
    gl->sl = 0;
    gl->sh = 1;
    gl->tl = 0;
    gl->th = 1;

    return &pic->pic;
}

void Menu::draw() {
    window->drawTransPic(16, 4, Draw_CachePic("gfx/qplaque.lmp"));
}
