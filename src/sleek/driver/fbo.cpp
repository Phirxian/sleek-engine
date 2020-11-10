#include "fbo.h"

namespace sleek
{
    namespace driver
    {
        fbo::fbo(const math::vec2i &i, const std::vector<TextureFormat> &a, bool depthbuffer) noexcept
            : identifier(0), size(i), attachment(a), usedepth(depthbuffer)
        {
        }

        fbo::~fbo() noexcept
        {
        }

        void fbo::resize(const math::vec2i &s) noexcept
        {
            size = s;
        }

        math::vec2i fbo::getSize() const noexcept
        {
            return size;
        }
    }
}
