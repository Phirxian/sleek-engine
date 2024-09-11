#include "../interface.h"
#include "frame.h"

namespace sleek
{
    namespace gui
    {
        frame::frame(interface *m) noexcept : mom(m)
        {
            textsize = 11;
            parent = nullptr;
            show = true;
            isActive = false;
            ft2 = mom->getInternalFont();
            fontcache = nullptr;
        }

        frame::~frame() noexcept
        {
        }

        void frame::setFontCache(std::shared_ptr<driver::texture> i) noexcept
        {
            fontcache = i;
            if (i)
            {
                i->createIdentifier(mom->getDrawManager()->getContext().get());
                i->getIdentifier()->update();
                UpdateFontPos();
            }
        }

        std::shared_ptr<driver::texture> frame::getFontCache() const noexcept
        {
            return fontcache;
        }

        void frame::addChild(std::shared_ptr<frame> i) noexcept
        {
            child.push_back(i);
            i->relative = i->absolute;
            i->absolute = absolute+relative;
            i->parent = this;
        }

        void frame::removeChild(std::shared_ptr<frame> i) noexcept
        {
            for(auto it = child.begin() ; it != child.end(); ++it)
            {
                if(*it == i)
                {
                    child.erase(it);
                    break;
                }
            }
        }

        void frame::setFont(std::shared_ptr<font> i) noexcept
        {
            ft2 = i;
            if(text.size() > 0 && ft2)
                setFontCache(ft2->build(text, textsize));
            else
                setFontCache(nullptr);
        }

        void frame::setParent(frame *i) noexcept
        {
            parent = i;
            i->addChild(getptr());
        }

        void frame::setText(std::wstring t) noexcept
        {
            text = t;
            if(text.size() > 0 && ft2)
                setFontCache(ft2->build(text, textsize));
            else
                setFontCache(nullptr);
        }

        void frame::setTextColor(const math::pixel &c) noexcept
        {
            textcolor = c;
        }

        void frame::setTextSize(u32 c) noexcept
        {
            textsize = c;
            if(text.size() > 0 && ft2)
                setFontCache(ft2->build(text, textsize));
            else
                setFontCache(nullptr);
        }

        interface* frame::getGUIEnvironment() const noexcept
        {
            return mom;
        }

        frame* frame::getParent() const noexcept
        {
            return parent;
        }

        std::shared_ptr<frame> frame::getChild(s32 i) const noexcept
        {
            return child[i];
        }

        void frame::removeChild(s32 i) noexcept
        {
            child.erase(child.begin()+i);
        }

        void frame::removeAll() noexcept
        {
            child.clear();
        }

        void frame::setVisible(bool i) noexcept
        {
            show = i;
        }

        bool frame::isVisible() const noexcept
        {
            return show;
        }

        std::shared_ptr<font> frame::getFont() const noexcept
        {
            return ft2;
        }

        const std::wstring& frame::getText() const noexcept
        {
            return text;
        }

        math::pixel frame::getTextColor() const noexcept
        {
            return textcolor;
        }

        u32 frame::getTextSize() const noexcept
        {
            return textsize;
        }

        void frame::setSize(math::vec2i size) noexcept
        {
            box.setSizeFromUpperLeft(size);
        }
        
        void frame::move(math::vec2i p) noexcept
        {
            if(parent) relative = p;
            else absolute = p;
            UpdateAbsolutePosition();
            UpdateFontPos();
        }

        bool frame::manage(device::input* e) noexcept
        {
            for(u32 i = 0; i<child.size(); ++i)
                if(child[i]->manage(e))
                    return true;
            return false;
        }

        void frame::setScale(math::vec2i i) noexcept
        {
            box.setSizeFromUpperLeft(i);
        }

        math::aabbox2di& frame::getBoundingBox() noexcept
        {
            return box;
        }

        math::vec2i frame::getScale() const noexcept
        {
            return box.getSize();
        }

        void frame::render() noexcept
        {
            if(!show) return;
            mom->getTheme()->drawFrame(this);
            renderChild();
        }

        void frame::renderChild() noexcept
        {
            //! TODO inspect why grow(1)
            mom->getDrawManager()->pushScissor(box.grow(1));
            for(u32 i = 0; i<child.size(); ++i)
                child[i]->render();
            mom->getDrawManager()->popScissor();
        }

        void frame::UpdateAbsolutePosition() noexcept
        {
            if(parent)
                absolute = parent->absolute+parent->relative;

            math::vec2i size = box.getSize();
            box.setUpperLeft(absolute + relative);
            box.setSizeFromUpperLeft(size);
            UpdateChildPosition();
            UpdateFontPos();
        }

        void frame::UpdateChildPosition() noexcept
        {
            for(u32 i = 0; i<child.size(); ++i)
            {
                child[i]->UpdateAbsolutePosition();
                child[i]->UpdateFontPos();
            }
        }

        void frame::UpdateFontPos() noexcept
        {
            textpos = absolute+relative;
            textpos += box.getSize()/2;

            if(fontcache)
            {
                textpos.x -= fontcache->getDimension().x/2;
                textpos.y -= fontcache->getDimension().y/2 - 2;
            }
        }
    }
}
