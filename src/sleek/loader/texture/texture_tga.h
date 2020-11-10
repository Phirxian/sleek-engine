#ifndef TEXTURE_TGA_H
#define TEXTURE_TGA_H

#include "../ressource_loader.h"

namespace sleek
{
    namespace loader
    {
        class textureloader_tga : public textureloader
        {
            public:
                virtual std::shared_ptr<driver::texture> read(io::filereader*) const noexcept;

                virtual const char *getTypeName() const noexcept { return "textureloader_tga"; }

                virtual bool write(driver::texture*, io::filewriter*) const noexcept;

                virtual bool match(const std::string&) const noexcept;
        };
    }
}

#endif // TEXTURE_TGA_H
