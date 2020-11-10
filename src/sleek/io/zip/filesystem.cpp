#include "filesystem.h"

#ifdef zip_filesystem_support
#include "directory.h"
#include "filereader.h"
#include <unistd.h>

namespace sleek
{
    namespace io
    {
        zip_filesystem::zip_filesystem(const std::string &filename) noexcept
            : cwd("/"), filename(filename)
        {
            archive = zip_open(filename.c_str(), 0, NULL);
        }

        zip_filesystem::~zip_filesystem() noexcept
        {
            zip_close(archive);
        }

        void zip_filesystem::cd(const std::string &path) noexcept
        {
            cwd = path;
        }

        const std::string& zip_filesystem::pwd() const noexcept
        {
            return cwd;
        }

        std::shared_ptr<filereader> zip_filesystem::read(const std::string &filename)  const noexcept
        {
            auto e = std::make_shared<zip_filereader>(archive, filename);

            if(e->is_open())
                return e;

            return nullptr;
        }

        std::shared_ptr<filewriter> zip_filesystem::write(const std::string &filename) const noexcept
        {
            // not yet supported
            return nullptr;
        }

        std::shared_ptr<directory> zip_filesystem::list(const std::string &filename) const noexcept
        {
            return std::make_shared<zip_directory>(archive, cwd+"/"+filename);
        }
    }
}
#endif
