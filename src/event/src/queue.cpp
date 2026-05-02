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

void EventSys::queueEvent(Event event) {
    head++;
    events[(head - 1) % MAX_EVENTS] = event;
}

Event EventSys::popEvent() {
    tail++;
    return events[(tail - 1) % MAX_EVENTS];
}

Event EventSys::getEvent() {
    if (tail != head) {
        return popEvent();
    }
    pollSysEvents();
    if (tail != head) {
        return popEvent();
    }
    return Event{};
}

void EventSys::pollSysEvents() {
    SDL_Event sys_ev;
    while (SDL_PollEvent(&sys_ev)) {
        queueSysEvent(sys_ev);
    }
}

void EventSys::queueSysEvent(SDL_Event& ev) {
    switch (ev.type) {
        case SDL_QUIT:
            queueEvent(QuitEvent{ev.quit.timestamp});
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            queueKeyboardEvent(ev.key);
            break;
        case SDL_MOUSEMOTION:
            queueMouseMotionEvent(ev.motion);
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            queueMouseButtonEvent(ev.button);
            break;
        case SDL_MOUSEWHEEL:
            queueMouseWheelEvent(ev.wheel);
            break;
        default:
            break;
    }
}
