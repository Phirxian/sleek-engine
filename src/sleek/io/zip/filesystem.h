#ifndef __ZIP_FILESYSTEM__
#define __ZIP_FILESYSTEM__

#include "../../compile.h"
#include "../filesystem.h"

#ifdef zip_filesystem_support
#include <zip.h>
namespace sleek
{
    namespace io
    {
        class zip_filesystem : public filesystem
        {
            public:
                zip_filesystem(const std::string &filename) noexcept;
                virtual ~zip_filesystem() noexcept;

                virtual void cd(const std::string&) noexcept;
                virtual const std::string& pwd() const noexcept;

                virtual std::shared_ptr<filereader> read(const std::string&)  const noexcept;
                virtual std::shared_ptr<filewriter> write(const std::string&) const noexcept;
                virtual std::shared_ptr<directory>  list(const std::string&)  const noexcept;
            protected:
                zip *archive;
                std::string cwd, filename;
        };
    }
}
#endif

#endif // __FILE_SYSTEM__
