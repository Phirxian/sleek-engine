#include "filesystem.h"
#include "mem/filesystem.h"
#include "std/filesystem.h"
#include "zip/filesystem.h"
#include "../compile.h"

#include <memory>

namespace sleek
{
    namespace io
    {
        std::shared_ptr<archive> filesystem::load(const std::string &filename) const noexcept
        {
            for(auto e : loader)
                if(e->match(filename))
                    return e->load(filename);
            return nullptr;
        }
        std::shared_ptr<filesystem> createFilesystem(FILE_SYSTEM_TYPE e, const std::string &working_dir)
        {
            switch(e)
            {
                #ifdef mem_filesystem_support
                    case FILE_SYSTEM_TYPE::FST_MEM:
                        return std::make_shared<mem_filesystem>();
                #endif
                #ifdef std_filesystem_support
                    case FILE_SYSTEM_TYPE::FST_STD:
                        return std::make_shared<std_filesystem>(working_dir);
                #endif
                #ifdef std_filesystem_support
                    //case FILE_SYSTEM_TYPE::FST_ZIP:
                    //    return std::make_shared<zip_filesystem>(working_dir);
                #endif
            }
            return nullptr;
        }
    }
}
