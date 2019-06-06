#pragma once

#include <ncurses.h>

#include "event.hpp"

namespace gamepad {

class UI {

public:
    UI() {
        initscr();
	    curs_set(0);
    }

    ~UI() {
        endwin();
    }

    void update(Event &event) {
        clear();

        mvprintw(0, 0, "Gamepad");
        mvprintw(1, 0, "=======");

        mvprintw(3, 0, "Axis");
        mvprintw(4, 0, "---------");
        for (unsigned int i = 0; i < event.getAxis().size(); i++) {
            mvprintw(i+5, 0, "%d", event.getAxis().at(i));
        }

        mvprintw(3, 20, "Buttons");
        mvprintw(4, 20, "-----------------------------");
        for (unsigned int j = 0; j < event.getButtons().size() / 2 + 1; j++) {
            mvprintw(j+5, 20, "%d: %s", j, event.getButtons().at(j) ? "true" : "false");
        }
        for (unsigned int j = event.getButtons().size() / 2 + 1; j < event.getButtons().size(); j++) {
            mvprintw(j+4-event.getButtons().size() / 2, 40, "%d: %s", j, event.getButtons().at(j) ? "true" : "false");
        }

        refresh();
    }

};

}
