#pragma once

#include <exception>
#include <thread>

#include <SDL2/SDL.h>

#include "event.hpp"
#include "ui.hpp"

namespace gamepad {

class NoGamepadsFoundException : public std::exception {
    virtual const char* what() const throw() {
        return "failed to find any gamepad";
    }
};

class Gamepad {

private:
    SDL_Joystick *m_gamepad;
    bool m_quit;
    UI m_ui;

    void getEvent(Event &gamepadEvent);

    void updateLoop();

public:
    Gamepad();
};

}
