#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class texturemime_pcx : public mimetype
        {
            public:
                const char *getTypeName() const noexcept override { return "texture_pcx"; }

                int check_header(io::filereader*) const noexcept override;

                bool match(const std::string&) const noexcept override;
        };

        class textureloader_pcx : public textureloader
        {
            public:
                std::shared_ptr<driver::texture> read(io::filereader*) const noexcept override;
        };

        class texturewriter_pcx : public texturewriter
        {
            public:
                bool write(driver::texture*, io::filewriter*) const noexcept override;
        };
    }
}
