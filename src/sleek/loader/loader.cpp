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
                rmesh.push_back(new mesh_3ds());
                rmesh.push_back(new mesh_txt());
                rmesh.push_back(new mesh_obj());

                wmesh.push_back(new mesh_obj());

                rtexture.push_back(new texture_blp());
                rtexture.push_back(new texture_bmp());
                rtexture.push_back(new texture_jpg());
                rtexture.push_back(new texture_pcx());
                rtexture.push_back(new texture_pgm());
                rtexture.push_back(new texture_png());
                rtexture.push_back(new texture_tga());
                rtexture.push_back(new texture_tiff());

                wtexture.push_back(new texture_blp());
                wtexture.push_back(new texture_bmp());
                wtexture.push_back(new texture_jpg());
                wtexture.push_back(new texture_pcx());
                wtexture.push_back(new texture_pgm());
                wtexture.push_back(new texture_png());
                wtexture.push_back(new texture_tga());
                // unsupported
                //wtexture.push_back(new texture_tiff());
            }
        }
        loader::~loader()
        {
        }
        std::shared_ptr<driver::mesh> loader::loadMesh(const std::string &filename) const noexcept
        {
            for(auto e : rmesh)
            {
                if(e->match(filename))
                {
                    auto loader = (meshloader*)e;
                    auto file = fs->read(filename);
                    return file ? debug(loader->read(file.get()), filename.c_str()) : nullptr;
                }
            }

            std::cout << "no matching loader for " << filename << std::endl;
            return nullptr;
        }
        std::shared_ptr<driver::texture> loader::loadTexture(const std::string &filename) const noexcept
        {
            for(auto e : rtexture)
            {
                if(e->match(filename))
                {
                    auto loader = (textureloader*)e;
                    auto file = fs->read(filename);
                    return file ? debug(loader->read(file.get()), filename.c_str()) : nullptr;
                }
            }

            std::cout << "no matching loader for " << filename << std::endl;
            return nullptr;
        }
        bool loader::writeMesh(std::shared_ptr<driver::mesh> data, const std::string &filename) const noexcept
        {
            if(!data)
                return false;

            for(auto e : wmesh)
            {
                if(e->match(filename))
                {
                    auto writer = (meshwriter*)e;
                    auto file = fs->write(filename);
                    return file ? writer->write(data.get(), file.get()) : false;
                }
            }

            return false;
        }
        bool loader::writeTexture(std::shared_ptr<driver::texture> data, const std::string &filename) const noexcept
        {
            if(!data)
                return false;

            for(auto e : wtexture)
            {
                if(e->match(filename))
                {
                    auto writer = (texturewriter*)e;
                    auto file = fs->write(filename);
                    return file ? writer->write(data.get(), file.get()) : false;
                }
            }

            return false;
        }
    }
}
