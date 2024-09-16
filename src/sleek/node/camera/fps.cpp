
#include "fps.h"

namespace sleek
{
    namespace scene3d
    {
        namespace camera
        {
            FPSCamera::FPSCamera(device::Device *dev)
                : Camera(dev), movementSpeed(2.0f), mouseSensitivity(0.1f), yaw(-90.0f), pitch(0.0f)
            {
                moveDirection = {0,0,0};
                front = math::vec3f(0.0f, 0.0f, -1.0f);
                right = math::vec3f(1.0f, 0.0f, 0.0f);
                up = math::vec3f(0.0f, 1.0f, 0.0f);
                timer.reset();
            }

            bool FPSCamera::manage(device::input *e) noexcept
            {
                // Handle keyboard input for movement
                // should always be updated
                moveDirection = {0,0,0};

                if (e->key_state[device::KEY_KEY_W])
                    moveDirection += front;
                if (e->key_state[device::KEY_KEY_S])
                    moveDirection -= front;
                if (e->key_state[device::KEY_KEY_A])
                    moveDirection -= right;
                if (e->key_state[device::KEY_KEY_D])
                    moveDirection += right;
                if (e->key_state[device::KEY_SPACE])
                    moveDirection += up;
                if (e->key_state[device::KEY_LSHIFT])
                    moveDirection -= up;

                if (e->type == device::EVENT_MOUSSE_MOVED)
                {
                    math::vec2f delta = math::vec2f(e->mouse_pos.x - lastMousePos.x, e->mouse_pos.y - lastMousePos.y);
                    // EVENT_MOUSSE_MOVED might be emmited by WarpMouse
                    if (abs(delta.x)+abs(delta.y) > 0)
                    {
                        rotateCamera(delta.x, -delta.y);

                        if (false)
                            lastMousePos = math::vec2f(e->mouse_pos.x, e->mouse_pos.y);
                        else
                        {
                            lastMousePos = screen->getInfo().size/2;
                            screen->WarpMouse(screen->getInfo().size/2);
                        }
                    }
                }

                return Camera::manage(e);
            }

            void FPSCamera::rotateCamera(float yawOffset, float pitchOffset)
            {
                yawOffset *= mouseSensitivity;
                pitchOffset *= mouseSensitivity;
                yaw += yawOffset;
                pitch += pitchOffset;
            }

            void FPSCamera::updateCameraMatrix() noexcept
            {
                front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
                front.y = sin(glm::radians(pitch));
                front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
                
                front = glm::normalize(front);
                right = glm::normalize(glm::cross(front, math::vec3f(0.0f, 1.0f, 0.0f)));
                up    = glm::normalize(glm::cross(right, front));
                view =  glm::lookAt(pos, pos+front, up);
            }

            void FPSCamera::render() noexcept
            {
                if (glm::length(moveDirection) > 0.0f)
                    pos += glm::normalize(moveDirection) * movementSpeed;
                Camera::render();
            }
        }
    }
}