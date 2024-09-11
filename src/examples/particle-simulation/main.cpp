#include "../sleek/start.h"
#include "simulation.h"

using namespace sleek;

class SimulationManager : public device::event
{
    public:
        SimulationManager(std::shared_ptr<device::Device> screen, Simulation *sim) : screen(screen), simulation(sim)
        {
        }

        bool manage(sleek::device::input *e) noexcept override
        {
            if(e->type == sleek::device::EVENT_MOUSSE_MOVED)
                simulation->handleMouseMove(e->mouse_pos.x, e->mouse_pos.y);

            if(e->type == sleek::device::EVENT_MOUSSE_DOWN)
                simulation->handleMouseDown(e->mouse_pos.x, e->mouse_pos.y);

            if(e->type == sleek::device::EVENT_MOUSSE_UP)
                simulation->handleMouseUp();

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
    private:
        std::shared_ptr<device::Device> screen;
        Simulation *simulation;
};

void update_title(device::Device *screen, math::timer time) noexcept
{
    time.update();
    
    if(time.getTimeMsec() < 1000)
        return;
        
    std::string title;
        title = "Particle Simulation using nanoflann -- Fps(";
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
    auto screen = CreateDeviceWindowManager(device::DWM_X11, info);

    if(screen == nullptr)
    {
        std::cout << "CreateDeviceWindowManager failed" << std::endl;
        return -1;
    }

    screen->setWindowPos((screen->getDesktopVideoSize()-screen->getInfo().size)/2);
    screen->setCaption("Particle Simulation using nanoflann");

    auto renderer = createContextRenderer(driver::RCTX_OGL3, screen);
    renderer->setAntialiasing(driver::DAM_NICE);
    renderer->setViewport(screen->getInfo().size);
    auto driver = renderer->createDriver();

    auto fs = io::createFilesystem(io::FILE_SYSTEM_TYPE::FST_STD);
    auto loader = std::make_shared<sleek::loader::loader>(fs);
    auto texture = loader->loadTexture("texture/particle.png");

    texture->createIdentifier(renderer.get());
    texture->getIdentifier()->update();

    Simulation simulation(texture.get());
    SimulationManager manager(screen, &simulation);
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
            time.reset();
            // speedup the simulation
            simulation.update(delta*3);
            simulation.render(driver);
        renderer->end();
        
        screen->end();
        update_title(screen.get(), fps);
    }
}