#include "../sleek/start.h"
#include "../sleek/gui/interface.h"
#include "../sleek/gui/button.h"
#include "../sleek/gui/statictext.h"
#include "../sleek/gui/scrollbar.h"
#include "../sleek/gui/progressbar.h"
#include "../sleek/gui/picture.h"
#include "../sleek/gui/colorpicker.h"
#include "../sleek/gui/window.h"
#include <cmath>

const unsigned int SCREEN_WIDTH = 1400;
const unsigned int SCREEN_HEIGHT = 900;

using namespace sleek;

class GUITest : public device::event
{
    public:
        GUITest(std::shared_ptr<device::Device> screen, std::shared_ptr<sleek::driver::driver> driver) : screen(screen), driver(driver)
        {
            auto fs = io::createFilesystem(io::FILE_SYSTEM_TYPE::FST_STD);
            auto loader = std::make_shared<sleek::loader::loader>(fs);
            guienv = sleek::gui::createGUIEnvironment(screen, driver);
            guienv->getCursor()->showCursor(true);
            guienv->getCursor()->showTexture(true);
            
            auto pointor = loader->loadTexture("texture/pointor.bmp");
            auto earth = loader->loadTexture("texture/earth.jpg");

            if(pointor)
            {
                pointor->createIdentifier(driver->getContext().get());
                pointor->getIdentifier()->update();
                guienv->getCursor()->setTexture(pointor);
            }

            if(earth)
            {
                earth->createIdentifier(driver->getContext().get());
                earth->getIdentifier()->update();
            }

            auto a = guienv->addButton("Button", {100, 100, 200, 150});
            a->setTextColor({255,128,0,255});
            guienv->addCustomFrame(a);

            auto b = guienv->addFrame("not displayed", {100, 200, 200, 250});
            guienv->addCustomFrame(b);

            auto c = guienv->addStaticText("static text", {100, 300, 200, 350});
            guienv->addCustomFrame(c);

            auto p1 = guienv->addScrollbar(false, {100, 10, 300, 25});
            guienv->addCustomFrame(p1);
            auto p2 = guienv->addScrollbar(true, {10, 100, 25, 300});
            guienv->addCustomFrame(p2);

            auto d = guienv->addPicture(earth, "", {500, 500, 750, 750});
            guienv->addCustomFrame(c);

            progressbar = guienv->addProgressbar("%f", {100, 50, 200, 75});
            guienv->addCustomFrame(progressbar);

            auto picker = guienv->addColorPicker({500, 300, 610, 462});
            guienv->addCustomFrame(picker);

            auto w = guienv->addWindow("title", {500, 00, 750, 250});
            guienv->addCustomFrame(w);
        }

        bool manage(sleek::device::input *e) noexcept override
        {
            if(guienv->manage(e))
            {
            }

            if(e->type == sleek::device::EVENT_KEY_DOWN)
            {
                if(e->key_state[sleek::device::KEY_KEY_Q] && e->key_state[sleek::device::KEY_CONTROL])
                {
                    this->exit();
                    e->exit_msg = true;
                    screen->exit();
                    return true;
                }
            }

            return device::event::manage(e);
        }

        void draw(float delta)
        {
            float alpha = progressbar->getPercentage();
            alpha += 0.1f*delta;
            progressbar->setPercentage(alpha - int(alpha));

            guienv->render();
        }
    private:
        std::shared_ptr<device::Device> screen;
        std::shared_ptr<sleek::driver::driver> driver;
        std::shared_ptr<sleek::gui::interface> guienv;
        std::shared_ptr<sleek::gui::progressbar> progressbar;
};

int main(int argc, char *args[])
{
    device::Device_stub info = device::Device_stub(SCREEN_WIDTH, SCREEN_HEIGHT, 32, false);
    auto screen = CreateDeviceWindowManager(device::DWM_X11, info);

    if(screen == nullptr)
    {
        std::cout << "CreateDeviceWindowManager failed" << std::endl;
        return -1;
    }

    screen->setWindowPos((screen->getDesktopVideoSize()-screen->getInfo().size)/2);
    screen->setCaption("GUI test");

    auto renderer = createContextRenderer(driver::RCTX_OGL3, screen);
    renderer->setAntialiasing(driver::DAM_NICE);
    renderer->setViewport(screen->getInfo().size);
    auto driver = renderer->createDriver();

    GUITest manager(screen, driver);
    screen->setEventReceiver(&manager);
    
    math::timer time;

    while(screen->run())
    {
        screen->begin();
        screen->manage();

        renderer->bind();
        renderer->begin(0xFF454545);
        
        time.update();
        float delta = time.getTimeSec();
        manager.draw(delta);
        time.reset();

        renderer->end();
        
        screen->end();
    }
}
