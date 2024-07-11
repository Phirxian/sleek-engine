#ifndef MESH_OBJ_H
#define MESH_OBJ_H

#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class meshmime_obj : public mimetype
        {
            public:
                const char *getTypeName() const noexcept override { return "mesh_md5"; }

                bool match(const std::string&) const noexcept override;
        };

        class meshloader_obj : public meshloader
        {
            public:
                std::shared_ptr<driver::mesh> read(io::filereader*) const noexcept override;
        };

        class meshwriter_obj : public meshwriter
        {
            public:
                bool write(driver::mesh *m, io::filewriter *out) const noexcept override;
        };
    }
}

#endif // MESH_MD5_H
