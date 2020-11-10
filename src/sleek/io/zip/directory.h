#ifndef __ZIP_DIRECTORY__
#define __ZIP_DIRECTORY__

#include <zip.h>
#include <algorithm>
#include "../directory.h"

namespace sleek
{
    namespace io
    {
        class zip_directory : public directory
        {
            public:
                zip_directory(zip *zip, const std::string &filename)
                    : archive(zip), directory()
                {
                    dir = filename;
                    refresh();
                }

                ~zip_directory()
                {
                }

                virtual void refresh() noexcept
                {
                    if(!archive)
                        return;

                    file.clear();

                    for(size_t i = 0; i < zip_get_num_entries(archive, 0); ++i)
                    {
                        struct zip_stat st;

                        zip_stat_init(&st);
                        zip_stat_index(archive, i, 0, &st);
                        std::string path(st.name);

                        // filtering with the working directory path
                        if(path.substr(0, dir.size()) != dir)
                            continue;

                        // remove the working directory path of the filename
                        path = std::string(st.name+dir.size());
                        int slash_cout = std::count(path.begin(), path.end(), '/');
                            slash_cout -= path[0] == '/';

                        // filtering to exclude sub-folder filename
                        if(path.size() == 0)
                            continue;

                        if(slash_cout == 0)
                            file.push_back({path, st.index, st.size, directory::regular});
                        else if(slash_cout == 1)
                        {
                            path = path.substr(0, path.find_first_of('/'));
                            file.push_back({path, st.index, st.size, directory::folder});
                        }

                        // higher slash_cout is in depth, would not be include
                    }

                    // remove diplicated sub-folder
                    file.erase(std::unique(file.begin(), file.end()), file.end());
                }
            private:
                zip *archive;
        };
    }
}

#endif // __DIRECTORY__
