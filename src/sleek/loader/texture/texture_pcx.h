#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        struct pcxheader
        {
            u8	Manufacturer;
            u8	Version;
            u8	Encoding;
            u8	BitsPerPixel;
            u16	XMin;
            u16	YMin;
            u16	XMax;
            u16	YMax;
            u16	HorizDPI;
            u16	VertDPI;
            u8	Palette[48];
            u8	Reserved;
            u8	Planes;
            u16	BytesPerLine;
            u16	PaletteType;
            u16	HScrSize;
            u16	VScrSize;
            u8	Filler[54];
        };

        class texture_pcx : public mimetype, public textureloader, public texturewriter
        {
            public:
                std::shared_ptr<driver::texture> read(io::filereader*) const noexcept override;

                const char *getTypeName() const noexcept override { return "texture_pcx"; }

                int check_header(io::filereader*) const noexcept override;

                bool write(driver::texture*, io::filewriter*) const noexcept override;

                bool match(const std::string&) const noexcept override;
        };
    }
}
