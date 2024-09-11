#include "../sleek/device/splash.h"
#include "../sleek/loader/ressource.h"

/**
 * Copyright 2010-2012 SleekThink All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
 *    in the documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE FREEBSD PROJECT ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE FREEBSD PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/
/** Compilation need gcc 6.8.0 or highter **/

#include "Core.h"

using namespace sleek;
using namespace sleek::device;

//void do_splash() noexcept
//{
//    std::srand(std::time(0));
//    Splash *splash = new Splash(DWM_AUTO);
//
//    splash->setCloseFunction([&splash]{
//        return splash->getTimer()->getTimeMsec() > 1500;
//    });
//
//    std::string file  = "texture/splash/0";
//                file += std::to_string(std::rand()%5);
//                file += ".bmp";
//
//    auto fs = sleek::io::createFilesystem(io::FILE_SYSTEM_TYPE::FST_STD);
//    auto loader = std::make_shared<sleek::loader::loader>(fs);
//
//    splash->setPicture(loader->loadTexture(file));
//    splash->resizeFromPicture();
//    splash->render();
//
//    delete splash;
//    os::ClearConsole();
//}

int main(int argc, char **argv) noexcept
{
//    do_splash();
    Core core;
    core.run();
    return 0;
}
