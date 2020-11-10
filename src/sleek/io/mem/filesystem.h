#ifndef __MEM_DIRECTORY__
#define __MEM_DIRECTORY__

#include "../../compile.h"
#include "../filesystem.h"

#ifdef std_filesystem_support
namespace sleek
{
    namespace io
    {
        class mem_filesystem : public filesystem, public directory
        {
            public:
                mem_filesystem() noexcept;
                virtual ~mem_filesystem() noexcept;

                virtual void cd(const std::string&) noexcept;
                virtual const std::string& pwd() const noexcept;

                virtual std::shared_ptr<filereader> read(const std::string&)  const noexcept;
                virtual std::shared_ptr<filewriter> write(const std::string&) const noexcept;
                virtual std::shared_ptr<directory> list(const std::string&) const noexcept;

                virtual void refresh() noexcept;
            protected:
                std::vector<std::vector<char>> stream;
                std::vector<std::string> filename;
                std::string cwd;
        };
    }
}
#endif

#endif // __FILE_SYSTEM__
