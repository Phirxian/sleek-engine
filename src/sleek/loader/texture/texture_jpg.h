#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class texturemime_jpg : public mimetype
        {
            public:
                const char *getTypeName() const noexcept override { return "texture_jpg"; }

                int check_header(io::filereader*) const noexcept override;

                bool match(const std::string&) const noexcept override;
        };
        
        class textureloader_jpg : public textureloader
        {
            public:
                std::shared_ptr<driver::texture> read(io::filereader*) const noexcept override;
        };
        
        class texturewriter_jpg : public texturewriter
        {
            public:
                bool write(driver::texture*, io::filewriter*) const noexcept override;
        };
    }
}
