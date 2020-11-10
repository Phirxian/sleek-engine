#include "texture_jpg.h"
#include "../../driver/texture.h"
#include "../../compile.h"

#ifdef texture_loader_jpeg_support
    #include <jpeglib.h>
    #include <exception>
#endif

namespace sleek
{
    namespace loader
    {
        #ifdef texture_loader_jpeg_support
            struct jpegErrorManager
            {
                struct jpeg_error_mgr pub;
            };
            void jpegErrorExit (j_common_ptr cinfo)
            {
                char jpegLastErrorMsg[JMSG_LENGTH_MAX];
                jpegErrorManager* myerr = (jpegErrorManager*) cinfo->err;
                /*(* (cinfo->err->output_message) ) (cinfo);*/
                ( *(cinfo->err->format_message) ) (cinfo, jpegLastErrorMsg);
                throw std::runtime_error( jpegLastErrorMsg );
            }
        #endif

        int textureloader_jpg::check_header(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_jpeg_support
                u32 magic;
                file->read(&magic, 4);
                return magic == 0xffd8ffe0;
            #endif
            return false;
        }

        std::shared_ptr<driver::texture> textureloader_jpg::read(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_jpeg_support
                std::shared_ptr<driver::texture> img = nullptr;
                std::string data = file->readAll();

                jpeg_decompress_struct cinfo;

                jpegErrorManager jerr;
                cinfo.err = jpeg_std_error(&jerr.pub);
                jerr.pub.error_exit = jpegErrorExit;

                try
                {
                    jpeg_create_decompress(&cinfo);
                    jpeg_mem_src(&cinfo, (unsigned const char*)data.c_str(), data.size());

                    jpeg_read_header(&cinfo, TRUE);
                    jpeg_start_decompress(&cinfo);

                    img = std::make_shared<driver::texture>(
                        math::vec2i(cinfo.image_width, cinfo.image_height),
                        (driver::TextureFormat)cinfo.num_components
                    );

                    unsigned char* cdata = img->getBuffer();
                    unsigned char** p2 = &cdata;
                    int numlines = 0;

                    while(cinfo.output_scanline < cinfo.output_height)
                    {
                        numlines = jpeg_read_scanlines(&cinfo, p2, 1);
                        *p2 += numlines * 3 * cinfo.output_width;
                    }
                }
                catch(std::exception e)
                {
                }

                jpeg_destroy_decompress(&cinfo);
                return img;
            #else
                return nullptr;
            #endif
        }

        bool textureloader_jpg::write(driver::texture *img, io::filewriter *file) const noexcept
        {
            return false;
        }

        bool textureloader_jpg::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);

            return extention == "jpg" || extention == "jpeg" ||
                   extention == "jpe" || extention == "jfi"  ||
                   extention == "jif" || extention == "jfif";
        }
    }
}
