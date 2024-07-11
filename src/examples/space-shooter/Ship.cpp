#include "Ship.h"

using namespace sleek;

Ship::Ship(sleek::scene3d::Scene *m) noexcept : Node(m)
{
    mat.reset(new driver::material());
    mat->setMaterialRender(driver::rmt_add);
//            rnd->setMaterialRender(driver::rmt_sub);
}

Ship::~Ship() noexcept
{
}

void Ship::setTexture(std::shared_ptr<driver::texture> a) noexcept
{
    tex = a;
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

    smgr->getDrawManager()->setActiveMaterial(mat);
    smgr->getDrawManager()->drawTexture(tex.get(), pos);
}
