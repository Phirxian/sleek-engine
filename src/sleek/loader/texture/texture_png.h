#include "../ressource_loader.h"

namespace sleek
{
    namespace loader
    {
        class textureloader_png : public textureloader
        {
            public:
                virtual std::shared_ptr<driver::texture> read(io::filereader*) const noexcept;

                virtual const char *getTypeName() const noexcept { return "textureloader_png"; }

                virtual int check_header(io::filereader*) const noexcept;

                virtual bool write(driver::texture*, io::filewriter*) const noexcept;

                virtual bool match(const std::string&) const noexcept;
        };
    }
}
