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

                    void updateCameraMatrix() noexcept override;
                    void render() noexcept override;
                private:
                    void rotateCamera(float yaw, float pitch);
                    math::timer timer;

                    float movementSpeed;
                    float mouseSensitivity;

                    math::vec2f lastMousePos;
                    float yaw;
                    float pitch;

                    math::vec3f moveDirection;
                    math::vec3f front;
                    math::vec3f right;
                    math::vec3f up;
                    
                    sleek::device::KEYCODE key_up, key_left, key_down, key_right;
            };
        }
    }
}