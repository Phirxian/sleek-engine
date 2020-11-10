#include "texture_array.h"

namespace sleek
{
    namespace driver
    {
        static const unsigned int TextureFormatSize[] = {
            1, 2,  3,  4,
            4, 8, 12, 16
        };

        static const unsigned int TextureFormatComponant[] = {
            1, 2, 3, 4,
            1, 2, 3, 4
        };

        texture_array::texture_array(const math::vec2i &s, const TextureFormat p) noexcept
            : original(s), fmt(p)
        {
            pitch = TextureFormatSize[p-1];
            component = TextureFormatComponant[p-1];
        }

        texture_array::~texture_array() noexcept
        {
        }

        u8 texture_array::getComposantCount() const noexcept
        {
            component;
        }

        u8 texture_array::getPitch() const noexcept
        {
            pitch;
        }

        bool texture_array::push_back(std::shared_ptr<texture> tx) noexcept
        {
            if(tx->getDimension() != getDimension() ||
               tx->getFormat() != getFormat())
               return false;

            textures.push_back(tx);
            return true;
        }

        bool texture_array::insert(texture_store::iterator i, std::shared_ptr<texture> tx) noexcept
        {
            if(tx->getDimension() != getDimension() ||
               tx->getFormat() != getFormat())
               return false;

            textures.insert(i, tx);
            return true;
        }

        void texture_array::erase(texture_store::iterator i) noexcept
        {
            textures.erase(i);
        }

        u32 texture_array::count() noexcept
        {
            return textures.size();
        }

        math::vec2i texture_array::getDimension() const noexcept
        {
            return original;
        }

        math::pixel texture_array::getPixel(const math::vec2i &pos, int i) const noexcept
        {
            return textures[i]->getPixel(pos);
        }

        TextureFormat texture_array::getFormat() const noexcept
        {
            return fmt;
        }

        std::shared_ptr<identifier> texture_array::getIdentifier() const noexcept
        {
            return gpu;
        }

        u8* texture_array::getBuffer(int i) const noexcept
        {
            return textures[i]->getBuffer();
        }
    }
}
