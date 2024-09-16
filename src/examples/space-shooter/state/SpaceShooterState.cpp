#include "Core.h"
#include "SpaceShooterState.h"

#include <iostream>
#include <unistd.h>
#include <GL/gl.h>

using namespace sleek;
using namespace device;

SpaceShooterState::SpaceShooterState(Core *mom) noexcept
    : screen(mom->getDevice()), core(mom)
{
    smgr = new sleek::scene3d::Scene(screen, mom->getDriver());
}

SpaceShooterState::~SpaceShooterState() noexcept
{
    smgr->clear();
}

sleek::driver::context* SpaceShooterState::getContext() const noexcept
{
    return core->getContext();
}
std::shared_ptr<sleek::driver::material> SpaceShooterState::buildMaterial(
    sleek::scene3d::Node *node, void *user,
    std::string filename_vert, std::string filename_frag,
    sleek::driver::shader_callback callback, int tid
) noexcept
{
    std::string material_key;
    material_key += filename_vert + "-";
    material_key += filename_frag + "-";
    material_key += tid;

    auto it = material_cache.find(material_key);
    if (it!= material_cache.end())
        return it->second;

    auto mat = std::make_shared<driver::material>();
    mat->setMode(driver::rmd_polygon);
    mat->setShadeModel(driver::rsd_flat);
    mat->setMaterialRender(driver::rmt_solid);

    if(tid >= 0 && tid < textures.size() && textures[tid])
        mat->Texture.push_back(textures[tid]->getIdentifier().get());

    // Load and cache shaders
    std::string vertShaderCode = loadShaderCode(filename_vert);
    std::string fragShaderCode = loadShaderCode(filename_frag);

    if (vertShaderCode.empty() || fragShaderCode.empty())
    {
        std::cout << "Failed to load shader files." << std::endl;
        return mat;
    }

    auto shade = core->getContext()->createShader();
    shade->attacheShader(driver::shd_vert, vertShaderCode, "main_vertex");
    shade->attacheShader(driver::shd_frag, fragShaderCode, "main_fragment");

    // Set up shader user data
    shade->user[0] = node;
    shade->user[1] = user;

    if (shade->compileShader())
    {
        mat->setShader(shade);
        shade->setCallback(callback);
    }
    else
    {
        /*
        std::cout << "Shader compilation failed." << std::endl;
        std::cout << "Vertex Shader: " << filename_vert << std::endl;
        std::cout << "Fragment Shader: " << filename_frag << std::endl;
        std::cout << "--------------------" << std::endl;
        std::cout << "Vertex Code: " << vertShaderCode << std::endl;
        std::cout << "--------------------" << std::endl;
        std::cout << "Fragment Code: " << fragShaderCode << std::endl;
        std::cout << "--------------------" << std::endl;
        */
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    material_cache[material_key] = mat;

    return mat;
}

// Helper function to load and cache shader code
std::string SpaceShooterState::loadShaderCode(const std::string& filename)
{
    auto it = shaders_cache.find(filename);
    if (it!= shaders_cache.end())
        return it->second;

    auto shaderCode = core->getFileSystem()->read(filename)->readAll();

    if (shaderCode.empty())
    {
        std::cout << "Failed to read shader file: " << filename << std::endl;
        return "";
    }

    shaders_cache[filename] = shaderCode;

    return shaderCode;
}
