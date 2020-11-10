#ifndef NATIF
#define NATIF

#include "../node.h"

namespace sleek
{
    namespace scene3d
    {
        namespace real
        {
            class Natif : public Node
            {
                public:
                    Natif(Scene*) noexcept;
                    ~Natif() noexcept;

                    virtual void setMesh(std::shared_ptr<driver::mesh>) noexcept;
                    virtual std::shared_ptr<driver::mesh> getMesh() const noexcept;

                    virtual void render() noexcept;
                private:
                    std::shared_ptr<driver::mesh> mesh;
            };
        }
    }
}

#endif
