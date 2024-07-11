#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class texture_bmp : public mimetype, public textureloader, public texturewriter
        {
            public:
                std::shared_ptr<driver::texture> read(io::filereader*) const noexcept override;

                const char *getTypeName() const noexcept override { return "texture_bmp"; }

                int check_header(io::filereader*) const noexcept override;

                bool write(driver::texture*, io::filewriter*) const noexcept override;

                bool match(const std::string&) const noexcept override;
            private:
                void decompress8BitRLE(u8*& BmpData, s32 size, s32 width, s32 height, s32 pitch) const;

                void decompress4BitRLE(u8*& BmpData, s32 size, s32 width, s32 height, s32 pitch) const;
        };
    }
}
