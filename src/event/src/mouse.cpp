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

#include "event/event.h"
#include "input/keys.h"
#include <SDL_mouse.h>

static u8 mapMouseButton(const u8 button) {
    switch (button) {
        case SDL_BUTTON_LEFT:
            return Key::Mouse1;
        case SDL_BUTTON_RIGHT:
            return Key::Mouse2;
        case SDL_BUTTON_MIDDLE:
            return Key::Mouse3;
        case SDL_BUTTON_X1:
            return Key::Mouse4;
        case SDL_BUTTON_X2:
            return Key::Mouse5;
        default:
            return Key::Unknown;
    }
}

void EventSys::queueMouseButtonEvent(SDL_MouseButtonEvent& ev) {
    u32 time{ev.timestamp};
    u8 key{mapMouseButton(ev.button)};
    bool down{ev.state == SDL_PRESSED};
    queueEvent(KeyEvent{time, key, down});
}

void EventSys::queueMouseMotionEvent(SDL_MouseMotionEvent& ev) {
    u32 time{ev.timestamp};
    i32 dx{ev.xrel};
    i32 dy{ev.yrel};
    queueEvent(MouseEvent{time, dx, dy});
}

void EventSys::queueMouseWheelEvent(SDL_MouseWheelEvent& ev) {
    if (ev.y == 0) {
        return;
    }
    u32 time{ev.timestamp};
    u8 key{};
    if (ev.y > 0) {
        key = Key::MouseWheelUp;
    } else {
        key = Key::MouseWheelDown;
    }
    // This emulates a button press.
    queueEvent(KeyEvent{time, key, true});
    queueEvent(KeyEvent{time, key, false});
}
