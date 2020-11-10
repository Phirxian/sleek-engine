#ifndef __FILE_READER__
#define __FILE_READER__

#include <string>
#include <memory>
#include "../define.h"

namespace sleek
{
    namespace io
    {
        class filereader : public std::enable_shared_from_this<filereader>
        {
            public:
                inline std::shared_ptr<filereader> getptr() noexcept
                {
                    return shared_from_this();
                }

                virtual const std::string& filename() const noexcept = 0;

                virtual void read(void *, u32) noexcept = 0;
                virtual void seek(u32, bool relative = false) noexcept = 0;

                virtual u32 pos() const noexcept = 0;
                virtual u32 size() const noexcept = 0;
                virtual bool as_data() const noexcept { return pos() < size(); }

                virtual void getline(std::string&) noexcept = 0;
                virtual std::string readAll() noexcept = 0;
        };
    }
}

#endif // __FILE_WRITER__
