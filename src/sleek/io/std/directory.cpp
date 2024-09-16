#include "directory.h"

#include <experimental/filesystem>

namespace sleek
{
    namespace io
    {
        std_directory::std_directory(const std::string &filename) : directory()
        {
            dir = filename;
            refresh();
        }

        void std_directory::refresh() noexcept
        {
        }
    }
}