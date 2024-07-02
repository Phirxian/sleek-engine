#include "interface.h"
#include "../driver/driver.h"
#include "theme.h"

#include "button.h"
#include "font.h"
#include "picture.h"
#include "progressbar.h"
#include "statictext.h"
#include "window.h"
#include "scrollbar.h"

namespace sleek
{
    namespace gui
    {
        static const math::pixel theme_color[] = {
            math::pixel( 25, 25, 25,128), // 0
            math::pixel(128,255,255,255),
            math::pixel( 25, 25, 25,100),
            math::pixel( 25, 25, 25,200),
            math::pixel(128, 25, 25,128), // 4
            math::pixel(  0,  0,255,255),
            math::pixel( 25, 25, 25,150),
            math::pixel(  0,255,  0,255),
            math::pixel( 25,128,255,128),
            math::pixel( 25, 25, 25,255), // 9
            math::pixel(255,255,255,255),
            math::pixel(  0,  0,  0,255)
        };

        theme::theme(interface *i) noexcept : mom(i)
        {
            solid = std::make_shared<driver::material>();
            solid->setMode(driver::rmd_quad);
            //solid->setMaterialRender(driver::rmt_solid);
            solid->setMaterialRender(driver::rmt_add);

            line = std::make_shared<driver::material>();
            line->setMode(driver::rmd_line_loop);
//            line->setMaterialRender(driver::rmt_solid);
            line->setMaterialRender(driver::rmt_add);
        }

        theme::~theme() noexcept
        {
        }

        void theme::drawFont(frame *i) const noexcept
        {
            auto cache = i->getFontCache();

            if(cache == nullptr)
                return;

            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawTexture(
                cache.get(), i->textpos,
                {0.f, 0.f, 0.f}, {1.f,1.f},
                i->getTextColor()
            );
        }

        void theme::drawWindowMain(window *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color[2 + i->isActive]);
        }

        void theme::drawWindowMainHovored(window *i) noexcept
        {
            drawWindowMain(i);
        }

        void theme::drawWindowMainMoved(window *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color[6]);
        }

        void theme::drawWindowDecoration(window *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color[1 + i->isActive*6]);

            // title s�parator

            math::vec2i a = i->box.getUpperLeft(),
                        b = i->box.getLowerRight();

            a.y += i->title_size;
            b.y = a.y;
            b.x -= 1;

            mom->getDrawManager()->drawLine(a, b, theme_color[1 + i->isActive*6]);
        }

        void theme::drawWindowDecorationHovored(window *i) noexcept
        {
            drawWindowDecoration(i);
        }

        void theme::drawWindowDecorationMoved(window *i) noexcept
        {
            drawWindowDecoration(i);
        }

        void theme::drawWindowTitle(window *i) noexcept
        {
        }

        void theme::drawWindowTitleHovored(window *i) noexcept
        {
        }

        void theme::drawWindowTitleMoved(window *i) noexcept
        {
        }

        void theme::drawButton(button *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color[0]);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color[1]);
        }

        void theme::drawButtonPushed(button *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color[4]);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color[9]);
        }

        void theme::drawButtonHovored(button *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color[8]);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color[5]);
        }

        void theme::drawStaticText(statictext *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(0,0,0), theme_color[0]);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(0,0,0), theme_color[1]);
            drawFont(i);
        }

        void theme::drawProgressbar(progressbar *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color[0]);
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color[4]);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color[1]);
        }

        void theme::drawScrollbar(scrollbar *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color[0]);

            if(i->getOrientation() == SBO_HORIZONTAL)
            {
                math::vec2i start = {
                    i->getBoundingBox().upperleft.x + 1 + (i->getBoundingBox().getSize().x-2) * i->getPercentage(),
                    i->getBoundingBox().upperleft.y
                };
                math::vec2i end = {start.x, i->getBoundingBox().lowerright.y};

                mom->getDrawManager()->drawLine({start.x-1, start.y}, {end.x-1, end.y}, theme_color[10]);
                mom->getDrawManager()->drawLine(start, end, theme_color[11]);
                mom->getDrawManager()->drawLine({start.x+1, start.y}, {end.x+1, end.y}, theme_color[10]);
            }
            else
            {
                math::vec2i start = {
                    i->getBoundingBox().upperleft.x, 
                    i->getBoundingBox().upperleft.y + 1 + (i->getBoundingBox().getSize().y-2) * i->getPercentage()
                };
                math::vec2i end = {i->getBoundingBox().lowerright.x, start.y};

                mom->getDrawManager()->drawLine({start.x, start.y-1}, {end.x, end.y-1}, theme_color[10]);
                mom->getDrawManager()->drawLine(start, end, theme_color[11]);
                mom->getDrawManager()->drawLine({start.x, start.y+1}, {end.x, end.y+1}, theme_color[10]);
            }

            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color[1]);
        }

        void theme::drawFrame(frame *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color[6]);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color[1]);
        }
    }
}
