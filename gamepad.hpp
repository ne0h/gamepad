#pragma once

#include <exception>
#include <thread>
#include <mutex>

#include <SDL2/SDL.h>

#include "event.hpp"
#include "ui.hpp"

namespace gamepad {

class NoGamepadsFoundException : public std::exception {
    virtual const char* what() const throw() {
        return "failed to find any gamepad";
    }
};

using gamepadCallback = void(*)(const Event &gamepadEvent);

class Gamepad {

private:
    SDL_Joystick *m_gamepad;
    bool m_quit;
    UI m_ui;
    std::vector<gamepadCallback> m_callbacks;
    std::mutex m_mtx;

    void getEvent(Event &gamepadEvent);

    void updateLoop();

public:
    Gamepad();

    void addCallback(gamepadCallback cb) {
        m_mtx.lock();
        m_callbacks.push_back(cb);
        m_mtx.unlock();
    }
};

}
