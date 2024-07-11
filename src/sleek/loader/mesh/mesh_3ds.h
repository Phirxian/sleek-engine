#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class mesh_3ds : public mimetype, public meshloader
        {
            public:
                std::shared_ptr<driver::mesh> read(io::filereader*) const noexcept override;

                const char *getTypeName() const noexcept override { return "mesh_3ds"; }

                bool match(const std::string&) const noexcept override;
        };
    }
}

