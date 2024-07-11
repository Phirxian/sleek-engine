#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class texturemime_pgm : public mimetype
        {
            public:
                const char *getTypeName() const noexcept override { return "texture_pgm"; }

                int check_header(io::filereader*) const noexcept override;

                bool match(const std::string&) const noexcept override;
        };
        
        class textureloader_pgm : public textureloader
        {
            public:
                std::shared_ptr<driver::texture> read(io::filereader*) const noexcept override;
        };
        
        class texturewriter_pgm : public texturewriter
        {
            public:
                bool write(driver::texture*, io::filewriter*) const noexcept override;
        };
    }
}
