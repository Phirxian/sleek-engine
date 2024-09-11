#include "interface.h"
#include "font/font-ttf.h"

#include "element/button.h"
#include "element/checkbox.h"
#include "element/colorpicker.h"
#include "element/statictext.h"
#include "element/progressbar.h"
#include "element/scrollbar.h"
#include "element/picture.h"
#include "element/window.h"

#include <algorithm>

namespace sleek
{
    namespace gui
    {
        std::shared_ptr<interface> createGUIEnvironment(std::shared_ptr<device::Device> screen, std::shared_ptr<driver::driver> drawer) noexcept
        {
            return std::make_shared<interface>(screen, drawer);
        }

        interface::interface(std::shared_ptr<device::Device> s, std::shared_ptr<driver::driver> d) noexcept : screen(s), mom(d)
        {
            cr = std::make_shared<cursor>(this);
            //internal = std::make_shared<font>(this, nullptr, 0);
            internal = std::make_shared<font_ttf>(this, "font/Raleway-Regular.ttf");
            icons = std::make_shared<font_ttf>(this, "font/FontAwesome.ttf");
            interne = std::make_shared<theme>(this);
            custom = interne;
        }

        interface::~interface() noexcept
        {
            clear();
        }

        std::shared_ptr<frame> interface::addFrame(const std::wstring &t, const math::aabbox2di &b) noexcept
        {
            auto tmp = std::make_shared<frame>(this);
            tmp->absolute = b.upperleft;
            tmp->box = b.minimise();
            tmp->setText(t);
            return tmp;
        }

        std::shared_ptr<checkbox> interface::addCheckbox(const std::wstring &text, const math::aabbox2di &b) noexcept
        {
            auto tmp = std::make_shared<checkbox>(this);
            tmp->absolute = b.upperleft;
            tmp->box = b.minimise();
            tmp->setText(text);
            return tmp;
        }

        std::shared_ptr<colorpicker> interface::addColorPicker(const math::aabbox2di &b) noexcept
        {
            auto tmp = std::make_shared<colorpicker>(this);
            tmp->absolute = b.upperleft;
            tmp->box = b.minimise();
            return tmp;
        }

        std::shared_ptr<picture> interface::addPicture(std::shared_ptr<driver::texture> w, const std::wstring &t, const math::aabbox2di &b) noexcept
        {
            auto tmp = std::make_shared<picture>(this);
            tmp->absolute = b.upperleft;
            tmp->box = b.minimise();
            tmp->setTexture(w);
            tmp->setText(t);
            return tmp;
        }

        std::shared_ptr<scrollbar> interface::addScrollbar(bool horizontal, const math::aabbox2di &pos) noexcept
        {
            auto tmp = std::make_shared<scrollbar>(this);

            if(horizontal)
                tmp->setOrientation(SBO_HORIZONTAL);
            else
                tmp->setOrientation(SBO_VERTICAL);

            tmp->absolute = pos.upperleft;
            tmp->box = pos.minimise();
            return tmp;
        }

        std::shared_ptr<progressbar> interface::addProgressbar(const std::wstring &t, const math::aabbox2di &b) noexcept
        {
            auto tmp = std::make_shared<progressbar>(this);
            tmp->absolute = b.upperleft;
            tmp->box = b.minimise();
            tmp->setText(t);
            return tmp;
        }

        std::shared_ptr<button> interface::addButton(const std::wstring &t, const math::aabbox2di &b) noexcept
        {
            auto tmp = std::make_shared<button>(this);
            tmp->absolute = b.upperleft;
            tmp->box = b.minimise();
            tmp->setText(t);
            return tmp;
        }

        std::shared_ptr<statictext> interface::addStaticText(const std::wstring &t, const math::aabbox2di &b) noexcept
        {
            auto tmp = std::make_shared<statictext>(this);
            tmp->absolute = b.upperleft;
            tmp->box = b.minimise();
            tmp->setText(t);
            return tmp;
        }

