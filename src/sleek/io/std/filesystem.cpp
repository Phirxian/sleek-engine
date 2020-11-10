#include "filesystem.h"

#ifdef std_filesystem_support
#include "directory.h"
#include "filereader.h"
#include "filewriter.h"
#include <unistd.h>

namespace sleek
{
    namespace io
    {
        std_filesystem::std_filesystem(const std::string &working_dir) noexcept
        {
            if(working_dir.size())
                cd(working_dir);
            else
            {
                char cCurrentPath[FILENAME_MAX];
                getcwd(cCurrentPath, sizeof(cCurrentPath));
                cwd = cCurrentPath;
            }
        }

        std_filesystem::~std_filesystem() noexcept
        {
        }

        void std_filesystem::cd(const std::string &path) noexcept
        {
            /*
             * at this time only
             * can be better in futur to build filename path
             * of @read and @write function from the system pwd and internal class pwd
             * and allow programm to have multiple instance of filesystem
             */
            /**
             * TODO
             */
            cwd = path;
        }

        const std::string& std_filesystem::pwd() const noexcept
        {
            return cwd;
        }

        std::shared_ptr<filereader> std_filesystem::read(const std::string &filename)  const noexcept
        {
            auto e = std::make_shared<std_filereader>(filename);

            if(e->is_open())
                return e;

            return nullptr;
        }

        std::shared_ptr<filewriter> std_filesystem::write(const std::string &filename) const noexcept
        {
            auto e = std::make_shared<std_filewriter>(filename);

            if(e->is_open())
                return e;

            return nullptr;
        }

        std::shared_ptr<directory> std_filesystem::list(const std::string &filename) const noexcept
        {
            return std::make_shared<std_directory>(filename);
        }
    }
}
#endif
