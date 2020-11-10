#include "../ressource_loader.h"

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

        class textureloader_pcx : public textureloader
        {
            public:
                virtual std::shared_ptr<driver::texture> read(io::filereader*) const noexcept;

                virtual const char *getTypeName() const noexcept { return "textureloader_pcx"; }

                virtual int check_header(io::filereader*) const noexcept;

                virtual bool write(driver::texture*, io::filewriter*) const noexcept;

                virtual bool match(const std::string&) const noexcept;
        };
    }
}
