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

    Simulation simulation;
    SimulationManager manager(screen, &simulation);
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
            time.reset();

            simulation.update(delta);
            simulation.render(driver);
        renderer->end();
        
        screen->end();
    }
}

/*
int main(int argc, char *args[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Particle Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Simulation simulation;

    bool quit = false;
    SDL_Event e;

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(e.button.button == SDL_BUTTON_LEFT)
                    {
                        simulation.handleMouseDown(e.button.x, e.button.y);
                        std::cout << "." << std::endl;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(e.button.button == SDL_BUTTON_LEFT)
                    {
                        simulation.handleMouseUp();
                    }
                    break;
                case SDL_MOUSEMOTION:
                    simulation.handleMouseMove(e.motion.x, e.motion.y);
                    break;
            }
        }

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        float time_step = ((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        simulation.update(time_step);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        simulation.render(renderer);

        SDL_RenderPresent(renderer);

        // SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
*/