#ifndef __DIRECTORY__
#define __DIRECTORY__

#include <string>
#include <memory>
#include <vector>

#include "../define.h"

namespace sleek
{
    namespace io
    {
        class directory : public std::enable_shared_from_this<directory>
        {
            public:
                enum file_type
                {
                    none = 0,
                    not_found = -1,
                    regular = 1,
                    folder = 2,
                    symlink = 3,
                    block = 4,
                    character = 5,
                    fifo = 6,
                    socket = 7,
                    unknown = 8
                };

                struct entry
                {
                    bool operator == (const entry &e) { return filename == e.filename; }
                    std::string filename;
                    size_t offset;
                    size_t size;
                    file_type type;
                };

                using file_list = std::vector<directory::entry>;
            public:
                inline file_list::const_iterator begin() const noexcept { return file.begin(); }
                inline file_list::const_iterator end() const noexcept { return file.end(); }

                inline std::shared_ptr<directory> getptr() noexcept
                {
                    return shared_from_this();
                }

                virtual const std::string& filename() const noexcept
                {
                    return dir;
                }

                virtual directory::entry operator[] (u32 i) const noexcept
                {
                    return file[i];
                }

                virtual s32 count() const noexcept
                {
                    return file.size();
                }

                virtual void refresh() noexcept = 0;
            protected:
                file_list file;
                std::string dir;
        };
    }
}

#endif // __DIRECTORY__
