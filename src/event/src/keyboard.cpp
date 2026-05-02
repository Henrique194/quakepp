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
#include <SDL_scancode.h>

static u8 mapKey(SDL_Scancode scancode) {
    switch (scancode) {
        default:
            return Key::Unknown;
        case SDL_SCANCODE_A:
            return Key::A;
        case SDL_SCANCODE_B:
            return Key::B;
        case SDL_SCANCODE_C:
            return Key::C;
        case SDL_SCANCODE_D:
            return Key::D;
        case SDL_SCANCODE_E:
            return Key::E;
        case SDL_SCANCODE_F:
            return Key::F;
        case SDL_SCANCODE_G:
            return Key::G;
        case SDL_SCANCODE_H:
            return Key::H;
        case SDL_SCANCODE_I:
            return Key::I;
        case SDL_SCANCODE_J:
            return Key::J;
        case SDL_SCANCODE_K:
            return Key::K;
        case SDL_SCANCODE_L:
            return Key::L;
        case SDL_SCANCODE_M:
            return Key::M;
        case SDL_SCANCODE_N:
            return Key::N;
        case SDL_SCANCODE_O:
            return Key::O;
        case SDL_SCANCODE_P:
            return Key::P;
        case SDL_SCANCODE_Q:
            return Key::Q;
        case SDL_SCANCODE_R:
            return Key::R;
        case SDL_SCANCODE_S:
            return Key::S;
        case SDL_SCANCODE_T:
            return Key::T;
        case SDL_SCANCODE_U:
            return Key::U;
        case SDL_SCANCODE_V:
            return Key::V;
        case SDL_SCANCODE_W:
            return Key::W;
        case SDL_SCANCODE_X:
            return Key::X;
        case SDL_SCANCODE_Y:
            return Key::Y;
        case SDL_SCANCODE_Z:
            return Key::Z;
        case SDL_SCANCODE_1:
            return Key::One;
        case SDL_SCANCODE_2:
            return Key::Two;
        case SDL_SCANCODE_3:
            return Key::Three;
        case SDL_SCANCODE_4:
            return Key::Four;
        case SDL_SCANCODE_5:
            return Key::Five;
        case SDL_SCANCODE_6:
            return Key::Six;
        case SDL_SCANCODE_7:
            return Key::Seven;
        case SDL_SCANCODE_8:
            return Key::Eight;
        case SDL_SCANCODE_9:
            return Key::Nine;
        case SDL_SCANCODE_0:
            return Key::Zero;
        case SDL_SCANCODE_RETURN:
            return Key::Enter;
        case SDL_SCANCODE_ESCAPE:
            return Key::Escape;
        case SDL_SCANCODE_BACKSPACE:
            return Key::Backspace;
        case SDL_SCANCODE_TAB:
            return Key::Tab;
        case SDL_SCANCODE_SPACE:
            return Key::Space;
        case SDL_SCANCODE_MINUS:
            return Key::Minus;
        case SDL_SCANCODE_EQUALS:
            return Key::Equals;
        case SDL_SCANCODE_LEFTBRACKET:
            return Key::LeftBracket;
        case SDL_SCANCODE_RIGHTBRACKET:
            return Key::RightBracket;
        case SDL_SCANCODE_BACKSLASH:
            return Key::Backslash;
        case SDL_SCANCODE_SEMICOLON:
            return Key::Semicolon;
        case SDL_SCANCODE_APOSTROPHE:
            return Key::Apostrophe;
        case SDL_SCANCODE_GRAVE:
            return Key::Grave;
        case SDL_SCANCODE_COMMA:
            return Key::Comma;
        case SDL_SCANCODE_PERIOD:
            return Key::Period;
        case SDL_SCANCODE_SLASH:
            return Key::Slash;
        case SDL_SCANCODE_F1:
            return Key::F1;
        case SDL_SCANCODE_F2:
            return Key::F2;
        case SDL_SCANCODE_F3:
            return Key::F3;
        case SDL_SCANCODE_F4:
            return Key::F4;
        case SDL_SCANCODE_F5:
            return Key::F5;
        case SDL_SCANCODE_F6:
            return Key::F6;
        case SDL_SCANCODE_F7:
            return Key::F7;
        case SDL_SCANCODE_F8:
            return Key::F8;
        case SDL_SCANCODE_F9:
            return Key::F9;
        case SDL_SCANCODE_F10:
            return Key::F10;
        case SDL_SCANCODE_F11:
            return Key::F11;
        case SDL_SCANCODE_F12:
            return Key::F12;
        case SDL_SCANCODE_PAUSE:
            return Key::Pause;
        case SDL_SCANCODE_INSERT:
            return Key::Ins;
        case SDL_SCANCODE_HOME:
            return Key::Home;
        case SDL_SCANCODE_PAGEUP:
            return Key::PageUp;
        case SDL_SCANCODE_DELETE:
            return Key::Del;
        case SDL_SCANCODE_END:
            return Key::End;
        case SDL_SCANCODE_PAGEDOWN:
            return Key::PageDown;
        case SDL_SCANCODE_RIGHT:
            return Key::RightArrow;
        case SDL_SCANCODE_LEFT:
            return Key::LeftArrow;
        case SDL_SCANCODE_DOWN:
            return Key::DownArrow;
        case SDL_SCANCODE_UP:
            return Key::UpArrow;
        case SDL_SCANCODE_KP_DIVIDE:
            return Key::Slash;
        case SDL_SCANCODE_KP_MULTIPLY:
            return Key::Asterisk;
        case SDL_SCANCODE_KP_MINUS:
            return Key::Minus;
        case SDL_SCANCODE_KP_PLUS:
            return Key::Plus;
        case SDL_SCANCODE_KP_ENTER:
            return Key::Enter;
        case SDL_SCANCODE_KP_2:
            return Key::DownArrow;
        case SDL_SCANCODE_KP_3:
            return Key::PageDown;
        case SDL_SCANCODE_KP_4:
            return Key::LeftArrow;
        case SDL_SCANCODE_KP_5:
            return Key::Five;
        case SDL_SCANCODE_KP_6:
            return Key::RightArrow;
        case SDL_SCANCODE_KP_8:
            return Key::UpArrow;
        case SDL_SCANCODE_KP_PERIOD:
            return Key::Del;
        case SDL_SCANCODE_LCTRL:
            return Key::Ctrl;
        case SDL_SCANCODE_LSHIFT:
            return Key::Shift;
        case SDL_SCANCODE_LALT:
            return Key::Alt;
        case SDL_SCANCODE_RCTRL:
            return Key::Ctrl;
        case SDL_SCANCODE_RSHIFT:
            return Key::Shift;
        case SDL_SCANCODE_RALT:
            return Key::Alt;
    }
}

void EventSys::queueKeyboardEvent(SDL_KeyboardEvent& ev) {
    u32 time{ev.timestamp};
    u8 key{mapKey(ev.keysym.scancode)};
    bool down{ev.state == SDL_PRESSED};
    queueEvent(KeyEvent{time, key, down});
}
