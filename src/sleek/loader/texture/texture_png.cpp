#include "texture_png.h"
#include "../../driver/texture.h"
#include "../../compile.h"
#include <stdlib.h>
#include <png.h>

extern "C" {
    void* memccpy(void *dest, const void *src, int c, size_t n);
}

namespace sleek
{
    namespace loader
    {
        #ifdef texture_loader_png_support
        static void png_cpexcept_error(png_structp png_ptr, png_const_charp msg)
        {
            printf("PNG fatal error: %s", msg);
            longjmp(png_jmpbuf(png_ptr), 1);
        }

        // PNG function for warning handling
        static void png_cpexcept_warn(png_structp png_ptr, png_const_charp msg)
        {
            printf("PNG warning: %s", msg);
        }

        void PNGAPI user_read_data_fcn(png_structp png_ptr, png_bytep data, png_size_t length)
        {
            io::filereader *file = (io::filereader*)png_get_io_ptr(png_ptr);
            int pos = file->pos();
            file->read((char*)data,(u32)length);

            if((file->pos()-pos) != length)
                png_error(png_ptr, "Read Error");
        }

        void PNGAPI user_write_data_fcn(png_structp png_ptr, png_bytep data, png_size_t length)
        {
            io::filewriter *file = (io::filewriter*)png_get_io_ptr(png_ptr);
            file->write((char*)data,(u32)length);
        }
        #endif

        int texturemime_png::check_header(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_png_support
                png_byte magic[8];
                file->read(magic, sizeof(magic));
                return -!png_check_sig(magic, sizeof (magic));
            #endif
            return -1;
        }

        std::shared_ptr<driver::texture> textureloader_png::read(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_png_support
                png_byte magic[8];
                png_structp png_ptr;
                png_infop info_ptr;
                int bit_depth = 0, color_type = 0;
                png_bytep *row_pointers = 0;
                png_uint_32 w = 0, h = 0;
                GLubyte *texels = 0;

                file->read(magic, sizeof(magic));

                if(!png_check_sig(magic, sizeof (magic)))
                    return nullptr;

                png_ptr = png_create_read_struct(
                    PNG_LIBPNG_VER_STRING, NULL,
                    (png_error_ptr)png_cpexcept_error,
                    (png_error_ptr)png_cpexcept_warn
                );

                if(!png_ptr)
                    return nullptr;

                info_ptr = png_create_info_struct(png_ptr);
                if(!info_ptr || setjmp(png_jmpbuf(png_ptr)))
                {
                    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
                    if(row_pointers)
                        free(row_pointers);
                    return nullptr;
                }

                png_set_read_fn(png_ptr, file, user_read_data_fcn);
                png_set_sig_bytes(png_ptr, sizeof (magic));
                png_read_info(png_ptr, info_ptr);

                bit_depth = png_get_bit_depth(png_ptr, info_ptr);
                color_type = png_get_color_type(png_ptr, info_ptr);

                if(color_type == PNG_COLOR_TYPE_PALETTE)
                    png_set_palette_to_rgb(png_ptr);

                if(bit_depth < 8)
                {
                    if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
                        png_set_expand_gray_1_2_4_to_8(png_ptr);
                    else png_set_packing(png_ptr);
                }

                if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
                    png_set_tRNS_to_alpha(png_ptr);

                if(bit_depth == 16)
                    png_set_strip_16(png_ptr);

                if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
                    png_set_gray_to_rgb(png_ptr);

                //! internal png format change to bgr/rgb
                png_set_bgr(png_ptr);

                png_read_update_info(png_ptr, info_ptr);
                png_get_IHDR(png_ptr, info_ptr, &w, &h, &bit_depth, &color_type, 0, 0, 0);

                int internalFormat = 0;
                if(color_type == PNG_COLOR_TYPE_GRAY)       internalFormat = driver::TXFMT_LUMINANCE;
                if(color_type == PNG_COLOR_TYPE_GRAY_ALPHA) internalFormat = driver::TXFMT_LUMINANCE_ALPHA;
                if(color_type == PNG_COLOR_TYPE_RGB)        internalFormat = driver::TXFMT_RGB;
                if(color_type == PNG_COLOR_TYPE_RGB_ALPHA)  internalFormat = driver::TXFMT_RGBA;

                texels = (GLubyte*)malloc(sizeof(GLubyte)*w*h*internalFormat);
                row_pointers = new png_bytep[h];

                // vertival flip or not ? comment = not
                //for(register unsigned int i = 0; i < h; ++i)
                //    row_pointers[i] = (png_bytep)(texels+(i*w*internalFormat));
                
                for(unsigned int i = 0; i < h; ++i)
                    row_pointers[i] = (png_bytep)(texels+((h-(i+1))*w*internalFormat));

                png_read_image(png_ptr, row_pointers);
                png_read_end(png_ptr, 0);
                png_destroy_read_struct(&png_ptr, &info_ptr, 0);
                delete row_pointers;

                auto tmp = std::make_shared<driver::texture>(math::vec2i(w, h), (driver::TextureFormat)internalFormat);
                memccpy(tmp->getBuffer(), (u8*)texels, 1, tmp->getBufferSize());

                //! png seem use BGR data ?
                if(color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_RGB_ALPHA)
                {
                    for (unsigned x = 0; x<w; ++x)
                    {
                        for (unsigned y = 0; y<h; ++y)
                        {
                            auto pixel = tmp->getPixel({x,y});
                            auto new_pixel = math::pixel{pixel.blue, pixel.green, pixel.red, pixel.alpha};
                            tmp->setPixel({x,y}, new_pixel);
                        }
                    }
                }

                tmp->flipVertical();
                return tmp;
            #else
                return nullptr;
            #endif
        }

