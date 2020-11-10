#include "loader.h"
#include "../driver/texture.h"
#include "../driver/mesh.h"
#include "../compile.h"

#include "mesh/mesh_3ds.h"
#include "mesh/mesh_txt.h"
#include "mesh/mesh_obj.h"
#include "texture/texture_bmp.h"
#include "texture/texture_png.h"
#include "texture/texture_jpg.h"
#include "texture/texture_tiff.h"
#include "texture/texture_pgm.h"
#include "texture/texture_tga.h"
#include "texture/texture_blp.h"
#include "texture/texture_pcx.h"
#include <iostream>

namespace sleek
{
    namespace loader
    {
        static std::shared_ptr<driver::mesh> debug(const std::shared_ptr<driver::mesh> &ptr, const char *filename)
        {
            std::cout << "Mesh \"" << filename << "\" ";
            if(ptr)
            {
                std::cout
                    << "\t triangle{" << ptr->indices.size() << "}"
                    << "\t attribut{" << ptr->datas.size() << "}"
                    << std::endl;
            }
            else
            {
                std::cout << "failed to load" << std::endl;
            }
            return ptr;
        }
        static std::shared_ptr<driver::texture> debug(const std::shared_ptr<driver::texture> &ptr, const char *filename)
        {
            std::cout << "Texture \"" << filename << "\" ";
            if(ptr)
            {
                std::cout
                    << "\t vec2{" << ptr->getDimension().x << ", " << ptr->getDimension().y << "}"
                    << "\t bits{" << ptr->getPitch()*8 << "}"
                    << std::endl;
            }
            else
            {
                std::cout << "failed to load" << std::endl;
            }
            return ptr;
        }

        loader::loader(std::shared_ptr<io::filesystem> f)
            : fs(f)
        {
            if(!fs)
            {
                std::cerr << "error >> loader with nullptr as filesystem" << std::endl;
            }
            else
            {
                mesh.push_back(new meshloader_3ds());
                mesh.push_back(new meshloader_txt());
                mesh.push_back(new meshloader_obj());

                texture.push_back(new textureloader_bmp());
                texture.push_back(new textureloader_png());
                texture.push_back(new textureloader_jpg());
                texture.push_back(new textureloader_tiff());
                texture.push_back(new textureloader_pgm());
                texture.push_back(new textureloader_tga());
                texture.push_back(new textureloader_blp());
                texture.push_back(new textureloader_pcx());
            }
        }
        loader::~loader()
        {
        }
        std::shared_ptr<driver::mesh> loader::loadMesh(const std::string &filename) const noexcept
        {
            for(auto e : mesh)
            {
                if(e->match(filename))
                {
                    auto file = fs->read(filename);
                    return file ? debug(e->read(file.get()), filename.c_str()) : nullptr;
                }
            }

            std::cout << "no matching loader for " << filename << std::endl;
            return nullptr;
        }
        std::shared_ptr<driver::texture> loader::loadTexture(const std::string &filename) const noexcept
        {
            for(auto e : texture)
            {
                if(e->match(filename))
                {
                    auto file = fs->read(filename);
                    return file ? debug(e->read(file.get()), filename.c_str()) : nullptr;
                }
            }

            std::cout << "no matching loader for " << filename << std::endl;
            return nullptr;
        }
        bool loader::writeMesh(std::shared_ptr<driver::mesh> data, const std::string &filename) const noexcept
        {
            if(!data)
                return false;

            for(auto e : mesh)
            {
                if(e->match(filename))
                {
                    auto file = fs->write(filename);
                    return file ? e->write(data.get(), file.get()) : false;
                }
            }

            return false;
        }
        bool loader::writeTexture(std::shared_ptr<driver::texture> data, const std::string &filename) const noexcept
        {
            if(!data)
                return false;

            for(auto e : texture)
            {
                if(e->match(filename))
                {
                    auto file = fs->write(filename);
                    return file ? e->write(data.get(), file.get()) : false;
                }
            }

            return false;
        }
    }
}
