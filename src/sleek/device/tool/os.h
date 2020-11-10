#ifndef __System_command_h__
#define __System_command_h__

#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
#include "define.h"
#include <math.h>

namespace sleek
{
    namespace device
    {
        namespace tool
        {
            /************************************************************/
                void openURL(const char*) noexcept;
                std::string getUserHome() noexcept;                     // return home directorie of curent user, max buffer is 64 ex : c:/Documents and Setting/Ovan/ or /home/ovan/
                std::string getExecutablePath() noexcept;               // return executable directorie ex: c:/programe file/FEDA-Corp/IGZ
                std::string getUserName() noexcept;                     // return current login user name
                void Sleeping(const unsigned long ms) noexcept;         // is multiplatform of Sleep() windows
            /************************************************************/
                bool deleteFile(const std::string&) noexcept;
                bool checkFileExiste(const std::string&) noexcept;
                unsigned long checkFileSize(const std::string&) noexcept;
            /************************************************************/
        }
    }
}
#endif
