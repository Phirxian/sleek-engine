#ifndef __STD_FILE_SYSTEM__
#define __STD_FILE_SYSTEM__

#include "../../compile.h"
#include "../filesystem.h"

#ifdef std_filesystem_support
namespace sleek
{
    namespace io
    {
        class std_filesystem : public filesystem
        {
            public:
                std_filesystem(const std::string &working_dir) noexcept;
                virtual ~std_filesystem() noexcept;

                virtual void cd(const std::string&) noexcept;
                virtual const std::string& pwd() const noexcept;

                virtual std::shared_ptr<filereader> read(const std::string&)  const noexcept;

                virtual std::shared_ptr<filewriter> write(const std::string&) const noexcept;

                virtual std::shared_ptr<directory> list(const std::string&) const noexcept;
            private:
                std::string cwd;
        };
    }
}
#endif

#endif // __FILE_SYSTEM__
