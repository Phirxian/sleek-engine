#ifndef __RESOURCE_LOADER__
#define __RESOURCE_LOADER__

#include <string>
#include <memory>
#include "../io/filesystem.h"

namespace sleek
{
    namespace driver
    {
        class mesh;
        class texture;
    }
    namespace loader
    {
        template<typename T>
        class ressource_loader
        {
            public:
                using type = T;
            public:
                virtual std::shared_ptr<T> read(io::filereader*) const noexcept = 0;

                virtual const char *getTypeName() const noexcept = 0;

                //! return -1 on failure, or version of the header [0, 1, 2, ...]
                virtual int check_header(io::filereader*) const noexcept { return true; }

                virtual bool write(T*, io::filewriter*) const noexcept = 0;

                virtual bool match(const std::string&) const noexcept = 0;
        };

        using meshloader = ressource_loader<driver::mesh>;
        using textureloader = ressource_loader<driver::texture>;
    }
}

#endif // __RESOURCE_LOADER__
