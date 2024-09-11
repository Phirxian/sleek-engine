#include "Ship.h"

using namespace sleek;

Ship::Ship(sleek::scene3d::Scene *m) noexcept : Node(m)
{
    mat = std::make_shared<driver::material>();
    mat->setMode(driver::rmd_polygon);
    mat->setShadeModel(driver::rsd_flat);
    mat->setMaterialRender(driver::rmt_solid);
}

Ship::~Ship() noexcept
{
}

void Ship::setTexture(std::shared_ptr<driver::texture> a) noexcept
{
    tex = a;

    std::cout << mat << std::endl;
    
    if (tex)
    {
        if (mat->Texture.size())
            mat->Texture[0] = tex->getIdentifier().get();
        else
            mat->Texture.push_back(tex->getIdentifier().get());
    }
    else
        mat->Texture.clear();
}

bool Ship::manage(device::input *a) noexcept
{
    return false;
}

std::shared_ptr<driver::texture> Ship::getTexture() const noexcept
{
    return tex;
}

void Ship::render() noexcept
{
    if(!smgr || !smgr->getDrawManager() || !tex)
        return;

    Node::render();

    smgr->getDrawManager()->drawTextureCenter(tex.get(), {pos.x,pos.y,pos.z});
}
