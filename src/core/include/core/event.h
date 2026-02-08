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
#include <memory>
#include <vector>
#include <SDL.h>

enum class Event {
    None,
    Quit,
};

class EventSys {
  public:
    static void init();
    static void shutdown();
    EventSys();
    void pollEvents();
    Event getEvent();

  private:
    void addEvent(const SDL_Event* event);
    std::vector<Event> events;
    u32 head;
    u32 tail;
};

extern std::unique_ptr<EventSys> event_sys;
