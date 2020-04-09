#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Keyboard.h"

namespace engine::window::input {
    bool Keyboard::downKeys[512];

    void Keyboard::HandleKeyPress(int keyCode, int scanCode, int action, int mods) {
        Keyboard::downKeys[keyCode] = action != GLFW_RELEASE;
    }

    bool Keyboard::isKeyDown(int keyCode) {
        return Keyboard::downKeys[keyCode];
    }

    bool Keyboard::isCtrlKeyDown() {
        return isKeyDown(GLFW_KEY_LEFT_CONTROL) || isKeyDown(GLFW_KEY_RIGHT_CONTROL);
    }

    bool Keyboard::isShiftKeyDown() {
        return isKeyDown(GLFW_KEY_LEFT_SHIFT) || isKeyDown(GLFW_KEY_RIGHT_SHIFT);
    }

    bool Keyboard::isAltKeyDown() {
        return isKeyDown(GLFW_KEY_LEFT_ALT) || isKeyDown(GLFW_KEY_RIGHT_ALT);
    }
}
