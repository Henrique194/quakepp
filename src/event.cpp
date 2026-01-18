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

#include "event.h"

#define MAX_EVENTS 1024

EventSys::EventSys()
    : events(MAX_EVENTS)
{
    if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) {
        PANIC("Couldn't initialize event system: {}", SDL_GetError());
    }
}

EventSys::~EventSys() {
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

void EventSys::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        addEvent(&event);
    }
}

void EventSys::addEvent(const SDL_Event* event) {
    switch (event->type) {
        case SDL_QUIT:
            events[head] = Event::Quit;
            break;
        default:
            return;
    }
    head = (head + 1) % MAX_EVENTS;
}

Event EventSys::getEvent() {
    if (tail == head) {
        return Event::None;
    }
    Event ev{events[tail]};
    tail = (tail + 1) % MAX_EVENTS;
    return ev;
}