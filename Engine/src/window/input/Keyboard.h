#ifndef CG_TP_ENGINE_SRC_WINDOW_INPUT_KEYBOARD_H_
#define CG_TP_ENGINE_SRC_WINDOW_INPUT_KEYBOARD_H_

namespace engine::window
{
    class Window;
}

namespace engine::window::input {
    class Keyboard {
    private:
        friend class ::engine::window::Window;

        static bool downKeys[512]; // Enough for all standard ASCII-keys

        Keyboard() = default;
    public:
        static void HandleKeyPress(int keyCode, int scanCode, int action, int mods);

        static bool isKeyDown(int keyCode);
        static bool isCtrlKeyDown();
        static bool isShiftKeyDown();
        static bool isAltKeyDown();
    };
}

#endif //CG_TP_ENGINE_SRC_WINDOW_INPUT_KEYBOARD_H_
