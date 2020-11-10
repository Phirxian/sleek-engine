#include "filesystem.h"

#ifdef mem_filesystem_support
#include "filereader.h"
#include "filewriter.h"
#include <unistd.h>

namespace sleek
{
    namespace io
    {
        mem_filesystem::mem_filesystem() noexcept
            : cwd("mem://"), directory()
        {
            dir = cwd;
        }

        mem_filesystem::~mem_filesystem() noexcept
        {
        }

        void mem_filesystem::cd(const std::string &path) noexcept
        {
        }

        const std::string& mem_filesystem::pwd() const noexcept
        {
            return cwd;
        }

        std::shared_ptr<filereader> mem_filesystem::read(const std::string &filename)  const noexcept
        {
            for(int i = 0; i<file.size(); ++i)
                if(file[i].filename == filename)
                    return std::make_shared<mem_filereader>(filename, stream[i]);
            return nullptr;
        }

        std::shared_ptr<filewriter> mem_filesystem::write(const std::string &filename) const noexcept
        {
            mem_filesystem *tmp = const_cast<mem_filesystem*>(this);
            // evil const hack, technicaly unsafe, may need refactoring

            tmp->file.push_back({filename, file.size()-1, 0, directory::character});
            tmp->stream.push_back({});

            auto e = std::make_shared<mem_filewriter>(filename, tmp->stream[stream.size()-1]);

            if(e->is_open())
                return e;

            return nullptr;
        }

        std::shared_ptr<directory> mem_filesystem::list(const std::string &filename) const noexcept
        {
            mem_filesystem *tmp = const_cast<mem_filesystem*>(this);
            directory *tmp2 = static_cast<directory*>(tmp);
            // evil const hack, but safe for this purpose
            return tmp2->shared_from_this();
        }

        //! directory part

        void mem_filesystem::refresh() noexcept
        {
            for(int i = 0; i<filename.size(); ++i)
            {
                file[i].offset = i;
                file[i].size = stream[i].size();
            }
        }
    }
}
#endif
