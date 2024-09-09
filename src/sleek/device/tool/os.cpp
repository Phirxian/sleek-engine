#include "string.h"
#include "os.h"

#include <stdlib.h>
#include <unistd.h>

#if defined WIN32 || defined WIN64
    #include <windows.h>
#elif ____linux__
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
#elif __mac__
    #include <sys/types.h>
    #include <sys/sysctl.h>
#endif

namespace sleek
{
    namespace device
    {
        namespace tool
        {
            void openURL(const char*url) noexcept
            {
                #if defined WIN32
                    ShellExecute(NULL, NULL,url, NULL, NULL, SW_SHOWNORMAL);
                #elif defined __linux
                    execlp(url,url,NULL);
                #else
                    std::cout << "url " << url << "is not open because os not supported" << std::endl;
                #endif
            }

            std::string getUserHome() noexcept
            {
                return getenv("HOME");
            }

            std::string getUserName() noexcept
            {
                return getenv("USER");
            }

            std::string getExecutablePath() noexcept
            {
                std::string buffer;
                buffer.reserve(BUFSIZ);

                int bytes;
                #if defined WIN32
                    bytes = GetModuleFileName(NULL, const_cast<char*>(buffer.c_str()), BUFSIZ);
                #elif defined __linux
                    if(getpid())
                    {
                        sprintf(const_cast<char*>(buffer.c_str()), "/proc/%d/exe", getpid());
                        bytes = readlink(const_cast<char*>(buffer.c_str()), const_cast<char*>(buffer.c_str()), BUFSIZ);
                    }
                    else bytes = readlink("/proc/self/exe", const_cast<char*>(buffer.c_str()), BUFSIZ);
                #else
                    bytes = 1;
                    #warning undefined os
                #endif

                buffer.resize(bytes);
                return buffer;
            }

            void Sleeping(const unsigned long ms) noexcept
            {
                #if defined WIN32
                    Sleep(ms);
                #elif defined __linux
                    usleep(ms*1000);
                #else
                    #warning undefined os
                #endif
            }
        }
    }
}
