#include "../sleek/start.h"
#include "../sleek/gui/interface.h"
#include "../sleek/gui/element/button.h"
#include "../sleek/gui/element/statictext.h"
#include "../sleek/gui/element/scrollbar.h"
#include "../sleek/gui/element/progressbar.h"
#include "../sleek/gui/element/picture.h"
#include "../sleek/gui/element/colorpicker.h"
#include "../sleek/gui/element/checkbox.h"
#include "../sleek/gui/element/window.h"
#include <cmath>

const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;

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
            
            auto pointor = loader->loadTexture("texture/pointor.png");
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

            auto a = guienv->addButton(L"Button", {100, 100, 200, 150});
            a->setTextColor({255,128,0,255});
            guienv->addCustomFrame(a);

            auto b = guienv->addFrame(L"not displayed", {100, 200, 200, 250});
            guienv->addCustomFrame(b);

            auto c = guienv->addStaticText(L"static text", {100, 300, 200, 350});
            guienv->addCustomFrame(c);

            auto p1 = guienv->addScrollbar(true, {100, 10, 300, 25});
            guienv->addCustomFrame(p1);
            auto p2 = guienv->addScrollbar(false, {20, 100, 35, 300});
            guienv->addCustomFrame(p2);

            progressbar = guienv->addProgressbar(L"%f", {100, 40, 300, 55});
            guienv->addCustomFrame(progressbar);

            auto check = guienv->addCheckbox(L"Something to enable", {100, 60, 300, 75});
            guienv->addCustomFrame(check);

            auto w1 = guienv->addWindow(L"title", {500, 100, 750, 330});
            auto i1 = guienv->addPicture(earth, L"", {5, 25, 240, 120});
            auto i2 = guienv->addPicture(earth, L"", {5, 125, 240, 220});
            i2->setScalable(false);
            w1->addChild(i1);
            w1->addChild(i2);
            guienv->addCustomFrame(w1);

            auto w2 = guienv->addWindow(L"title", {250, 120, 370, 310});
            auto picker = guienv->addColorPicker({5, 25, 115, 185});
            w2->addChild(picker);
            guienv->addCustomFrame(w2);
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
        std::shared_ptr<sleek::gui::Interface> guienv;
        std::shared_ptr<sleek::gui::progressbar> progressbar;
};

void update_title(device::Device *screen, math::timer time) noexcept
{
    time.update();
    
    if(time.getTimeMsec() < 1000)
        return;
        
    std::string title;
        title = "GUI test -- Fps(";
        title += std::to_string(screen->getFpsCounter().getFps());
        title += ") -- Time(~";
        title += std::to_string(screen->getFpsCounter().getAvarageTime());
        title += ")ms";
    screen->setCaption(title);
    
    time.reset();
}

int main(int argc, char *args[])
{
    device::Device_stub info = device::Device_stub(SCREEN_WIDTH, SCREEN_HEIGHT, 32, false);
    auto screen = CreateDeviceWindowManager(device::DWM_GLFW3, info);

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
    math::timer fps;

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
        update_title(screen.get(), fps);
    }
}
