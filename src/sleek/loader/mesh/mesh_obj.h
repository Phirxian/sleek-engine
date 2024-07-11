#ifndef MESH_OBJ_H
#define MESH_OBJ_H

#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class mesh_obj : public mimetype, public meshloader, public meshwriter
        {
            public:
                std::shared_ptr<driver::mesh> read(io::filereader*) const noexcept override;

                const char *getTypeName() const noexcept override { return "mesh_md5"; }

                bool match(const std::string&) const noexcept override;

                bool write(driver::mesh *m, io::filewriter *out) const noexcept override;
        };
    }
}

#endif // MESH_MD5_H
