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
        static auto theme_color_bg = math::pixel(24, 28, 47, 255);
        static auto theme_color_fg = math::pixel(37, 45, 65, 255);
        static auto theme_color_hover = math::pixel(24, 47, 45, 255);
        static auto theme_color_border = math::pixel(8, 8, 18, 255);

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
                {0.f, 0.f, 0.f}, {1.f, 1.f},
                i->getTextColor()
            );
        }

        void theme::drawWindowMain(window *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color_bg);
        }

        void theme::drawWindowMainHovored(window *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color_fg);
        }

        void theme::drawWindowMainMoved(window *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color_fg);
        }

        void theme::drawWindowDecoration(window *i) noexcept
        {
            math::vec2i a = i->box.getUpperLeft(),
                        b = i->box.getLowerRight();

            b.y = a.y + i->title_size;

            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube({a, b}, {0, 0, 0}, theme_color_bg);

            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube({a, b}, {0, 0, 0}, theme_color_border);
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
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_bg);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_border);
        }

        void theme::drawButtonPushed(button *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_fg);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_border);
        }

        void theme::drawButtonHovored(button *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_border);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_fg);
        }

        void theme::drawStaticText(statictext *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(0,0,0), theme_color_bg);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(0,0,0), theme_color_border);
        }

        void theme::drawProgressbar(progressbar *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_bg);

            float alpha = i->getPercentage();
            math::aabbox2di pos = i->box;
            pos.lowerright.x = (1-alpha)*i->box.upperleft.x + alpha*i->box.lowerright.x;

            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(pos, math::vec3f(), theme_color_fg);

            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_border);
        }

        void theme::drawScrollbar(scrollbar *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color_bg);

            if(i->getOrientation() == SBO_HORIZONTAL)
            {
                math::vec2i start = {
                    i->getBoundingBox().upperleft.x + 1 + (i->getBoundingBox().getSize().x-2) * i->getPercentage(),
                    i->getBoundingBox().upperleft.y
                };
                math::vec2i end = {start.x, i->getBoundingBox().lowerright.y};

                mom->getDrawManager()->drawLine({start.x-1, start.y}, {end.x-1, end.y}, theme_color_border);
                mom->getDrawManager()->drawLine(start, end, theme_color_hover);
                mom->getDrawManager()->drawLine({start.x+1, start.y}, {end.x+1, end.y}, theme_color_border);
            }
            else
            {
                math::vec2i start = {
                    i->getBoundingBox().upperleft.x, 
                    i->getBoundingBox().upperleft.y + 1 + (i->getBoundingBox().getSize().y-2) * i->getPercentage()
                };
                math::vec2i end = {i->getBoundingBox().lowerright.x, start.y};

                mom->getDrawManager()->drawLine({start.x, start.y-1}, {end.x, end.y-1}, theme_color_border);
                mom->getDrawManager()->drawLine(start, end, theme_color_hover);
                mom->getDrawManager()->drawLine({start.x, start.y+1}, {end.x, end.y+1}, theme_color_border);
            }

            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color_border);
        }

        void theme::drawFrame(frame *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color_bg);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_border);
        }
    }
}
