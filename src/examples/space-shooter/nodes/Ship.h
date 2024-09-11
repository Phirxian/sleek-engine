#ifndef SPACE_SHOOTER_SHIP
#define SPACE_SHOOTER_SHIP

#include "../sleek/node/node.h"
#include "../sleek/node/scene.h"

class Ship : public sleek::scene3d::Node
{
    public:
        Ship(sleek::scene3d::Scene*) noexcept;
        virtual ~Ship() noexcept;
        
        virtual bool manage(sleek::device::input*) noexcept;
        virtual void setTexture(std::shared_ptr<sleek::driver::texture>) noexcept;

        virtual std::shared_ptr<sleek::driver::texture> getTexture() const noexcept;

        virtual void render() noexcept;
    protected:
        std::shared_ptr<sleek::driver::texture> tex;
};

#endif // NODE
