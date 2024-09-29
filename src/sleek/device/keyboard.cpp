#include "keyboard.h"
#include <iostream>
#include <unordered_map>

#if defined WIN32 || WIN64
#include <Windows.h>
#elif defined(__linux__)
#include <cstdio>
#include <string>
#endif

  
namespace sleek
{
    namespace device
    {
        #if defined WIN32 || WIN64
            std::unordered_map<HKL, KEYBOARD_LAYOUT> winLayoutMap = {
                {0x04090409, KEYBOARD_LAYOUT::KBD_QWERTY},   // English (United States)
                {0x08080809, KEYBOARD_LAYOUT::KBD_QWERTY},   // English (United Kingdom)
                {0x040c0c13, KEYBOARD_LAYOUT::KBD_AZERTY},   // French (France)
                {0x080c0c13, KEYBOARD_LAYOUT::KBD_AZERTY},   // French (Belgium)
                {0x04070c07, KEYBOARD_LAYOUT::KBD_QWERTZ},   // German (Germany)
                {0x00000409, KEYBOARD_LAYOUT::KBD_DVORAK},   // Dvorak (United States)
            };
        #elif defined __linux__ || __linux
            std::unordered_map<std::string, KEYBOARD_LAYOUT> linuxLayoutMap = {
                {"us", KEYBOARD_LAYOUT::KBD_QWERTY},
                {"gb", KEYBOARD_LAYOUT::KBD_QWERTY},
                {"fr", KEYBOARD_LAYOUT::KBD_AZERTY},
                {"be", KEYBOARD_LAYOUT::KBD_AZERTY},
                {"de", KEYBOARD_LAYOUT::KBD_QWERTZ},
                {"dvorak", KEYBOARD_LAYOUT::KBD_DVORAK},
                {"colemak", KEYBOARD_LAYOUT::KBD_COLEMAK},
                // Add more mappings as needed
            };
            std::unordered_map<std::string, KEYBOARD_LAYOUT> linuxAliasesMap = {
                {"qwerty", KEYBOARD_LAYOUT::KBD_QWERTY},
                {"azerty", KEYBOARD_LAYOUT::KBD_AZERTY},
                {"qwertz", KEYBOARD_LAYOUT::KBD_QWERTZ},
                {"dvorak", KEYBOARD_LAYOUT::KBD_DVORAK},
                {"colemak", KEYBOARD_LAYOUT::KBD_COLEMAK},
                // Add more mappings as needed
            };
        #endif
        
        #if defined WIN32 || WIN64
            KEYBOARD_LAYOUT detectKeyboardLayout()
            {
                HKL hkl = GetKeyboardLayout(0); // 0 for the current thread
                auto it = winLayoutMap.find(hkl);
                return it != winLayoutMap.end() ? it->second : KEYBOARD_LAYOUT::KBD_UNKNOWN;
            }
        #elif defined __linux__ || __linux
            std::string readXKBmap()
            {
                FILE* pipe = popen("setxkbmap -print", "r");
                
                if (!pipe)
                {
                    std::cerr << "popen readXKBmap() failed" << std::endl;
                    return "";
                } 
                    
                char buffer[128];
                std::string result = "";
                
                while (fgets(buffer, 128, pipe) != NULL)
                    result += buffer;
                    
                pclose(pipe);
                
                std::cerr << "readXKBmap() " << result << std::endl;
                
                return result;
            }
            
            KEYBOARD_LAYOUT getKeyboardAlias()
            {
                std::string result = readXKBmap();
              
                // Find the line containing the layout aliases
                size_t pos = result.find("aliases(");
                if (pos != std::string::npos)
                {
                    size_t endPos = result.find(")", pos);
                    if (endPos != std::string::npos)
                    {
                        std::string layoutName = result.substr(pos + 8, endPos - pos - 8); // Extract the layout name
                        layoutName.erase(layoutName.find_last_not_of(")") + 1); // Trim trailing whitespace
                        auto it = linuxAliasesMap.find(layoutName);
                        std::cerr << "getKeyboardAlias() " << layoutName << std::endl;
                        return it != linuxAliasesMap.end() ? it->second : KEYBOARD_LAYOUT::KBD_UNKNOWN;
                    }
                }
              
                return KEYBOARD_LAYOUT::KBD_UNKNOWN;
            }

            KEYBOARD_LAYOUT detectKeyboardLayout()
            {
                std::string result = readXKBmap();

                size_t pos = result.find("layout:");
                
                if (pos != std::string::npos)
                {
                    std::string layoutName = result.substr(pos + 7); // Skip "layout: "
                    layoutName.erase(layoutName.find_last_not_of(" \n\r\t") + 1); // Trim trailing whitespace
                    auto it = linuxLayoutMap.find(layoutName);
                    return it != linuxLayoutMap.end() ? it->second : KEYBOARD_LAYOUT::KBD_UNKNOWN;
                }

                return getKeyboardAlias();
            }
        #else
            KEYBOARD_LAYOUT detectKeyboardLayout()
            {
                std::cerr << "detectKeyboardLayout() not implemented " << std::endl;
                return KEYBOARD_LAYOUT::KBD_UNKNOWN;
            }
        #endif

        void printKeyboardLayout(KEYBOARD_LAYOUT layout)
        {
            if (layout > KEYBOARD_LAYOUT::KBD_UNKNOWN && layout < KEYBOARD_LAYOUT::KBD_COUNT)
                std::cerr << "Keyboard Layout: " << KeyboardLayoutName[(int)layout] << std::endl;
            else
                std::cerr << "Keyboard Layout: Unknown " << (int)layout << std::endl;
        }

    } // namespace sleek
} // namespace sleek