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
                radius = 5.f;
            }

            bool TrackballCamera::manage(device::input *e) noexcept
            {
                if(e->type == device::EVENT_MOUSSE_DOWN)
                {
                    if(e->mouse[device::MOUSE_LEFT])
                    {
                        std::cout << "rotation start" << std::endl;
                        rotstart = getmouseonscreen(e->mouse_pos);
                        rotend = rotstart;
                    }

                    if(e->mouse[device::MOUSE_RIGHT])
                    {
                        std::cout << "pan start" << std::endl;
                        panstart = getmouseonscreen(e->mouse_pos);
                        panend = panstart;
                    }
                }

                if(e->type == device::EVENT_MOUSSE_MOVED)
                {
                    if(e->key_state[device::KEY_LBUTTON])
                    {
                        rotend = getmouseonscreen(e->mouse_pos);
                        rotatecamera();
                        rotstart = rotend;
                    }

                    if(e->key_state[device::KEY_RBUTTON])
                    {
                        panend = getmouseonscreen(e->mouse_pos);
                        pancamera();
                        panstart = panend;
                    }
                }

                return Camera::manage(e);
            }

            math::vec2f TrackballCamera::getmouseonscreen(math::vec2i pos)
            {
                return {
                    pos.x / float(screen->getInfo().size.x),
                    (pos.y - screen->getInfo().size.y) / float(screen->getInfo().size.y)
                };
            }

            void TrackballCamera::rotatecamera()
            {
                math::vec3f direction = {rotend.x-rotstart.x, rotend.y-rotstart.y, 1};
                direction *= sensitivity;
                float velocity = glm::length(direction);
                
                sleek::math::vec4f camera(pos.x, pos.y, pos.z, 1);
                sleek::math::mat4f transform  = glm::toMat4(sleek::math::quatf(glm::vec3(0.0f, -direction.x, 0.0f)));
                transform *= glm::toMat4(sleek::math::quatf(glm::vec3(0.0f, 0.0f, direction.y*2)));
                camera = transform * camera;

                setPosition({camera.x, camera.y, camera.z});
            }

            void TrackballCamera::pancamera()
            {
                math::vec2f mov = (panend - panstart) * sensitivity*sensitivity;
                
                auto cen = getTarget();
                auto up = math::vec3f(0.0f, 1.0f, 0.0f);
                auto forward = normalize(cen - pos);
                auto right = normalize(cross(forward, up));

                up = normalize(cross(right, forward));
                auto pan = (right * mov.x + up * -mov.y) * sensitivity*sensitivity;

                setTarget(cen + pan);
                setPosition(pos + pan);

                panstart = panend;
            }
        }
    }
}
