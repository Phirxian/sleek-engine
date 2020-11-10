#include "trackball.h"

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
                : Camera(dev), movementspeed(1.0f), mousesensitivity(1.0)
            {
                radius = glm::length(cen-pos);
                cen = pos + (cen-pos)/radius;
            }

            TrackballCamera::~TrackballCamera()
            {
            }

            bool TrackballCamera::manage(device::input *e) noexcept
            {
                if(e->type == device::EVENT_MOUSSE_DOWN)
                {
                    if(e->mouse[device::MOUSE_LEFT])
                    {
                        rotstart = getmouseprojectiononball(e->mouse_pos);
                        rotend = rotstart;
                    }

                    if(e->mouse[device::MOUSE_RIGHT])
                    {
                        panstart = getmouseonscreen(e->mouse_pos);
                        panend = panstart;
                    }
                }

                if(e->type == device::EVENT_MOUSSE_MOVED)
                {
                    if(e->mouse[device::MOUSE_LEFT])
                    {
                        rotend = getmouseprojectiononball(e->mouse_pos);
                        rotatecamera();
                    }

                    if(e->mouse[device::MOUSE_RIGHT])
                    {
                        panend = getmouseonscreen(e->mouse_pos);
                        pancamera();
                    }
                }

                return Camera::manage(e);
            }

            math::vec3f TrackballCamera::getmouseprojectiononball(math::vec2i pos)
            {
                math::vec3f mouseonball = math::vec3f(getmouseonscreen(pos), 1);

                float length = std::max(1.0f, glm::length(mouseonball));

                mouseonball.z = std::sqrt(1-length*length);
                mouseonball = glm::normalize(mouseonball);

                return mouseonball;
            }

            math::vec2f TrackballCamera::getmouseonscreen(math::vec2i pos)
            {
                return {
                    (pos.x - viewport.upperleft.x * 0.5f) / (viewport.lowerright.x * 0.5f),
                    (pos.y - viewport.upperleft.y * 0.5f) / (viewport.lowerright.y * 0.5f)
                };
            }

            void TrackballCamera::rotatecamera()
            {
                math::vec3f direction = rotend - rotstart;
                float velocity = glm::length(direction);

                if(velocity > 0.0001)
                {
                    /*
                    math::vec3f axis = glm::cross(rotend, rotstart);
                    float length = glm::length(axis);
                    axis = glm::normalize(axis);

                    float angle = std::atan2(length, glm::dot(rotstart, rotend));
                    math::vec3f f = cen-pos;

                    math::quatf quaternion = glm::angleAxis(angle, axis);
                    math::vec3f center = pos + f*radius;

                    math::quatf q = glm::rotate(quaternion, f);
                    f = glm::normalize<float, GLM_Precision>(q);
                    up = glm::normalize(glm::rotate(quaternion, up));

                    pos = center-f*radius;
                    cen = center;

                    rotstart  = rotend;
                    */
                }
            }

            void TrackballCamera::pancamera()
            {
                math::vec2f mov = panend - panstart;

                if(glm::length(mov) != 0.0f)
                {
                    mov *= mousesensitivity*movementspeed;
                    math::vec3f pan = glm::cross(up,cen-pos) * mov.x + up * mov.y;
                    pos += pan;
                    panstart = panend;
                }
            }
        }
    }
}
