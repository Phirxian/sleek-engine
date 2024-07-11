#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class meshmime_3ds : public mimetype
        {
            public:
                const char *getTypeName() const noexcept override { return "mesh_3ds"; }

                bool match(const std::string&) const noexcept override;
        };

        class meshloader_3ds : public meshloader
        {
            public:
                std::shared_ptr<driver::mesh> read(io::filereader*) const noexcept override;
        };
    }
}

