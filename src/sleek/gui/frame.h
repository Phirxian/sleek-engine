#ifndef GUI_FRAME
#define GUI_FRAME

#include "font.h"
#include "type.h"
#include "../compile.h"
#include "../driver/texture.h"
#include "../driver/material.h"
#include "../device/event.h"
#include "../reference.h"

namespace sleek
{
    namespace gui
    {
        class interface;
        class frame : public reference, public std::enable_shared_from_this<frame>
        {
            public:
                frame(interface*) noexcept;
                virtual ~frame() noexcept;

                virtual INTERFACE_GUI_CODE getType() const noexcept { return IGT_FRAME; }

                inline std::shared_ptr<frame> getptr() noexcept
                {
                    return std::enable_shared_from_this<frame>::shared_from_this();
                }

                virtual void addChild(std::shared_ptr<frame>) noexcept;
                virtual void removeChild(std::shared_ptr<frame>) noexcept;
                virtual void removeChild(s32) noexcept;
                virtual void removeAll() noexcept;

                virtual std::shared_ptr<frame> getChild(s32) const noexcept;

                virtual void setFont(std::shared_ptr<font>) noexcept;
                virtual void setVisible(bool) noexcept;
                virtual void setParent(frame*) noexcept;
                virtual void setText(std::wstring) noexcept;
                virtual void setTextSize(u32) noexcept;
                virtual void setTextColor(const math::pixel&) noexcept;
                virtual void setScale(math::vec2i) noexcept;

                virtual interface* getGUIEnvironment() const noexcept;

                virtual math::aabbox2di& getBoundingBox() noexcept;
                virtual math::vec2i getScale() const noexcept;
                virtual const std::wstring& getText() const noexcept;
                virtual frame* getParent() const noexcept;
                virtual std::shared_ptr<font> getFont() const noexcept;
                virtual math::pixel getTextColor() const noexcept;
                virtual u32 getTextSize() const noexcept;
                virtual bool isVisible() const noexcept;

                virtual void setFontCache(std::shared_ptr<driver::texture>) noexcept;
                std::shared_ptr<driver::texture> getFontCache() const noexcept;

                virtual void setSize(math::vec2i) noexcept;
                virtual void move(math::vec2i) noexcept;
                virtual bool manage(device::input*) noexcept;

                void* user[gui_frame_userdata];

                virtual void UpdateAbsolutePosition() noexcept;
                virtual void UpdateChildPosition() noexcept;
                virtual void UpdateFontPos() noexcept;

                virtual void renderChild() noexcept;
                virtual void render() noexcept;
            protected:
                frame() noexcept {}

                std::shared_ptr<font> ft2;
                std::shared_ptr<driver::texture> fontcache;
                
                frame* parent;
                interface *mom;

                bool show, isActive;
                math::vec2i relative, absolute, textpos;
                math::aabbox2di box;

                std::wstring text;
                math::pixel textcolor;
                u32 textsize;
            private:
                friend class window;
                friend class theme;
                friend class interface;
                std::vector<std::shared_ptr<frame>> child;
        };
    }
}

#endif
