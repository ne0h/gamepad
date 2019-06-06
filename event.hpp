#pragma once

#include <vector>

namespace gamepad {

class Event {

private:
	std::vector<bool>  m_buttons;
	std::vector<int> m_axis;

public:
    Event() {

    }

	Event(const std::vector<bool> buttons, const std::vector<int> axis)
        : m_buttons(buttons), m_axis(axis) {

    }

	std::vector<bool> getButtons() {
        return m_buttons;
    }

	std::vector<int> getAxis() {
        return m_axis;
    }

    void setButtons(const std::vector<bool> buttons) {
        m_buttons = buttons;
    }

    void setAxis(const std::vector<int> axis) {
        m_axis = axis;
    }

};

}