        bool texturewriter_png::write(driver::texture *img, io::filewriter *file) const noexcept
        {
            #ifdef texture_loader_png_support
                png_structp p = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
                png_infop info_ptr = png_create_info_struct(p);

                static const int png_color_type[] = {
                    PNG_COLOR_TYPE_GRAY,
                    PNG_COLOR_TYPE_GRAY_ALPHA,
                    PNG_COLOR_TYPE_RGB,
                    PNG_COLOR_TYPE_RGB_ALPHA,
                };

                int colorType = png_color_type[img->getComposantCount()];

                png_set_IHDR(
                    p, info_ptr,
                    img->getDimension().x,
                    img->getDimension().y,
                    img->getFormat() >= 5 ? 32 : 8,
                    colorType,
                    PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_DEFAULT,
                    PNG_FILTER_TYPE_DEFAULT
                );

                png_set_write_fn(p, file, user_write_data_fcn, NULL);
                png_write_info(p, info_ptr);

                //std::vector<png_bytep> row_pointers(img->getDimension().y);
                //for (int y = 0; y < img->getDimension().y; y++)
                //    row_pointers[y] = const_cast<png_bytep>(&img->getBuffer()[(y * img->getDimension().x)*img->getPitch()]);


                std::vector<png_bytep> row_pointers(img->getDimension().y);
                for (int y = 0; y < img->getDimension().y; ++y)
                {
                    row_pointers[y] = new png_byte[png_get_rowbytes(p, info_ptr)];
                    for (int x = 0; x < img->getDimension().x; ++x)
                    {
                        math::pixel pixel = img->getPixel(math::vec2i(x, y));
                        int index = x * png_get_channels(p, info_ptr);
                        
                        row_pointers[y][index] = pixel.red;

                        if(colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
                            row_pointers[y][index + 1] = pixel.alpha;

                        if(colorType == PNG_COLOR_TYPE_RGB)
                        {
                            row_pointers[y][index + 1] = pixel.green;
                            row_pointers[y][index + 2] = pixel.blue;
                        }

                        if (colorType == PNG_COLOR_TYPE_RGBA)
                        {
                            row_pointers[y][index + 1] = pixel.green;
                            row_pointers[y][index + 2] = pixel.blue;
                            row_pointers[y][index + 3] = pixel.alpha;
                        }
                    }
                }

                png_set_rows(p, info_ptr, &row_pointers[0]);
                png_write_png(p, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
                png_destroy_write_struct(&p, NULL);

                return true;
            #endif
            return false;
        }

        bool texturemime_png::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);
            return extention == "png" || extention == "jng" || extention == "mnj" || extention == "apng";
        }
    }
}
