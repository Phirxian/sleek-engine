#include "Core.h"

#include "../sleek/gui/element/button.h"
#include "../sleek/gui/element/statictext.h"

#include "state/Game.h"

#include <string>
#include <sstream>
#include <unistd.h>

#ifdef __WIN32
namespace std
{
    template <typename T>
    string to_string(T const & t) {
        ostringstream s;
        s << t;
        return s.str();
    }
}
#endif // WIN32

using namespace sleek;

Core::Core() noexcept
{
    device::Device_stub info = device::Device_stub(1024,768,32,false);
    screen = CreateDeviceWindowManager(device::DWM_AUTO, info);

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

    pointor = loader->loadTexture("texture/pointor.png");

    if(pointor)
    {
        pointor->createIdentifier(renderer.get());
        pointor->getIdentifier()->update();
        guienv->getCursor()->setTexture(pointor);
    }

    scene = new Game(this);
    screen->setEventReceiver(this);

    // pp = new PostProcessing(this);
}

Core::~Core() noexcept
{
    screen->setEventReceiver(0);
}

sleek::gui::Interface* Core::getGui() const noexcept
{
    return guienv.get();
}

sleek::device::Device* Core::getDevice() const noexcept
{
    return screen.get();
}

sleek::driver::driver* Core::getDriver() const noexcept
{
    return driver.get();
}

sleek::driver::context* Core::getContext() const noexcept
{
    return renderer.get();
}

sleek::loader::loader* Core::getLoader() const noexcept
{
    return loader.get();
}

sleek::io::filesystem* Core::getFileSystem() const noexcept
{
    return fs.get();
}

bool Core::manage(sleek::device::input *a) noexcept
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

    // pp->manage(a);

    if(guienv->manage(a))
        return true;

    if(scene->manage(a))
        return true;

    event::manage(a);

    return false;
}

void Core::update_title() noexcept
{
    time.update();
    
    if(time.getTimeMsec() < 1000)
        return;
        
    std::string title;
        title = "Space Shooter -- Fps(";
        title += std::to_string(screen->getFpsCounter().getFps());
        title += ") -- Time(~";
        title += std::to_string(screen->getFpsCounter().getAvarageTime());
        title += ")ms";
    screen->setCaption(title);
    
    time.reset();
}

void Core::run() noexcept
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
            //    if(scene)
                    scene->render();
            //pp->end();

            //pp->draw();

            guienv->render();
        renderer->end();
        
        screen->end();
    }
}
