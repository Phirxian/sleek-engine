#include "texture_jpg.h"
#include "../../driver/texture.h"
#include "../../compile.h"
#include <setjmp.h>
#include <iostream>

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

        int texturemime_jpg::check_header(io::filereader *file) const noexcept
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
                    std::cout << e.what() << std::endl;
                }

                jpeg_destroy_decompress(&cinfo);
                return img;
            #else
                return nullptr;
            #endif
        }

        bool texturewriter_jpg::write(driver::texture *img, io::filewriter *file) const noexcept
        {
            #ifdef texture_loader_jpeg_support
                struct jpeg_compress_struct cinfo;
                struct jpeg_error_mgr jerr;

                cinfo.err = jpeg_std_error(&jerr);
                jerr.error_exit = [](j_common_ptr cinfo){
                    std::cout << cinfo->err << std::endl;
                };

                //setjmp(jerr.setjmp_buffer);
                jpeg_create_compress(&cinfo);

                unsigned char* buffer = nullptr;
                unsigned long size = 0;
                jpeg_mem_dest(&cinfo, &buffer, &size);

                int width = img->getDimension().x;
                int height = img->getDimension().y;
                int numComponents;

                switch (img->getFormat())
                {
                    case driver::TXFMT_LUMINANCE:
                        numComponents = 1;
                    break;
                    case driver::TXFMT_RGB:
                    case driver::TXFMT_RGBA:
                        numComponents = 3; // JPEG doesn't support alpha, so we'll ignore it
                    break;
                    default:
                        jpeg_destroy_compress(&cinfo);
                        std::cout << "Unsupported texture format for JPEG writing" << std::endl;
                        return false;
                }

                cinfo.image_width = width;
                cinfo.image_height = height;
                cinfo.input_components = numComponents;
                cinfo.in_color_space = (numComponents == 1) ? JCS_GRAYSCALE : JCS_RGB;

                std::vector<JSAMPLE> rowBuffer(width * numComponents);
                JSAMPROW rowPointer[1];

                jpeg_set_defaults(&cinfo);
                jpeg_set_quality(&cinfo, 99, TRUE);
                jpeg_start_compress(&cinfo, TRUE);

                for(int y = 0; y < img->getDimension().y; ++y)
                {
                    for(int x = 0; x < img->getDimension().x; ++x)
                    {
                        math::pixel pixel = img->getPixel(math::vec2i(x, y));
                        int index = x * numComponents;
                        rowBuffer[index] = pixel.red;
                        if (numComponents == 3)
                        {
                            rowBuffer[index + 1] = pixel.green;
                            rowBuffer[index + 2] = pixel.blue;
                        }
                    }
                    rowPointer[0] = rowBuffer.data();
                    jpeg_write_scanlines(&cinfo, rowPointer, 1);
                }
                
                jpeg_finish_compress(&cinfo);
                jpeg_destroy_compress(&cinfo);
                file->write(buffer, size);

                return true;
            #endif
            return false;
        }

        bool texturemime_jpg::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);

            return extention == "jpg" || extention == "jpeg" ||
                   extention == "jpe" || extention == "jfi"  ||
                   extention == "jif" || extention == "jfif";
        }
    }
}
