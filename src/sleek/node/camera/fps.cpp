
#include "fps.h"

namespace sleek
{
    namespace scene3d
    {
        namespace camera
        {
            FPSCamera::FPSCamera(device::Device *dev)
                : Camera(dev), movementSpeed(0.5f), mouseSensitivity(0.1f), yaw(-90.0f), pitch(0.0f)
            {
                front = math::vec3f(0.0f, 0.0f, -1.0f);
                right = math::vec3f(1.0f, 0.0f, 0.0f);
                up = math::vec3f(0.0f, 1.0f, 0.0f);
                timer.reset();
            }

            bool FPSCamera::manage(device::input *e) noexcept
            {
                if (e->type == device::EVENT_MOUSSE_MOVED)
                {
                    math::vec2f mouseDelta = getMouseDelta(e->mouse_pos);
                    rotateCamera(mouseDelta.x, -mouseDelta.y); // Invert Y-axis
                }

                // Handle keyboard input for movement
                math::vec3f moveDirection(0.0f);
                if (e->key_state[device::KEY_KEY_W]) moveDirection += front;
                if (e->key_state[device::KEY_KEY_S]) moveDirection -= front;
                if (e->key_state[device::KEY_KEY_A]) moveDirection -= right;
                if (e->key_state[device::KEY_KEY_D]) moveDirection += right;
                if (e->key_state[device::KEY_SPACE]) moveDirection += up;
                if (e->key_state[device::KEY_LSHIFT]) moveDirection -= up;

                if (glm::length(moveDirection) > 0.0f)
                    moveCamera(glm::normalize(moveDirection));

                return Camera::manage(e);
            }

            void FPSCamera::moveCamera(const math::vec3f& direction)
            {
                pos += direction * movementSpeed * 0.01f; // * device::Device::getDeltaTime();
                setPosition(pos);
            }

            void FPSCamera::rotateCamera(float yawOffset, float pitchOffset)
            {
                yaw += yawOffset * mouseSensitivity;
                pitch += pitchOffset * mouseSensitivity;

                // Constrain pitch
                if (pitch > 89.0f) pitch = 89.0f;
                if (pitch < -89.0f) pitch = -89.0f;

                // Calculate new front vector
                front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
                front.y = sin(glm::radians(pitch));
                front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
                front = glm::normalize(front);

                // Recalculate right and up vectors
                right = glm::normalize(glm::cross(front, math::vec3f(0.0f, 1.0f, 0.0f)));
                up = glm::normalize(glm::cross(right, front));

                setTarget(pos + front);
            }

            math::vec2f FPSCamera::getMouseDelta(const math::vec2i& currentMousePos)
            {
                math::vec2f delta = math::vec2f(currentMousePos.x - lastMousePos.x, currentMousePos.y - lastMousePos.y);
                lastMousePos = math::vec2f(currentMousePos.x, currentMousePos.y);
                return delta;
            }
        }
    }
}