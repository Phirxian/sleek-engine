#ifndef __STD_DIRECTORY__
#define __STD_DIRECTORY__

#include <vector>
#include "../directory.h"

namespace sleek
{
    namespace io
    {
        class std_directory : public directory
        {
            public:
                std_directory(const std::string &filename);

                virtual void refresh() noexcept;
        };
    }
}

#endif // __DIRECTORY__
