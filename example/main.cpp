#include <iostream>

#include <gamepad.hpp>

void cb(const gamepad::Event &gamepadEvent) {
    std::cout << "called!" << std::endl;
}

int main() {
    gamepad::Gamepad gamepad;
    gamepad.addCallback(cb);
    std::cin.ignore();
    return 0;
}