#pragma once

#include "camera.h"
#include "device/device.h"
#include "math/timer.h"
#include "math/math.h"

namespace sleek
{
    namespace scene3d
    {
        namespace camera
        {
            class FPSCamera : public Camera
            {
                public:
                    FPSCamera(device::Device *dev);
                    virtual ~FPSCamera() = default;

                    bool manage(device::input *e) noexcept override;

                    void setMovementSpeed(float speed) { movementSpeed = speed; }
                    void setMouseSensitivity(float sensitivity) { mouseSensitivity = sensitivity; }

                private:
                    void moveCamera(const math::vec3f& direction);
                    void rotateCamera(float yaw, float pitch);
                    math::timer timer;

                    math::vec2f getMouseDelta(const math::vec2i& currentMousePos);

                    float movementSpeed;
                    float mouseSensitivity;

                    math::vec2f lastMousePos;
                    float yaw;
                    float pitch;

                    math::vec3f front;
                    math::vec3f right;
                    math::vec3f up;
            };
        }
    }
}