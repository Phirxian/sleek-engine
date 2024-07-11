#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class mesh_txt : public mimetype, public meshloader, public meshwriter
        {
            public:
                std::shared_ptr<driver::mesh> read(io::filereader*) const noexcept override;

                const char *getTypeName() const noexcept override { return "mesh_txt"; }

                bool write(driver::mesh*, io::filewriter*) const noexcept override;

                bool match(const std::string&) const noexcept override;
        };
    }
}

