

#include "MainMenu.h"

#include "../sleek/gui/button.h"
#include "../sleek/gui/statictext.h"
#include "Ship.h"

#include <string>
#include <sstream>
#include <unistd.h>

using namespace sleek;

MainMenu::MainMenu(SpaceShooterManager *mgr) noexcept
    : SpaceShooterState(mgr)
{

    play = guienv->addButton("Play", {100, 100, 200, 150});
    play->setTextColor({255,128,0,255});
    guienv->addCustomFrame(play);

    quit = guienv->addButton("Exit", {100, 250, 200, 300});
    quit->setTextColor({255,128,0,255});
    guienv->addCustomFrame(quit);
    //pp->manage(e);
}

MainMenu::~MainMenu() noexcept
{
}

bool MainMenu::manage(sleek::device::input *e) noexcept
{
    if(smgr->manage(e))
        return true;

    if(guienv->manage(e))
    {
        if(e->gui.code == gui::IET_BUTTON_CLICKED)
        {
            if(e->gui.called == play.get())
            {
                mgr->setState(GS_GAME);
            }
                
            if(e->gui.called == quit.get())
            {
                this->exit();
                e->exit_msg = true;
                mgr->getDevice()->exit();
                return false;
            }
        }
        
        return true;
    }

    return event::manage(e);
}

void MainMenu::run() noexcept
{
    smgr->render();
    guienv->render();
}