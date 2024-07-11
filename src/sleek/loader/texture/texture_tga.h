#ifndef TEXTURE_TGA_H
#define TEXTURE_TGA_H

#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class texture_tga : public mimetype, public textureloader, public texturewriter
        {
            public:
                std::shared_ptr<driver::texture> read(io::filereader*) const noexcept override;

                const char *getTypeName() const noexcept override { return "texture_tga"; }

                bool write(driver::texture*, io::filewriter*) const noexcept override;

                bool match(const std::string&) const noexcept override;
        };
    }
}

#endif // TEXTURE_TGA_H
