#include "gamepad.hpp"

namespace gamepad {

Gamepad::Gamepad() : m_quit(false) {
	gamepad::NoGamepadsFoundException ex;

    SDL_Init(SDL_INIT_JOYSTICK);
    const int num_joysticks = SDL_NumJoysticks();
    if (num_joysticks < 1) {
		throw ex;
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
        throw ex;
    }

    SDL_JoystickEventState(SDL_ENABLE);
    SDL_JoystickEventState(SDL_QUERY);

    std::thread(&Gamepad::updateLoop, this).detach();
}

void Gamepad::getEvent(Event &gamepadEvent) {
    SDL_Event event;
    std::vector<bool> buttons;
    std::vector<int>  axis;

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

void Gamepad::updateLoop() {
    while (!m_quit) {
        gamepad::Event event;
        getEvent(event);
        m_ui.update(event);

        m_mtx.lock();
        for (auto it = m_callbacks.begin(); it != m_callbacks.end(); it++) {
            (*it)(event);
        }
        m_mtx.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

}
