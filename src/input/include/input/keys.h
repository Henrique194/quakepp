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

struct Key {
    enum {
        Unknown = 0,

        Tab = 9,
        Enter = 13,
        Escape = 27,
        Space = 32,

        Apostrophe = '\'',
        Asterisk = '*',
        Plus = '+',
        Comma = ',',
        Minus = '-',
        Period = '.',
        Slash = '/',
        Zero = '0',
        One = '1',
        Two = '2',
        Three = '3',
        Four = '4',
        Five = '5',
        Six = '6',
        Seven = '7',
        Eight = '8',
        Nine = '9',
        Semicolon = ';',
        Equals = '=',
        LeftBracket = '[',
        Backslash = '\\',
        RightBracket = ']',
        Grave = '`',

        A = 'a',
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Backspace = 127,
        UpArrow,
        DownArrow,
        LeftArrow,
        RightArrow,
        Alt,
        Ctrl,
        Shift,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        Ins,
        Del,
        PageDown,
        PageUp,
        Home,
        End,

        Mouse1 = 200,
        Mouse2,
        Mouse3,
        Mouse4,
        Mouse5,

        MouseWheelUp = 241,
        MouseWheelDown = 242,

        Pause = 255,

        MAX = 256,
    };
};
