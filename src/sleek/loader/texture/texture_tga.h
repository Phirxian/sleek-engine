#ifndef TEXTURE_TGA_H
#define TEXTURE_TGA_H

#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class texturemime_tga : public mimetype
        {
            public:
                const char *getTypeName() const noexcept override { return "texture_tga"; }

                bool match(const std::string&) const noexcept override;
        };

        class textureloader_tga : public textureloader
        {
            public:
                std::shared_ptr<driver::texture> read(io::filereader*) const noexcept override;
        };

        class texturewriter_tga : public texturewriter
        {
            public:
                bool write(driver::texture*, io::filewriter*) const noexcept override;
        };
    }
}

#endif // TEXTURE_TGA_H
