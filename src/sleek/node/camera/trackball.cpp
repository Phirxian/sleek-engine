#define GLM_Precision glm::precision::mediump

#include "trackball.h"
#include "device/device.h"
#include <algorithm>
#include <iostream>
#include <cmath>

#include "glm/gtx/vector_angle.hpp"
#include "glm/detail/func_geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace sleek
{
    namespace scene3d
    {
        namespace camera
        {
            TrackballCamera::TrackballCamera(device::Device *dev)
                : Camera(dev), sensitivity(2.0f), isRotating(false), isMoving(false)
            {
            }

            void TrackballCamera::setDistance(f32 d) noexcept
            {
                math::vec3f direction = normalize(pos - getTarget());
                pos = getTarget() + direction * std::max(1.f, d);
                setPosition(pos);
            }

            f32 TrackballCamera::getDistance() const noexcept
            {
                return glm::length(tar-pos);
            }

            bool TrackballCamera::manage(device::input *e) noexcept
            {
                if(e->type == device::EVENT_MOUSSE_DOWN)
                {
                    if(e->mouse[device::MOUSE_LEFT])
                    {
                        isRotating = true;
                        rotstart = getMouseOnScreen(e->mouse_pos);
                        rotend = rotstart;
                    }

                    if(e->mouse[device::MOUSE_RIGHT])
                    {
                        isMoving = true;
                        panstart = getMouseOnScreen(e->mouse_pos);
                        panend = panstart;
                    }

                    if(e->mouse[device::MOUSE_WHEEL_UP])
                    {
                        float distance = getDistance() + sensitivity;
                        setDistance(distance);
                    }

                    if(e->mouse[device::MOUSE_WHEEL_DOWN])
                    {
                        float distance = getDistance() - sensitivity;
                        setDistance(distance);
                    }
                }

                if(e->type == device::EVENT_MOUSSE_UP)
                {
                    if(e->mouse[device::MOUSE_LEFT])
                        isRotating = false;

                    if(e->mouse[device::MOUSE_RIGHT])
                        isMoving = false;
                }

                if(e->type == device::EVENT_MOUSSE_MOVED)
                {
                    if(isRotating)
                    {
                        rotend = getMouseOnScreen(e->mouse_pos);
                        rotatecamera();
                        rotstart = rotend;
                    }

                    if(isMoving)
                    {
                        panend = getMouseOnScreen(e->mouse_pos);
                        pancamera();
                        panstart = panend;
                    }
                }

                return Camera::manage(e);
            }

            math::vec2f TrackballCamera::getMouseOnScreen(math::vec2i pos)
            {
                return {
                    pos.x / float(screen->getInfo().size.x),
                    (pos.y - screen->getInfo().size.y) / float(screen->getInfo().size.y)
                };
            }

            void TrackballCamera::rotatecamera()
            {
                math::vec2f mov = (rotend - rotstart) * sensitivity*sensitivity;

                yaw += mov.x;
                pitch += mov.y;
                
                if (pitch > 1.56)
                    pitch = 1.56;
                if (pitch < -1.56)
                    pitch = -1.56;
                
                sleek::math::vec4f camera(glm::length(tar-pos), 0, 0, 1);
                sleek::math::mat4f transform = glm::toMat4(sleek::math::quatf(glm::vec3(0.0f, yaw, 0.0f)));
                transform *= glm::toMat4(sleek::math::quatf(glm::vec3(0.0f, 0.0f, pitch)));
                camera = transform * camera;

                setPosition(math::vec3f(camera.x, camera.y, camera.z) + tar);
            }

            void TrackballCamera::updateCameraMatrix() noexcept
            {
                math::vec3f vector = pos - tar;
                vector = glm::normalize(vector);
                pitch = glm::asin(vector.y);
                yaw = -std::atan2(vector.z, vector.x);

                if (pitch > 1.56f)
                    pitch = 1.56f;

                if (pitch < -1.56f)
                    pitch = -1.56f;

                // distance = glm::length(pos-tar);
                Camera::updateCameraMatrix();
            }

            void TrackballCamera::pancamera()
            {
                math::vec2f mov = (panend - panstart) * sensitivity*sensitivity;
                
                auto cen = getTarget();
                auto up = math::vec3f(0.0f, 1.0f, 0.0f);
                auto forward = normalize(cen - pos);
                auto right = normalize(cross(forward, up));

                up = normalize(cross(right, forward));
                auto pan = (right * -mov.x + up * mov.y) * sensitivity*sensitivity;

                setTarget(cen + pan);
                setPosition(pos + pan);

                panstart = panend;
            }
        }
    }
}
