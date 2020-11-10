#include "../ressource_loader.h"

namespace sleek
{
    namespace loader
    {
        class meshloader_3ds : public meshloader
        {
            public:
                virtual std::shared_ptr<driver::mesh> read(io::filereader*) const noexcept;

                virtual const char *getTypeName() const noexcept { return "meshloader_3ds"; }

                virtual bool write(driver::mesh*, io::filewriter*) const noexcept;

                virtual bool match(const std::string&) const noexcept;
        };
    }
}

