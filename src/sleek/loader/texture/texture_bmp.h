#include "../ressource_loader.h"

namespace sleek
{
    namespace loader
    {
        class textureloader_bmp : public textureloader
        {
            public:
                virtual std::shared_ptr<driver::texture> read(io::filereader*) const noexcept;

                virtual const char *getTypeName() const noexcept { return "textureloader_bmp"; }

                virtual int check_header(io::filereader*) const noexcept;

                virtual bool write(driver::texture*, io::filewriter*) const noexcept;

                virtual bool match(const std::string&) const noexcept;
            private:
                void decompress8BitRLE(u8*& BmpData, s32 size, s32 width, s32 height, s32 pitch) const;

                void decompress4BitRLE(u8*& BmpData, s32 size, s32 width, s32 height, s32 pitch) const;
        };
    }
}
