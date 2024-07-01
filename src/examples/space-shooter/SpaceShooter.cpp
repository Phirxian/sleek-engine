#include "SpaceShooter.h"

#include "../sleek/gui/button.h"
#include "../sleek/gui/statictext.h"

#include <string>
#include <sstream>
#include <unistd.h>

using namespace sleek;

SpaceShooter::SpaceShooter() noexcept
{
    device::Device_stub info = device::Device_stub(512, 512, 32, false);
    screen = CreateDeviceWindowManager(device::DWM_X11, info);

    if (screen == nullptr)
    {
        std::cout << "CreateDeviceWindowManager failed" << std::endl;
        return;
    }

    screen->setWindowPos((screen->getDesktopVideoSize()-screen->getInfo().size)/2);
    screen->setCaption("SleekThink !");

    renderer = createContextRenderer(driver::RCTX_OGL3, screen);
    renderer->setAntialiasing(driver::DAM_NICE);
    renderer->setViewport(screen->getInfo().size);
    driver = renderer->createDriver();

    fs = io::createFilesystem(io::FILE_SYSTEM_TYPE::FST_STD);
    loader = std::make_shared<sleek::loader::loader>(fs);

    guienv = sleek::gui::createGUIEnvironment(screen, driver);
    guienv->getCursor()->showCursor(false);
    guienv->getCursor()->showTexture(true);

    pointor = loader->loadTexture("texture/pointor.bmp");

    if(pointor)
    {
        pointor->createIdentifier(renderer.get());
        pointor->getIdentifier()->update();
        guienv->getCursor()->setTexture(pointor);
    }
}

SpaceShooter::~SpaceShooter() noexcept
{
    screen->setEventReceiver(0);
}

sleek::gui::interface* SpaceShooter::getGui() const noexcept
{
    return guienv.get();
}

sleek::device::Device* SpaceShooter::getDevice() const noexcept
{
    return screen.get();
}

sleek::driver::driver* SpaceShooter::getDriver() const noexcept
{
    return driver.get();
}

sleek::driver::context* SpaceShooter::getContext() const noexcept
{
    return renderer.get();
}

sleek::loader::loader* SpaceShooter::getLoader() const noexcept
{
    return loader.get();
}

sleek::io::filesystem* SpaceShooter::getFileSystem() const noexcept
{
    return fs.get();
}

bool SpaceShooter::manage(sleek::device::input *a) noexcept
{
    if(a->type == sleek::device::EVENT_WINDOW_RESIZE)
        renderer->setViewport(screen->getInfo().size);

    if(a->type == sleek::device::EVENT_KEY_DOWN)
    {
        if(a->key[sleek::device::KEY_KEY_Q] && a->key[sleek::device::KEY_CONTROL])
        {
            screen->exit();
            return true;
        }
    }

    //pp->manage(a);

    if(guienv->manage(a))
        return true;

    //if(scene->manage(a))
    //    return true;

    event::manage(a);

    return false;
}

void SpaceShooter::update_title() noexcept
{
    time.update();
    
    if(time.getTimeMsec() < 1000)
        return;
        
    std::string title;
        title = "Sleek-Think -- Fps(";
        title += std::to_string(screen->getFpsCounter().getFps());
        title += ") -- Time(~";
        title += std::to_string(screen->getFpsCounter().getAvarageTime());
        title += ")ms";
    screen->setCaption(title);
    
    time.reset();
}

void SpaceShooter::run() noexcept
{
    if (screen == nullptr)
        return;

    srand(clock());

    time.update();
    time.reset();

    while(screen->run())
    {
        update_title();
            
        screen->begin();
        screen->manage();

        renderer->bind();
        renderer->begin(0xFF101010);
            //pp->begin();
            //    scene->render();
            //pp->end();

            //pp->draw();

            guienv->render();
        renderer->end();
        
        screen->end();
    }
}
