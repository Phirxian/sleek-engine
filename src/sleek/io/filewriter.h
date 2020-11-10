#ifndef __FILE_WRITER__
#define __FILE_WRITER__

#include <string>
#include <memory>
#include "../define.h"

namespace sleek
{
    namespace io
    {
        class filewriter : public std::enable_shared_from_this<filewriter>
        {
            public:
                inline std::shared_ptr<filewriter> getptr() noexcept
                {
                    return shared_from_this();
                }

                virtual const std::string& filename() const noexcept = 0;

                inline void write(const std::string &str) noexcept { return write(str.c_str(), str.size()); }

                virtual void put(const char) noexcept = 0;
                virtual void write(const void *, u32) noexcept = 0;
                virtual void seek(u32, bool relative = false) noexcept = 0;

                virtual u32 pos() noexcept = 0;
        };
    }
}

#endif // __FILE_WRITER__
