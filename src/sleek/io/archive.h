#ifndef __ARCHIVE__
#define __ARCHIVE__

#include <memory>
#include <string>

#include "filesystem.h"
#include "filereader.h"
#include "filewriter.h"
#include "directory.h"

namespace sleek
{
    namespace io
    {
        class archive : public filesystem
        {
            public:
                virtual const std::string& filename() = 0;

                virtual std::shared_ptr<filereader> read(const std::string&) = 0;
                virtual std::shared_ptr<filewriter> write(const std::string&) = 0;

                virtual std::shared_ptr<archive>    load(const std::string&) = 0;
                virtual std::shared_ptr<directory>  list(const std::string&) = 0;
        };

        class archiveloader : public std::enable_shared_from_this<archiveloader>
        {
            public:

                inline std::shared_ptr<archiveloader> getptr() noexcept
                {
                    return shared_from_this();
                }

                /**
                 * test if the given filename can be loader
                 */
                virtual bool match(const std::string&) const noexcept = 0;

                virtual std::shared_ptr<archive> load(const std::string&) const noexcept = 0;
        };
    }
}

#endif // __ARCHIVE_LOADER__
