#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class texturemime_tiff : public mimetype
        {
            public:
                const char *getTypeName() const noexcept override { return "texture_tiff"; }

                bool match(const std::string&) const noexcept override;
        };

        class textureloader_tiff : public textureloader
        {
            public:
                std::shared_ptr<driver::texture> read(io::filereader*) const noexcept override;
        };
    }
}
