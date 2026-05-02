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

#pragma once

#include "common/types.h"

enum class EventType {
    None,
    Quit,
    Key,
    Mouse,
};

struct QuitEvent {
    EventType type{EventType::Quit};
    u32 time;

    QuitEvent(u32 time) : time{time} {}
};

struct KeyEvent {
    EventType type{EventType::Key};
    u32 time;
    u8 key;
    bool down;

    KeyEvent(u32 time, u8 key, bool down)
        : time{time}, key{key}, down{down} {}
};

struct MouseEvent {
    EventType type{EventType::Mouse};
    u32 time;
    i32 dx;
    i32 dy;

    MouseEvent(u32 time, i32 dx, i32 dy)
        : time{time}, dx{dx}, dy{dy} {}
};

union Event {
    EventType type;
    QuitEvent quit;
    KeyEvent key;
    MouseEvent mouse;

    Event(): type{EventType::None} {}
    Event(QuitEvent ev): quit{ev} {}
    Event(KeyEvent ev): key{ev} {}
    Event(MouseEvent ev): mouse{ev} {}
};
