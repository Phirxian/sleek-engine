#ifndef MESH_OBJ_H
#define MESH_OBJ_H

#include "../ressource_loader.h"

namespace sleek
{
    namespace loader
    {
        class meshloader_obj : public meshloader
        {
            public:
                virtual std::shared_ptr<driver::mesh> read(io::filereader*) const noexcept;

                virtual const char *getTypeName() const noexcept { return "meshloader_md5"; }

                virtual bool write(driver::mesh*, io::filewriter*) const noexcept;

                virtual bool match(const std::string&) const noexcept;
        };
    }
}

#endif // MESH_MD5_H
