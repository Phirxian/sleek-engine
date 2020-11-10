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
                    virtual ~TrackballCamera();

                    virtual bool manage(device::input*) noexcept;
                protected:
                    math::vec3f getmouseprojectiononball(math::vec2i);
                    math::vec2f getmouseonscreen(math::vec2i);
                    void rotatecamera();
                    void pancamera();
                protected:
                    f32 radius;
                    f32 movementspeed;
                    f32 mousesensitivity;
                    math::vec3f rotstart;
                    math::vec3f rotend;
                    math::vec2f panstart;
                    math::vec2f panend;
            };
        }
    }
}

#endif
