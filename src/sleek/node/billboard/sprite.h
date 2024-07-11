#ifndef SPRITE
#define SPRITE

#include "billboard.h"
#include "math/timer.h"

namespace sleek
{
    namespace scene3d
    {
        namespace billboard
        {
            class Sprite : public Billboard
            {
                public:
                    Sprite(Scene*) noexcept;
                    Sprite(Scene*, std::vector<driver::texture*>) noexcept;

                    virtual void setTimer(const u32) noexcept; // ms
                    virtual void setArray(std::vector<driver::texture*>) noexcept;
                    virtual void setTexture(driver::texture*) noexcept;

                    virtual std::vector<driver::texture*> getArray() const noexcept;
                    virtual driver::texture *getTexture() const noexcept;
                    virtual u32 getTimer() const noexcept;

                    virtual void render() noexcept;
                private:
                    u32 timespec, current;
                    math::timer time_stamp;
                    std::vector<driver::texture*> anim;
            };
            
            std::vector<driver::texture*> cut_texture_to_array(driver::texture*, u32 width, u32 height, u32 lenght) noexcept;
        }
    }
}

#endif
