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
        static auto theme_color_fg = math::pixel(24, 28, 47, 255);
        static auto theme_color_bg = math::pixel(37, 45, 65, 200);
        static auto theme_color_ligth = math::pixel(124, 147, 145, 255);
        static auto theme_color_hover = math::pixel(24, 47, 45, 255);
        static auto theme_color_border = math::pixel(8, 8, 18, 255);

        theme::theme(interface *i) noexcept : mom(i)
        {
            add = std::make_shared<driver::material>();
            add->setMode(driver::rmd_quad);
            add->setMaterialRender(driver::rmt_add);

            solid = std::make_shared<driver::material>();
            solid->setMode(driver::rmd_quad);
            //solid->setMaterialRender(driver::rmt_solid);
            //solid->setMaterialRender(driver::rmt_add);

            line = std::make_shared<driver::material>();
            line->setMode(driver::rmd_line_loop);
            line->setWireframe(true);
            line->setPointSize(2);
            line->setMaterialRender(driver::rmt_solid);
            //line->setMaterialRender(driver::rmt_add);
        }

        theme::~theme() noexcept
        {
        }

        void theme::drawFont(frame *i) const noexcept
        {
            auto cache = i->getFontCache();

            if(cache == nullptr)
                return;

            mom->getDrawManager()->setActiveMaterial(add);
            mom->getDrawManager()->drawTexture(
                cache.get(), i->textpos,
                {0.f, 0.f, 0.f}, {1.f, 1.f},
                i->getTextColor()
            );
            mom->getDrawManager()->setActiveMaterial(solid);
        }

        void theme::drawWindowMain(window *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color_bg);
        }

        void theme::drawWindowDecoration(window *i) noexcept
        {
            math::vec2i a = i->box.getUpperLeft(),
                        b = i->box.getLowerRight();

            b.y = a.y + i->title_size;

            mom->getDrawManager()->setActiveMaterial(solid);

            if (i->isMoved)
                mom->getDrawManager()->drawCube({a, b}, {0, 0, 0}, theme_color_border);
            else if (i->isActive)
                mom->getDrawManager()->drawCube({a, b}, {0, 0, 0}, theme_color_hover);
            else
                mom->getDrawManager()->drawCube({a, b}, {0, 0, 0}, theme_color_fg);

            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube({a, b}, {0, 0, 0}, theme_color_border);

            if (!i->isCollapsed)
                mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color_border);
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
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_fg);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_border);
        }

        void theme::drawButtonPushed(button *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_border);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_bg);
        }

        void theme::drawButtonHovored(button *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_hover);
            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_border);
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
            mom->getDrawManager()->drawCube(pos, math::vec3f(), theme_color_ligth);

            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(i->box, math::vec3f(), theme_color_border);
        }

        void theme::drawScrollbar(scrollbar *i) noexcept
        {
            mom->getDrawManager()->setActiveMaterial(solid);
            mom->getDrawManager()->drawCube(i->box, {0, 0, 0}, theme_color_ligth);

            auto size = i->getBoundingBox().getSize();
            auto box = i->getBoundingBox();

            if(i->getOrientation() == SBO_HORIZONTAL)
            {
                box.upperleft.x += size.y;
                box.lowerright.x -= size.y;
                size.x -= 2*size.y-4;

                math::vec2i start = {
                    box.upperleft.x + 1 + (size.x-2) * i->getPercentage(),
                    box.upperleft.y
                };
                math::vec2i end = {start.x, box.lowerright.y};

                mom->getDrawManager()->drawLine({start.x-1, start.y}, {end.x-1, end.y}, theme_color_border);
                mom->getDrawManager()->drawLine(start, end, theme_color_hover);
                mom->getDrawManager()->drawLine({start.x+1, start.y}, {end.x+1, end.y}, theme_color_border);
            }
            else
            {
                box.upperleft.y += size.x;
                box.lowerright.y -= size.x;
                size.y -= 2*size.x-4;

                math::vec2i start = {
                    box.upperleft.x, 
                    box.upperleft.y + 1 + (size.y-2) * i->getPercentage()
                };
                math::vec2i end = {box.lowerright.x, start.y};

                mom->getDrawManager()->drawLine({start.x, start.y-1}, {end.x, end.y-1}, theme_color_border);
                mom->getDrawManager()->drawLine(start, end, theme_color_hover);
                mom->getDrawManager()->drawLine({start.x, start.y+1}, {end.x, end.y+1}, theme_color_border);
            }

            mom->getDrawManager()->setActiveMaterial(line);
            mom->getDrawManager()->drawCube(box, {0, 0, 0}, theme_color_border);
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
