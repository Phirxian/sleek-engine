#include "texture_pgm.h"
#include "../../driver/texture.h"
#include "../../compile.h"

#include <sstream>

namespace sleek
{
    namespace loader
    {
        int texture_pgm::check_header(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_pgm_support
                char line[3];
                file->read(line, 3);
                return line[0] == 'P' && std::isalnum(line[1]) && line[2] == '\n';
            #endif
            return false;
        }

        std::shared_ptr<driver::texture> texture_pgm::read(io::filereader *file) const noexcept
        {
            #ifdef texture_loader_pgm_support
                std::string line = "";
                file->getline(line);

                if(line.size() == 3 && line[0] != 'P' && !std::isalnum(line[1]) && line[2] != '\n')
                    return nullptr;

                int magic = std::atoi(line.c_str()+1);
                int bitcount = (magic-1)%3+1;

                if(magic < 1 || magic > 6)
                    return nullptr;

                // comment line
                do { file->getline(line); }
                while(line[0] == '#');

                s32 width = std::atoi(line.c_str());
                s32 height = std::atoi(line.c_str() + (int)std::log10(width) + 1);

                auto img = std::make_shared<driver::texture>(math::vec2i{width, height}, (driver::TextureFormat)bitcount);

                if(bitcount == 1)
                {
                    file->getline(line);
                    s32 max_value = std::atoi(line.c_str());
                }

                if(magic >= 4)
                {
                    auto count = file->size() - file->pos();
                    file->read(img->getBuffer(), count);
                }
                else
                {
                    for(auto *it : *img)
                    {
                        for(int i = 0; i<bitcount; ++i)
                        {
                            file->getline(line);
                            it[i] = std::atoi(line.c_str());
                        }
                    }
                }

                if(bitcount == 1)
                {
                    for(int y = 0; y<height; ++y)
                    {
                        for(int x = 0; x<height; ++x)
                        {
                            auto px = img->getPixel({x,y}) * 255;
                            img->setPixel({x,y}, px);
                        }
                    }
                }
                else
                {
                    for(int y = 0; y<height; ++y)
                    {
                        for(int x = 0; x<height; ++x)
                        {
                            auto px = img->getPixel({x,y});
                            std::swap(px.green, px.blue); // RGB -> RBG
                            std::swap(px.blue, px.red);   // RBG -> GBR
                            img->setPixel({x,y}, px);
                        }
                    }
                }

                return img;
            #else
            return nullptr;
            #endif
        }

        bool texture_pgm::write(driver::texture *img, io::filewriter *file) const noexcept
        {
            #ifdef texture_loader_pgm_support
                if(img->getFormat() >= 5)
                    return false;

                file->write("P3\n");
                file->write(std::to_string(img->getDimension().x) + " ");
                file->write(std::to_string(img->getDimension().y) + "\n");
                file->write("255\n");

                for (int y = 0; y < img->getDimension().y; ++y)
                {
                    for (int x = 0; x < img->getDimension().x; ++x)
                    {
                        auto pixel = img->getPixel({x,y});
                        file->write(std::to_string(pixel.red) + " ");
                        file->write(std::to_string(pixel.green) + " ");
                        file->write(std::to_string(pixel.blue) + "\n");
                    }
                }

                return true;
            #endif
            return false;
        }

        bool texture_pgm::match(const std::string &filename) const noexcept
        {
            int index = filename.find_last_of('.')+1;
            auto extention = filename.substr(index, filename.size()-index);
            return extention == "pbm" || extention == "pgm" || extention == "ppm";
        }
    }
}