        std::shared_ptr<window> interface::addWindow(const std::wstring &t, const math::aabbox2di &b) noexcept
        {
            auto tmp = std::make_shared<window>(this);
            tmp->absolute = b.upperleft;
            tmp->box = b.minimise();
            tmp->setTextSize(11);
            tmp->setText(t);
            tmp->box = b;
            return tmp;
        }

        void interface::addCustomFrame(std::shared_ptr<frame> tmp) noexcept
        {
            tmp->move(tmp->absolute);
            gui.push_back(tmp);
        }

        /** ******************************************** **/

        std::shared_ptr<theme> interface::getTheme() const noexcept
        {
            return custom;
        }


        std::shared_ptr<font> interface::getIconsFont() const noexcept
        {
            return icons;
        }

        std::shared_ptr<font> interface::getInternalFont() const noexcept
        {
            return internal;
        }

        std::shared_ptr<font> interface::getFont(const std::string &file) noexcept
        {
            for(int i = 0; i<fontcache.size(); ++i)
                if(fontcache[i]->getFilename() == file)
                    return fontcache[i];

            auto tmp = std::make_shared<font_ttf>(this, file);
            fontcache.push_back(tmp);

            return tmp;
        }

        void interface::unActiveElement() noexcept
        {
            for(u32 a = 0; a<gui.size(); ++a)
                gui[a]->isActive = false;
        }

        bool interface::manage(device::input *a) noexcept
        {
            if(!a)
                return false;

            cr->manage(a);

            // disable current if no event was captured before
            // might be override later
            if (a->type == device::EVENT_MOUSSE_UP && a->mouse[device::MOUSE_LEFT])
                setActiveFrame(nullptr);

            for(u32 i = 0; i<gui.size(); ++i)
            {
                if(gui[gui.size()-i-1]->manage(a))
                {
                    //std::cout << "event fired by " << gui[gui.size()-i-1]->getType() << std::endl;
                    return true;
                }
            }

            // active element might capture the event
            if (active && active->manage(a))
                return true;

            return false;
        }

        void interface::setActiveFrame(frame *_active) noexcept
        {
            active = _active;
        }

        frame* interface::getActiveFrame() noexcept
        {
            return active;
        }

        void interface::popFrame(std::shared_ptr<frame> i) noexcept
        {
            if(*gui.rbegin() == i)
                return;

            for(auto it = gui.begin(); it != gui.end(); ++it)
            {
                if(*it == i)
                {
                    (*it).reset();
                    gui.erase(it);
                    break;
                }
            }

            gui.push_back(i);
        }

        void interface::ActiveElement(std::shared_ptr<frame> i) noexcept
        {
            unActiveElement();
            popFrame(i);
            i->isActive = true;
        }

        void interface::removeFrame(std::shared_ptr<frame> i) noexcept
        {
            gui.erase(
                std::remove_if(
                    gui.begin(), gui.end(),
                    [&i](const std::shared_ptr<frame> &it){
                        return it == i;
                    }
                )
            );
        }

        void interface::removeFrame(const s32 i) noexcept
        {
            removeFrame(gui[i]);
        }

        void interface::popFrame(const s32 i) noexcept
        {
            popFrame(gui[i]);
        }

        void interface::clear() noexcept
        {
            gui.clear();
        }

        std::shared_ptr<driver::driver> interface::getDrawManager() const noexcept
        {
            return mom;
        }

        std::shared_ptr<device::Device> interface::getDevice() const noexcept
        {
            return screen;
        }

        std::shared_ptr<cursor> interface::getCursor() const noexcept
        {
            return cr;
        }

        void interface::render() noexcept
        {
            auto mat = std::make_shared<driver::material>();
            //mat->setMaterialRender(driver::rmt_add);
            mom->setActiveMaterial(mat);
            mom->beginTo2D();

            for(u32 i = 0; i<gui.size(); ++i)
            {
                gui[i]->render();
                mom->clearScissor();
            }
            
            cr->render();

            mom->endFrom2D();
        }
    }
}
