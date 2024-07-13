#ifndef TRACKBALL
#define TRACKBALL

#include "camera.h"

namespace sleek
{
    namespace device
    {
        class Device;
    }
    namespace scene3d
    {
        namespace camera
        {
            class TrackballCamera : public Camera
            {
                public:
                    TrackballCamera(device::Device*);

                    bool manage(device::input*) noexcept override;
                protected:
                    math::vec2f getmouseonscreen(math::vec2i);
                    void rotatecamera();
                    void pancamera();
                protected:
                    f32 radius;
                    f32 sensitivity;
                    math::vec2f rotstart;
                    math::vec2f rotend;
                    math::vec2f panstart;
                    math::vec2f panend;
            };
        }
    }
}

#endif
