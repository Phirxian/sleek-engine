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
    sleek::driver::material_callback callback, int tid
) noexcept
{
    std::string shader_key;
    shader_key += filename_vert + "-";
    shader_key += filename_frag;

    auto mat = std::make_shared<driver::material>();
    mat->setMode(driver::rmd_polygon);
    mat->setShadeModel(driver::rsd_flat);
    mat->setMaterialRender(driver::rmt_solid);
    mat->setCallback(callback);
    mat->depth_test = false;
    mat->user[0] = node;
    mat->user[1] = user;

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

    auto it = shader_cache.find(shader_key);
    if (it != shader_cache.end())
    {
        mat->setShader(it->second);
    }
    else
    {
        auto shade = core->getContext()->createShader();
        shade->attacheShader(driver::shd_vert, vertShaderCode, "main_vertex");
        shade->attacheShader(driver::shd_frag, fragShaderCode, "main_fragment");

        if (shade->compileShader())
            mat->setShader(shade);
        else
            std::this_thread::sleep_for(std::chrono::seconds(10));

        shader_cache[shader_key] = shade;
    }

    return mat;
}

// Helper function to load and cache shader code
std::string SpaceShooterState::loadShaderCode(const std::string& filename)
{
    auto it = shaders_source_cache.find(filename);
    if (it!= shaders_source_cache.end())
        return it->second;

    auto shaderCode = core->getFileSystem()->read(filename)->readAll();

    if (shaderCode.empty())
    {
        std::cout << "Failed to read shader file: " << filename << std::endl;
        return "";
    }

    shaders_source_cache[filename] = shaderCode;

    return shaderCode;
}
