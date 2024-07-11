#include "../scene.h"
#include "sprite.h"

namespace sleek
{
    namespace scene3d
    {
        namespace billboard
        {
            Sprite::Sprite(Scene *smgr) noexcept : Billboard(smgr)
            {
                mat->Texture.push_back(nullptr);
                timespec = 100;
                current = 0;
            }

            Sprite::Sprite(Scene *smgr, std::vector<driver::texture*> i) noexcept : Billboard(smgr)
            {
                mat->Texture.push_back(nullptr);
                timespec = 100;
                current = 0;
            }

            /** ************************* **/

            void Sprite::setTimer(const u32 i) noexcept
            {
                timespec = i;
            }

            void Sprite::setArray(std::vector<driver::texture*> i) noexcept
            {
                anim = i;
                current = 0;
            }

            void Sprite::setTexture(driver::texture *i) noexcept
            {
                anim.push_back(i);
            }

            /** ************************* **/

            std::vector<driver::texture*> Sprite::getArray() const noexcept
            {
                return anim;
            }

            driver::texture *Sprite::getTexture() const noexcept
            {
                return anim[current];
            }

            u32 Sprite::getTimer() const noexcept
            {
                return timespec;
            }

            /** ************************* **/

            void Sprite::render() noexcept
            {
                if(!enabled)
                    return;

                time_stamp.update();
                
                if(time_stamp.getTimeMsec() > timespec)
                {
                    current += time_stamp.getTimeMsec()/timespec; // sync ( ex: time_stamp = 500, timespec = 100; 500/100 = 5; frame += 5 so frame skipped = 5
                    mat->Texture[0] = anim[current % anim.size()]->getIdentifier().get();
                    time_stamp.reset();
                }

                Billboard::render();
            }
        }
    }
}
