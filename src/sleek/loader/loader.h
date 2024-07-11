#ifndef __LOADER__
#define __LOADER__

#include <vector>
#include <utility>

#include "ressource.h"

namespace sleek
{
    namespace loader
    {
        class loader : public std::enable_shared_from_this<loader>
        {
            public:
                loader(std::shared_ptr<io::filesystem>);
                virtual ~loader();

                inline std::shared_ptr<loader> getptr() noexcept
                {
                    return shared_from_this();
                }

                virtual std::shared_ptr<driver::mesh>    loadMesh(const std::string&) const noexcept;
                virtual std::shared_ptr<driver::texture> loadTexture(const std::string&) const noexcept;

                virtual bool writeMesh(std::shared_ptr<driver::mesh>, const std::string&) const noexcept;
                virtual bool writeTexture(std::shared_ptr<driver::texture>, const std::string&) const noexcept;
            public:
                std::shared_ptr<io::filesystem> fs;
                std::vector<std::pair<mimetype*, meshloader*>> rmesh;
                std::vector<std::pair<mimetype*, textureloader*>> rtexture;
                std::vector<std::pair<mimetype*, meshwriter*>> wmesh;
                std::vector<std::pair<mimetype*, texturewriter*>> wtexture;
        };
    }
}

#endif // __LOADER__
