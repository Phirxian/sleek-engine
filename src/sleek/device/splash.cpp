#include "../driver/driver.h"
#include "../gui/interface.h"
#include "splash.h"

namespace sleek
{
    namespace device
    {
        Splash::Splash(const DeviceWindowManager &dwm, const math::vec2i &size, bool window_decorator) noexcept
            : csp(0), close([]{ return true; }), tm(new math::timer())
        {
            Device_stub info = Device_stub(size, 32, false);
            info.decorator = window_decorator;

            screen = CreateDeviceWindowManager(dwm, info);
            screen->setWindowPos((screen->getDesktopVideoSize()-size)/2);
            screen->setCaption("SleekThink");
            screen->enableWindowDecorator(window_decorator);

            renderer = driver::createContextRenderer(driver::RCTX_OGL3, screen);
            renderer->setAntialiasing(driver::DAM_FAST);
            renderer->setViewport(size);
            driver = renderer->createDriver();
            guienv = gui::createGUIEnvironment(screen, driver);

            screen->setEventReceiver(this);
        }

        Splash::~Splash() noexcept
        {
            delete tm;
            guienv.reset();
            driver.reset();
            renderer.reset();
            screen.reset();
        }

        bool Splash::manage(sleek::device::input *a) noexcept
        {
            guienv->manage(a);
            event::manage(a);
            return false;
        }

        void Splash::setPicture(std::shared_ptr<driver::texture> i) noexcept
        {
            if(i)
            {
                renderer->bind();
                i->createIdentifier(renderer.get());
                i->getIdentifier()->update();
                csp = i->getptr();
            }
        }

        std::shared_ptr<driver::texture> Splash::getPicture() const noexcept
        {
            return csp;
        }

        driver::context* Splash::getRenderer() const noexcept
        {
            return renderer.get();
        }

        gui::Interface* Splash::getGUIEnvirnoment() const noexcept
        {
            return guienv.get();
        }

        math::timer* Splash::getTimer() const noexcept
        {
            return tm;
        }

        void Splash::setCloseFunction(std::function<bool()> i) noexcept
        {
            close = i;
        }

        void Splash::resizeFromPicture() noexcept
        {
            if(!csp)
                return;

            screen->setVideoSize(csp->getDimension());
            screen->setWindowPos((screen->getDesktopVideoSize()-csp->getDimension())/2);
            renderer->setViewport(csp->getDimension());
        }

        void Splash::resize(const math::vec2i &i) noexcept
        {
            screen->setVideoSize(i);
            screen->setWindowPos((screen->getDesktopVideoSize()-screen->getInfo().size)/2);
        }

        void Splash::render() noexcept
        {
            tm->update();
            tm->reset();

            while(screen->run() && !close())
            // divised by 2 beacause, time is augmented by x Sleeping ms time
            {
                tm->update();
                screen->manage();
                screen->begin();
                renderer->begin(0xFF484848);
                    if(csp && csp->getIdentifier())
                        driver->drawTexture(csp.get(), {0, 0});
                    guienv->render();
                renderer->end();
                screen->end();
                tool::Sleeping(2);
            }
        }
    }
}
