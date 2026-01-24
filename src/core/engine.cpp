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

#include "core/engine.h"
#include "common/common.h"
#include "config.h"
#include <SDL.h>
#include <memory>

static std::unique_ptr<Engine> engine;

Engine::Engine(int argc, char* argv[])
    : cli{argc, argv} {
}

void Engine::init(int argc, char* argv[]) {
    engine = std::make_unique<Engine>(argc, argv);
}

void Engine::shutdown() {
    engine = nullptr;
    SDL_Quit();
}

void Engine::run(int argc, char* argv[]) {
    try {
        init(argc, argv);
        runLoop();
    } catch (std::exception& e) {
        handleError(e);
    }
    shutdown();
}

void Engine::runLoop() {
    while (engine->runFrame()) {
        SDL_Delay(16); // 60 FPS
    }
}

bool Engine::runFrame() {
    event.pollEvents();
    while (true) {
        Event ev{event.getEvent()};
        switch (ev) {
            case Event::None:
                return true;
            case Event::Quit:
                return false;
            default:
                break;
        }
    }
}

void Engine::handleError(const std::exception& e) {
    u32 flags{SDL_MESSAGEBOX_ERROR};
    const char* title{PACKAGE_STRING};
    const char* msg{e.what()};
    SDL_Window* window{nullptr};
    SDL_ShowSimpleMessageBox(flags, title, msg, window);
}
