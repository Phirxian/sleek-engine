#include "device/device.h"
#include "glm/detail/func_geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "camera.h"

/**
 * TODO remove ogl include
 */

#include "GL/gl.h"

namespace sleek
{
    namespace scene3d
    {
        namespace camera
        {
            Camera::Camera(device::Device *dev) noexcept : screen(dev)
            {
                frust = new Frustum();

                fars  = 500.f;
                nears = 1.0f;
                fovs  = 45.f;

                asps  = (f32)screen->getInfo().size.x
                      / (f32)screen->getInfo().size.y;

                setViewMode(CVM_PERSPECTIV);
                updateCameraMatrix();
            }

            Camera::~Camera() noexcept
            {
                delete frust;
            }

            bool Camera::manage(device::input *e) noexcept
            {
                if(e->type == device::EVENT_WINDOW_RESIZE)
                    setViewMode(mode);

                return false;
            }

            void Camera::setFovValue(const f32 i) noexcept
            {
                fovs = i;
                setViewMode(mode);
            }

            void Camera::setFarValue(const f32 i) noexcept
            {
                fars = i;
                setViewMode(mode);
            }

            void Camera::setNearValue(const f32 i) noexcept
            {
                nears = i;
                setViewMode(mode);
            }

            void Camera::setAspectRatio(const f32 i) noexcept
            {
                asps = i;
                setViewMode(mode);
            }

            void Camera::setViewMode(const CAMERA_VIEW_MODE i) noexcept
            {
                mode = i;

                asps  = (f32)screen->getInfo().size.x
                      / (f32)screen->getInfo().size.y;

                proj = {
                    mode != CVM_ORTHOGRAPHIC ?
                    glm::perspective<f32>(fovs, asps, nears, fars) :
                    glm::ortho<f32>(
                        -screen->getInfo().size.x/2, screen->getInfo().size.x/2,
                        -screen->getInfo().size.y/2, screen->getInfo().size.y/2,
                        nears, fars
                    )
                };

                need_update = true;
            }

            void Camera::setTarget(const math::vec3f &i) noexcept
            {
                tar = i;
                need_update = true;
            }

            void Camera::setPosition(const math::vec3f &i) noexcept
            {
                pos = i;
                need_update = true;
            }

            void Camera::setRotation(const math::vec3f &i) noexcept
            {
                rot = i;
                need_update = true;
            }

            math::mat4f& Camera::getViewMatrix()
            {
                return view;
            }

            math::mat4f& Camera::getProjectionMatrix()
            {
                return proj;
            }

            math::vec3f Camera::getPosition() const noexcept
            {
                return pos;
            }

            math::vec3f Camera::getRotation() const noexcept
            {
                return rot;
            }

            math::vec3f Camera::getTarget() const noexcept
            {
                return tar;
            }

            CAMERA_VIEW_MODE Camera::getViewMode() const noexcept
            {
                return mode;
            }

            Frustum* Camera::getViewFrustum() const noexcept
            {
                return frust;
            }

            f32 Camera::getAspectRatio() const noexcept
            {
                return asps;
            }

            f32 Camera::getNearValue() const noexcept
            {
                return nears;
            }

            f32 Camera::getFarValue() const noexcept
            {
                return fars;
            }

            f32 Camera::getFovValue() const noexcept
            {
                return fovs;
            }

            void Camera::updateCameraMatrix() noexcept
            {
                if(!need_update)
                    return;

                eye = pos;
                cen = tar;
                up = normalize(rot);
                view = glm::lookAt(eye, cen, up);

                need_update = false;
            }

            void Camera::render() noexcept
            {
                updateCameraMatrix();
                glMatrixMode(GL_PROJECTION);
                glLoadMatrixf(glm::value_ptr(proj*view));
                //glMatrixMode(GL_MODELVIEW);
                //glLoadIdentity();
            }
        }
    }
}
