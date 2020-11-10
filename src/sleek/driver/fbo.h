#pragma once

#include "../math/math.h"
#include "../math/pixel.h"
#include "identifier.h"
#include "texture.h"

#include <vector>

namespace sleek
{
    namespace driver
    {
        enum E_CLEAR_BIT
        {
            ECB_COLOR = 0x00004000,
            ECB_DEPTH = 0x00000100,
            ECB_ACCUM = 0x00000200
        };

        class fbo : public identifier
        {
            public:
                fbo(const math::vec2i &size, const std::vector<TextureFormat>&, bool depthbuffer = true) noexcept;
                virtual ~fbo() noexcept;

                virtual HARDWARE_IDENTIFIER_TYPE getType() const noexcept
                {
                    return HIT_FBO;
                }

                virtual void resize(const math::vec2i &size) noexcept;
                virtual math::vec2i getSize() const noexcept;

                virtual void setBackground(math::pixel c) { color = c; }
                virtual math::pixel getBackground() { return color; }

                virtual identifier* getTexture(int i) const noexcept { return textures[i]; }
                virtual unsigned    getTextureCount() const noexcept { return textures.size(); }

                virtual void* getHardwareLink() const noexcept = 0;

                //! @i is a bitfield of E_CLEAR_BIT
                virtual void bind(int i) noexcept = 0;
                virtual void bind() noexcept = 0;
            protected:
                math::pixel color;
                std::vector<identifier*> textures;
                std::vector<TextureFormat> attachment;
                math::vec2i size;
                bool usedepth;
        };
    }
}
