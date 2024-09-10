#ifndef INTERFACE
#define INTERFACE

#include "font.h"
#include "frame.h"
#include "theme.h"
#include "cursor.h"
#include "../driver/fbo.h"

namespace sleek
{
    namespace gui
    {
        class colorpicker;
        class picture;
        class scrollbar;
        class progressbar;
        class button;
        class statictext;
        class window;

        class interface : public std::enable_shared_from_this<interface>
        {
            public:
                interface(std::shared_ptr<device::Device> screen, std::shared_ptr<driver::driver> drawer) noexcept;
                virtual ~interface() noexcept;

                inline std::shared_ptr<interface> getptr() noexcept
                {
                    return shared_from_this();
                }

                std::shared_ptr<frame>       addFrame(const std::wstring &text = L"", const math::aabbox2di &pos = math::aabbox2di()) noexcept;
                std::shared_ptr<colorpicker> addColorPicker(const math::aabbox2di &b) noexcept;
                std::shared_ptr<picture>     addPicture(std::shared_ptr<driver::texture>, const std::wstring &text = L"", const math::aabbox2di &pos = math::aabbox2di()) noexcept;
                std::shared_ptr<scrollbar>   addScrollbar(bool horizontal, const math::aabbox2di &pos = math::aabbox2di()) noexcept;
                std::shared_ptr<progressbar> addProgressbar(const std::wstring &text = L"%f%%", const math::aabbox2di &pos = math::aabbox2di()) noexcept;
                std::shared_ptr<button>      addButton(const std::wstring &text = L"", const math::aabbox2di &pos = math::aabbox2di()) noexcept;
                std::shared_ptr<statictext>  addStaticText(const std::wstring &text = L"", const math::aabbox2di &pos = math::aabbox2di()) noexcept;
                std::shared_ptr<window>      addWindow(const std::wstring &text = L"", const math::aabbox2di &pos = math::aabbox2di()) noexcept;

                void setTheme(std::shared_ptr<theme>) noexcept;
                void addCustomFrame(std::shared_ptr<frame>) noexcept;
                void unActiveElement() noexcept;
                void ActiveElement(std::shared_ptr<frame>) noexcept;

                std::shared_ptr<theme> getTheme() const noexcept;
                std::shared_ptr<font> getInternalFont() const noexcept;
                std::shared_ptr<font> getIconsFont() const noexcept;
                std::shared_ptr<font> getFont(const std::string&) noexcept;

                bool manage(device::input*) noexcept;

                void popFrame(std::shared_ptr<frame>) noexcept;
                void removeFrame(std::shared_ptr<frame>) noexcept;
                void removeFrame(const s32) noexcept;
                void popFrame(const s32) noexcept;
                void clear() noexcept;

                std::shared_ptr<driver::driver> getDrawManager() const noexcept;
                std::shared_ptr<device::Device> getDevice() const noexcept;
                std::shared_ptr<cursor> getCursor() const noexcept;

                void render() noexcept;
            protected:
                std::vector<std::shared_ptr<frame>> gui;
                std::shared_ptr<device::Device> screen;
                std::shared_ptr<driver::driver> mom;
            private:
                friend class frame;
                std::vector<std::shared_ptr<font>> fontcache;
                std::shared_ptr<font> internal, icons;
                std::shared_ptr<theme> custom, interne;
                std::shared_ptr<cursor> cr;
        };

        std::shared_ptr<interface> createGUIEnvironment(
            std::shared_ptr<device::Device> screen,
            std::shared_ptr<driver::driver> drawer
        ) noexcept;
    }
}

#endif // INTERFACE
