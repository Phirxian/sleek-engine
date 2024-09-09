#include "colorpicker.h"

#include "interface.h"
#include "scrollbar.h"
#include "button.h"

#include "../driver/texture.h"
#include "../math/math.h"
#include "../math/function.h"

#include <iostream>

namespace sleek
{
    namespace gui
    {
        colorpicker::colorpicker(interface *guienv) noexcept
            : frame(guienv), background{64, 255, 255, 255}, white{255, 255, 255, 255}, black{0, 0, 0, 255},
              isGradient(false), isColor(false)
        {
            close = guienv->addButton("take this color", {5, 140, 85, 156});
            close->setParent(this);

            scroll = guienv->addScrollbar(true, {5, 125, 85, 135});
            scroll->setParent(this);
            scroll->setMin(0);
            scroll->setMax(255);
            scroll->setPercentage(0.5);

            createAlphaTexture();
            createGradientTexture();

            colorpos = 0;
            color = img[1]->getPixel({0, 0});
            recalculatePickedColor();

            setPickedColor({255, 64, 64, 128});
        }
        colorpicker::~colorpicker() noexcept
        {
        }
        void colorpicker::createAlphaTexture() noexcept
        {
            img[0] = std::make_shared<driver::texture>(math::vec2i{16, 16}, driver::TXFMT_RGB);
            math::pixel color;

            #define square(colorstart, sx, sy, sz, sw)    \
                color = colorstart;                       \
                for(int y=sy; y<sw; ++y)                  \
                    for(int x=sx; x<sz; ++x)              \
                        img[0]->setPixel({x, y}, color);  \

            square(math::pixel(153, 153, 153), 0, 0,  8,  8);
            square(math::pixel(153, 153, 153), 8, 8, 16, 16);
            square(math::pixel(102, 102, 102), 8, 0, 16,  8);
            square(math::pixel(102, 102, 102), 0, 8,  8, 16);

            #undef square

            img[0]->createIdentifier(mom->getDrawManager()->getContext().get());
            img[0]->getIdentifier()->update();
        }
        void colorpicker::createGradientTexture() noexcept
        {
            auto size = math::vec2i{1, 150};
            img[1] = std::make_shared<driver::texture>(size, driver::TXFMT_RGBA);

            auto interpolate = [this, size](math::pixel from, math::pixel to, int start, int end)
            {
                for (int y = start; y < end; ++y)
                {
                    math::pixel c = to.getInterpolated(from, (y - start) / static_cast<float>(end - start));
                    for (int x = 0; x < size.x; ++x)
                        img[1]->setPixel({x, y}, c);
                }
            };

            interpolate(math::pixel(255, 0, 0), math::pixel(255, 0, 255), 0, 25);
            interpolate(math::pixel(255, 0, 255), math::pixel(0, 0, 255), 25, 50);
            interpolate(math::pixel(0, 0, 255), math::pixel(0, 255, 255), 50, 75);
            interpolate(math::pixel(0, 255, 255), math::pixel(0, 255, 0), 75, 100);
            interpolate(math::pixel(0, 255, 0), math::pixel(255, 255, 0), 100, 125);
            interpolate(math::pixel(255, 255, 0), math::pixel(255, 0, 0), 125, 150);

            img[1]->createIdentifier(mom->getDrawManager()->getContext().get());
            img[1]->getIdentifier()->update();
        }
        void colorpicker::setScale(math::vec2i i) noexcept
        {
            colorpicker::setScale({110, 160});
        }
        bool colorpicker::manage(device::input *e) noexcept
        {
            math::vec2i pos(e->mouse_pos);

            if(e->type == device::EVENT_MOUSSE_DOWN)
            {
                isGradient = gradient.intersect(pos);
                isColor = colorbox.intersect(pos);
                isInside = box.intersect(pos);
            }

            if(e->type == device::EVENT_MOUSSE_UP)
                isGradient = isColor = false;

            if(isGradient)
            {
                if(pos.x < gradient.upperleft.x)
                    pos.x = gradient.upperleft.x;
                if(pos.y < gradient.upperleft.y)
                    pos.y = gradient.upperleft.y;

                if(pos.x > gradient.lowerright.x)
                    pos.x = gradient.lowerright.x;
                if(pos.y > gradient.lowerright.y)
                    pos.y = gradient.lowerright.y;

                colorpos = std::min(pos.y - gradient.upperleft.y, img[1]->getDimension().y-1);
                color = img[1]->getPixel({0, colorpos});
                recalculatePickedColor();
            }

            if(isColor)
            {
                if(pos.x < colorbox.upperleft.x)
                    pos.x = colorbox.upperleft.x;
                if(pos.y < colorbox.upperleft.y)
                    pos.y = colorbox.upperleft.y;

                if(pos.x > colorbox.lowerright.x)
                    pos.x = colorbox.lowerright.x;
                if(pos.y > colorbox.lowerright.y)
                    pos.y = colorbox.lowerright.y;

                pickpos.x = pos.x - colorbox.upperleft.x;
                pickpos.y = pos.y - colorbox.upperleft.y;
                recalculatePickedColor();
            }

            if(isGradient || isColor)
            {
                e->gui.called = this;
                e->gui.type = gui::IGT_COLORPICKER;
                e->gui.code = gui::IET_COLORPICKER_UPDATED;
                return true;
            }

            if(frame::manage(e))
            {
                switch(e->gui.code)
                {
                    case IET_BUTTON_CLICKED:
                        e->gui.called = this;
                        e->gui.type = gui::IGT_COLORPICKER;
                        e->gui.code = gui::IET_COLORPICKER_SELECTED;
                    break;
                    case IET_SCROLLBAR_UPDATED:
                        recalculatePickedColor();
                        e->gui.called = this;
                        e->gui.type = gui::IGT_COLORPICKER;
                        e->gui.code = gui::IET_COLORPICKER_UPDATED;
                    break;
                }
                return true;
            }

            return false;
        }
        void colorpicker::recalculatePickedColor() noexcept
        {
            math::pixel hcolor = color.getInterpolated(white, pickpos.x/80.f);

            pickcolor = black.getInterpolated(hcolor, pickpos.y/80.f);
            pickcolor.setAlpha(scroll->getValue());

            alpha = color;
            alpha.setAlpha(0);
        }
        void colorpicker::setPickedColor(const math::pixel &c) noexcept
        {
            pickcolor = c;

            math::vec3f hsv = c.HSV();

            colorpos = 150-hsv.x/360.f*150.f;
            pickpos.x = hsv.y*80.f;
            pickpos.y = 80-(hsv.z)*80.f;

            color = img[1]->getPixel({0, colorpos});
            color.setAlpha(255);

            alpha = color;
            alpha.setAlpha(0);
        }
        const math::pixel& colorpicker::getPickedColor() const noexcept
        {
            return pickcolor;
        }
        void colorpicker::setBackgroundColor(const math::pixel &b) noexcept
        {
            background = b;
        }
        const math::pixel& colorpicker::getBackgroundColor() const noexcept
        {
            return background;
        }
        void colorpicker::UpdateAbsolutePosition() noexcept
        {
            frame::UpdateAbsolutePosition();

            colorbox.upperleft = box.upperleft;
            colorbox.lowerright = box.upperleft;
            colorbox.upperleft.x += 5;
            colorbox.upperleft.y += 5;
            colorbox.lowerright.x += 85;
            colorbox.lowerright.y += 85;

            gradient.upperleft = box.upperleft;
            gradient.lowerright = box.upperleft;
            gradient.upperleft.x += 90;
            gradient.upperleft.y += 5;
            gradient.lowerright.x += 105;
            gradient.lowerright.y += 155;

            pickbox.upperleft = box.upperleft;
            pickbox.lowerright = box.upperleft;
            pickbox.upperleft.x += 5;
            pickbox.upperleft.y += 90;
            pickbox.lowerright.x += 85;
            pickbox.lowerright.y += 120;
        }
        void colorpicker::render() noexcept
        {
            if(!show) return;

            frame::render();

            mom->getDrawManager()->setActiveMaterial(mom->getTheme()->getSolidMaterial());
            // draw the background
            mom->getDrawManager()->drawCube(colorbox, {0, 0, 0}, black);
            //mom->getDrawManager()->drawCube(colorbox, {0, 0, 0}, white, color, black, black);
            mom->getDrawManager()->drawCube(colorbox, {0, 0, 0}, white, color, alpha, alpha);
            
            mom->getDrawManager()->drawTextureScale(
                img[1].get(),
                {box.upperleft.x+90, box.upperleft.y+5},
                {0, 0, 0},
                {15, 150, 0},
                {1.f, 1.f}
            );

            // right vertical texture
            //mom->getDrawManager()->drawTexture(img[1].get(), {
            //    box.upperleft.x+90,
            //    box.upperleft.y+5
            //});

            {
                const math::vec2i start =  {box.upperleft.x+90,  box.upperleft.y+5+colorpos};
                const math::vec2i end =    {box.upperleft.x+105, box.upperleft.y+5+colorpos};
                const math::vec2i hstart = {colorbox.upperleft.x,     colorbox.upperleft.y+pickpos.y};
                const math::vec2i hend =   {colorbox.lowerright.x,    colorbox.upperleft.y+pickpos.y};
                const math::vec2i vstart = {colorbox.upperleft.x+pickpos.x, colorbox.upperleft.y};
                const math::vec2i vend =   {colorbox.upperleft.x+pickpos.x, colorbox.lowerright.y};

                mom->getDrawManager()->drawLine({ start.x,    start.y-1}, { end.x,    end.y-1}, white);
                mom->getDrawManager()->drawLine({ start.x,    start.y+1}, { end.x,    end.y+1}, white);
                mom->getDrawManager()->drawLine({hstart.x,   hstart.y-1}, {hend.x,   hend.y-1}, white);
                mom->getDrawManager()->drawLine({hstart.x,   hstart.y+1}, {hend.x,   hend.y+1}, white);
                mom->getDrawManager()->drawLine({vstart.x-1,   vstart.y}, {vend.x-1, vend.y  }, white);
                mom->getDrawManager()->drawLine({vstart.x+1,   vstart.y}, {vend.x+1, vend.y  }, white);

                mom->getDrawManager()->drawLine(start,   end, black);
                mom->getDrawManager()->drawLine(hstart, hend, black);
                mom->getDrawManager()->drawLine(vstart, vend, black);
            }

            auto scl = pickbox.getSize();
            auto pickbox_a = pickbox;
            auto pickbox_b = pickbox;

            pickbox_a.lowerright.y = pickbox_a.upperleft.y + scl.y/2;
            pickbox_b.upperleft.y = pickbox_b.lowerright.y - scl.y/2;

            // chessboard texture
            mom->getDrawManager()->drawTextureScale(
                img[0].get(), pickbox.upperleft, {0, 0, 0},
                {scl.x, scl.y, 0}, {scl.x/16.f, scl.y/16.f}
            );

            mom->getDrawManager()->drawCube(
                pickbox_a, {0, 0, 0}, {pickcolor.red, pickcolor.green, pickcolor.blue, 255}
            );

            mom->getDrawManager()->drawCube(
                pickbox_b, {0, 0, 0}, pickcolor
            );
        }
    }
}
