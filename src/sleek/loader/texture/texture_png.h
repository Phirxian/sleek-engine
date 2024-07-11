#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class texturemime_png : public mimetype
        {
            public:
                const char *getTypeName() const noexcept override { return "texture_png"; }

                int check_header(io::filereader*) const noexcept override;

                bool match(const std::string&) const noexcept override;
        };
        
        class textureloader_png : public textureloader
        {
            public:
                std::shared_ptr<driver::texture> read(io::filereader*) const noexcept override;
        };
        
        class texturewriter_png : public texturewriter
        {
            public:
                bool write(driver::texture*, io::filewriter*) const noexcept override;
        };
    }
}
