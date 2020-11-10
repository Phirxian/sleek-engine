#ifndef __STD_DIRECTORY__
#define __STD_DIRECTORY__

#include <vector>
#include "../directory.h"

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

namespace sleek
{
    namespace io
    {
        class std_directory : public directory
        {
            public:
                std_directory(const std::string &filename) : directory()
                {
                    dir = filename;
                    refresh();
                }

                virtual void refresh() noexcept
                {
                    file.clear();
                    for(auto& p: fs::directory_iterator(dir))
                    {
                        file.push_back(directory::entry{
                            p.path().filename(), 0, 0,
                            (file_type)p.status().type()
                        });
                    }
                }
        };
    }
}

#endif // __DIRECTORY__
