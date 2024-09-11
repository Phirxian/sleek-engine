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

                    void setDistance(f32) noexcept;
                    f32 getDistance() const noexcept;

                    bool manage(device::input*) noexcept override;

                    void updateCameraMatrix() noexcept override;
                protected:
                    math::vec2f getMouseOnScreen(math::vec2i);
                    void rotatecamera();
                    void pancamera();
                protected:
                    f32 yaw, pitch;
                    f32 sensitivity;
                    bool isRotating, isMoving;
                    math::vec2f rotstart;
                    math::vec2f rotend;
                    math::vec2f panstart;
                    math::vec2f panend;
            };
        }
    }
}

#endif
