#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class meshmime_txt : public mimetype
        {
            public:
                const char *getTypeName() const noexcept override { return "mesh_txt"; }

                bool match(const std::string&) const noexcept override;
        };

        class meshloader_txt : public meshloader
        {
            public:
                std::shared_ptr<driver::mesh> read(io::filereader*) const noexcept override;
        };

        class meshwriter_txt : public meshwriter
        {
            public:
                bool write(driver::mesh*, io::filewriter*) const noexcept override;
        };
    }
}

