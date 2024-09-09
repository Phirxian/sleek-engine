#include "trackball.h"
#include "device/device.h"
#include <iostream>

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
                : Camera(dev), sensitivity(2.0f)
            {
                distance = 5.f;
            }

            void TrackballCamera::setDistance(f32 d) noexcept
            {
                distance = d;
                math::vec3f direction = normalize(pos - getTarget());
                pos = getTarget() + direction * distance;
                setPosition(pos);
            }

            f32 TrackballCamera::getDistance() const noexcept
            {
                return distance;
            }

            bool TrackballCamera::manage(device::input *e) noexcept
            {
                if(e->type == device::EVENT_MOUSSE_DOWN)
                {
                    if(e->mouse[device::MOUSE_LEFT])
                    {
                        rotstart = getMouseOnScreen(e->mouse_pos);
                        rotend = rotstart;
                    }

                    if(e->mouse[device::MOUSE_RIGHT])
                    {
                        panstart = getMouseOnScreen(e->mouse_pos);
                        panend = panstart;
                    }

                    if(e->mouse[device::MOUSE_WHEEL_UP])
                    {
                        distance += sensitivity;
                        setDistance(distance);
                    }

                    if(e->mouse[device::MOUSE_WHEEL_DOWN])
                    {
                        distance -= sensitivity;
                        setDistance(distance);
                    }
                }

                if(e->type == device::EVENT_MOUSSE_MOVED)
                {
                    if(e->key_state[device::KEY_LBUTTON])
                    {
                        rotend = getMouseOnScreen(e->mouse_pos);
                        rotatecamera();
                        rotstart = rotend;
                    }

                    if(e->key_state[device::KEY_RBUTTON])
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
                auto start = getTrackballVector(rotstart);
                auto end = getTrackballVector(rotend);
                auto axis = cross(start, end);
                auto direction = glm::normalize(pos-tar);
                
                sleek::math::vec4f camera(direction.x, direction.y, direction.z, 1);
                sleek::math::mat4f transform  = glm::toMat4(sleek::math::quatf(glm::vec3(axis.z*2, -axis.x, axis.y*2)));
                camera = transform * camera * distance;

                setPosition({camera.x, camera.y, camera.z});
            }

            void TrackballCamera::updateCameraMatrix() noexcept
            {
                Camera::updateCameraMatrix();
            }

            // Helper function to map 2D screen coordinates to 3D trackball coordinates
            math::vec3f TrackballCamera::getTrackballVector(const math::vec2f& screenPos)
            {
                math::vec3f v;

                float d;
                v.x = (2.0f * screenPos.x - 1.0f);
                v.y = (1.0f - 2.0f * screenPos.y);
                v.z = 0.0f;
                d = length(v);

                if (d >= 1.0f)
                {
                    d = 1.0f;
                    v.z = 0.0f;
                }
                else
                    v.z = sqrtf(1.f - d * d);
                    
                return normalize(v);
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
