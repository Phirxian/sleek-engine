#include "texture_tiff.h"
#include "../../driver/texture.h"
#include "../../compile.h"

#ifdef texture_loader_tiff_support
    #include <tiffio.h>
#endif

namespace sleek
{
    namespace loader
    {
        #ifdef texture_loader_tiff_support
        static tsize_t tiff_Read(thandle_t st, tdata_t buffer, tsize_t size) noexcept
        {
            ((io::filereader*)st)->read(buffer, size);
        }

        static tsize_t tiff_Write(thandle_t st,tdata_t buffer,tsize_t size) noexcept
        {
            ((io::filewriter*)st)->write(buffer, size);
        }

        static int tiff_Close(thandle_t i) noexcept
        {
        }

        static toff_t tiff_Seek(thandle_t st, toff_t pos, int whence) noexcept
        {
            if(pos == 0xFFFFFFFF)
                return 0xFFFFFFFF;

            ((io::filereader*)st)->seek(pos, whence);
        }

        static toff_t tiff_Size(thandle_t st) noexcept
        {
            return ((io::filereader*)st)->size();
        }

        static int tiff_Map(thandle_t, tdata_t*, toff_t*) noexcept
        {
            return 0;
        }

        static void tiff_Unmap(thandle_t, tdata_t, toff_t) noexcept
        {
            return;
        }
        #endif

        std::shared_ptr<driver::texture> textureloader_tiff::read(io::filereader *file) const noexcept
        {
            std::shared_ptr<driver::texture> img;

            #ifdef texture_loader_tiff_support
                TIFF* tif = TIFFClientOpen(
                    "File", "r", (thandle_t)file,
                    tiff_Read, nullptr, tiff_Seek,
                    tiff_Close, tiff_Size,
                    tiff_Map, tiff_Unmap
                );

                if(!tif)
                    return nullptr;

                u32 w, h;
                TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
                TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);

                img = std::make_shared<driver::texture>(math::vec2i(w, h));

                bool succ = TIFFReadRGBAImageOriented(tif, w, h, (uint32*)img->getBuffer(), ORIENTATION_TOPLEFT, 0);
                TIFFClose(tif);

                if(!succ)
                    return nullptr;

                //swap red and blue channels
                int size = w*h;
                unsigned char* cdata = img->getBuffer();

                for(int i=0; i<size; i++)
                {
                    unsigned char tmp = cdata[i*4];
                    cdata[i*4] = cdata[i*4+2];
                    cdata[i*4+2] = tmp;
                }
            #endif

            return img;
        }

        bool textureloader_tiff::write(driver::texture *img, io::filewriter *file) const noexcept
        {
            return false;
        }

        bool textureloader_tiff::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);
            return extention == "tiff" || extention == "tif";
        }
    }
}
