#ifndef SLEEK_KEYBOARD_H
#define SLEEK_KEYBOARD_H

namespace sleek
{
    namespace device
    {
        enum class KEYBOARD_LAYOUT
        {
            KBD_UNKNOWN,
            KBD_QWERTY,
            KBD_AZERTY,
            KBD_QWERTZ,
            KBD_DVORAK,
            KBD_COLEMAK,
            KBD_COUNT
        };
        
        static const char* KeyboardLayoutName[] = {
            "UNKNOWN",
            "QWERTY",
            "AZERTY",
            "QWERTZ",
            "DVORAK",
            "COLEMAK",
            "COUNT",
        };

        KEYBOARD_LAYOUT detectKeyboardLayout();
        void printKeyboardLayout(KEYBOARD_LAYOUT layout);
    }
}

#endif // SLEEK_KEYBOARD_H