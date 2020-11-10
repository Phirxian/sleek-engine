#ifndef __FILE_SYSTEM__
#define __FILE_SYSTEM__

#include "directory.h"
#include "filereader.h"
#include "filewriter.h"
#include <vector>

namespace sleek
{
    namespace io
    {
        enum class FILE_SYSTEM_TYPE
        {
            FST_MEM,
            FST_STD,
            FST_ZIP,
            FST_COUNT
        };

        class archive;
        class archiveloader;

        class filesystem : public std::enable_shared_from_this<filesystem>
        {
            public:
                inline std::shared_ptr<filesystem> getptr() noexcept
                {
                    return shared_from_this();
                }

                virtual void cd(const std::string&) noexcept = 0;
                virtual const std::string& pwd() const noexcept = 0;

                virtual std::shared_ptr<filereader> read(const std::string&)  const noexcept = 0;
                virtual std::shared_ptr<filewriter> write(const std::string&) const noexcept = 0;

                virtual std::shared_ptr<archive>   load(const std::string&) const noexcept;
                virtual std::shared_ptr<directory> list(const std::string&) const noexcept = 0;

                std::vector<archiveloader*> loader;
        };

        std::shared_ptr<filesystem> createFilesystem(FILE_SYSTEM_TYPE, const std::string &working_dir = "");
    }
}

#include "archive.h"

#endif // __FILE_SYSTEM__
