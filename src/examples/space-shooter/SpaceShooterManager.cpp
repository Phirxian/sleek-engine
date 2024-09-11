#include "SpaceShooterManager.h"

#include "../sleek/gui/element/button.h"
#include "../sleek/gui/element/statictext.h"
#include "MainMenu.h"
#include "Game.h"

#include <string>
#include <sstream>
#include <unistd.h>

using namespace sleek;

static void material_callback(sleek::driver::shader *i) noexcept
{
    auto *node = static_cast<sleek::scene3d::Node*>(i->user[0]);
    auto *camera = node->getScene()->getCamera();

    i->setVariable("model",      node->getModelMatrix());
    i->setVariable("view",       camera->getViewMatrix());
    i->setVariable("projection", camera->getProjectionMatrix());

    if (i->getLinkFromMaterial() && i->getLinkFromMaterial()->Texture.size())
        i->setTexture("base", i->getLinkFromMaterial()->Texture[0], 0);
};

SpaceShooterManager::SpaceShooterManager() noexcept
{
    device::Device_stub info = device::Device_stub(512, 512, 32, false);
    screen = CreateDeviceWindowManager(device::DWM_GLFW3, info);

    if(screen == nullptr)
    {
        std::cout << "CreateDeviceWindowManager failed" << std::endl;
        return;
    }

    screen->setWindowPos((screen->getDesktopVideoSize()-screen->getInfo().size)/2);
    screen->setCaption("SleekThink !");
    screen->setEventReceiver(this);

    renderer = createContextRenderer(driver::RCTX_OGL3, screen);
    renderer->setAntialiasing(driver::DAM_NICE);
    renderer->setViewport(screen->getInfo().size);
    driver = renderer->createDriver();

    fs = io::createFilesystem(io::FILE_SYSTEM_TYPE::FST_STD);
    loader = std::make_shared<sleek::loader::loader>(fs);

    guienv = sleek::gui::createGUIEnvironment(screen, driver);
    guienv->getCursor()->showCursor(true);
    guienv->getCursor()->showTexture(true);
    
    pointor = loader->loadTexture("texture/pointor.bmp");

    if(pointor)
    {
        pointor->createIdentifier(renderer.get());
        pointor->getIdentifier()->update();
        guienv->getCursor()->setTexture(pointor);
    }

    game = std::make_shared<Game>(this);
    main_menu = std::make_shared<MainMenu>(this);
    current_state = game;
}

std::shared_ptr<sleek::driver::material> SpaceShooterManager::buildMaterial(
    sleek::scene3d::Node *node, void *user,
    std::string filename_vert, std::string filename_frag,
    sleek::driver::shader_callback callback, std::shared_ptr<sleek::driver::texture> texture
) noexcept
{
    auto shade = getContext()->createShader();
    auto mat = std::make_shared<driver::material>();

    mat->setMode(driver::rmd_polygon);
    mat->setShadeModel(driver::rsd_flat);
    mat->setMaterialRender(driver::rmt_solid);
    mat->setShader(shade);

    if(texture && texture->getIdentifier())
        mat->Texture.push_back(texture->getIdentifier().get());

    auto vert = getFileSystem()->read(filename_vert);
    auto frag = getFileSystem()->read(filename_frag);

    shade->attacheShader(driver::shd_vert, vert->readAll(), "main");
    shade->attacheShader(driver::shd_frag, frag->readAll(), "main");
    // used to get information from material (like texture binding) by callback
    shade->setLinkToMaterial(mat.get());
    // used to get model view
    shade->user[0] = node;
    shade->user[1] = user;

    shade->compileShader();

    if (callback)
        shade->setCallback(callback);
    else
        shade->setCallback(material_callback);

    return mat;
}

void SpaceShooterManager::setState(GameState new_state)
{
    switch (new_state)
    {
    case GS_MAIN_MENU:
        current_state = main_menu;
        break;
    case GS_GAME:
        current_state = game;
        break;
    
    default:
        break;
    }
}

SpaceShooterManager::~SpaceShooterManager() noexcept
{
    screen->setEventReceiver(0);
}

sleek::gui::interface* SpaceShooterManager::getGui() const noexcept
{
    return guienv.get();
}

sleek::device::Device* SpaceShooterManager::getDevice() const noexcept
{
    return screen.get();
}

sleek::driver::driver* SpaceShooterManager::getDriver() const noexcept
{
    return driver.get();
}

sleek::driver::context* SpaceShooterManager::getContext() const noexcept
{
    return renderer.get();
}

sleek::loader::loader* SpaceShooterManager::getLoader() const noexcept
{
    return loader.get();
}

sleek::io::filesystem* SpaceShooterManager::getFileSystem() const noexcept
{
    return fs.get();
}

bool SpaceShooterManager::manage(sleek::device::input *e) noexcept
{
    if(e->type == sleek::device::EVENT_WINDOW_RESIZE)
        renderer->setViewport(screen->getInfo().size);

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

    if(current_state->manage(e))
        return true;

    return event::manage(e);
}

void SpaceShooterManager::update_title() noexcept
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

void SpaceShooterManager::run() noexcept
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
        renderer->begin(0xFF454545);
            current_state->run();
            //smgr->render();
            //guienv->render();
        renderer->end();
        
        screen->end();
    }
}
