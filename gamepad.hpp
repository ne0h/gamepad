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
} NoGamepadsFoundException;

class Gamepad {

private:
    SDL_Joystick *m_gamepad;
    bool m_quit;
    UI m_ui;

    void getEvent(Event &gamepadEvent) {
        SDL_Event event;
        std::vector<bool>  buttons;
        std::vector<int> axis;

        SDL_JoystickUpdate();
        
        // get keys
        for (int i = 0; i < SDL_JoystickNumButtons(m_gamepad); i++) {
            unsigned int n = SDL_JoystickGetButton(m_gamepad, i);
            buttons.push_back((n == 1) ? true : false);
        }
        
        // get axis
        for (int i = 0; i < SDL_JoystickNumAxes(m_gamepad); i++) {
            int a = SDL_JoystickGetAxis(m_gamepad, i);
            axis.push_back(a);
        }

        gamepadEvent.setButtons(buttons);
        gamepadEvent.setAxis(axis);
    }

    void updateLoop() {
        while (!m_quit) {
            gamepad::Event event;
            getEvent(event);
            m_ui.update(event);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

public:
    Gamepad() : m_quit(false) {
        SDL_Init(SDL_INIT_JOYSTICK);
        const int num_joysticks = SDL_NumJoysticks();
        if (num_joysticks < 1) {
            throw NoGamepadsFoundException;
        }

        // pick the first gamepad having more than two axis
        bool found = false;
        for (unsigned int i = 0; i < num_joysticks; i++) {
            m_gamepad = SDL_JoystickOpen(i);
            if (SDL_JoystickNumAxes(m_gamepad) > 2) {
                found = true;
                break;
            }
        }
        if (!found) {
            throw NoGamepadsFoundException;
        }

        SDL_JoystickEventState(SDL_ENABLE);
        SDL_JoystickEventState(SDL_QUERY);

        std::thread(&Gamepad::updateLoop, this).detach();
    }

};

}
