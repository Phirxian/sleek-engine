#ifndef CAMERA
#define CAMERA

#include "frustum.h"
#include "device/event.h"
#include "math/aabbox.h"
#include "glm/mat4x4.hpp"
#include "../../reference.h"

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
            enum CAMERA_VIEW_MODE
            {
                CVM_ORTHOGRAPHIC,
                CVM_PERSPECTIV,
                CVM_COUNT
            };

            class Camera : public reference, public sleek::device::event, public std::enable_shared_from_this<Camera>
            {
                public:
                    Camera(device::Device*) noexcept;
                    virtual ~Camera() noexcept;

                    inline std::shared_ptr<Camera> getptr() noexcept
                    {
                        return shared_from_this();
                    }

                    virtual void setFovValue(const f32) noexcept;
                    virtual void setFarValue(const f32) noexcept;
                    virtual void setNearValue(const f32) noexcept;
                    virtual void setAspectRatio(const f32) noexcept;

                    virtual void setViewMode(const CAMERA_VIEW_MODE) noexcept;
                    virtual void setTarget(const math::vec3f&) noexcept;
                    virtual void setPosition(const math::vec3f&) noexcept;
                    virtual void setRotation(const math::vec3f&) noexcept;

                    virtual math::mat4f& getViewMatrix();
                    virtual math::mat4f& getProjectionMatrix();

                    virtual math::vec3f getPosition() const noexcept;
                    virtual math::vec3f getRotation() const noexcept;
                    virtual math::vec3f getTarget() const noexcept;
                    virtual CAMERA_VIEW_MODE getViewMode() const noexcept;

                    virtual Frustum* getViewFrustum() const noexcept;

                    virtual f32 getAspectRatio() const noexcept;
                    virtual f32 getNearValue() const noexcept;
                    virtual f32 getFarValue() const noexcept;
                    virtual f32 getFovValue() const noexcept;

                    bool manage(device::input*) noexcept override;

                    virtual void updateCameraMatrix() noexcept;
                    virtual void render() noexcept;
                protected:
                    Frustum *frust;
                    device::Device *screen;
                    f32 fars, nears, fovs, asps;

                    math::mat4f view, proj;
                    math::vec3f pos, rot, tar;
                    math::vec3f eye, cen, up;

                    CAMERA_VIEW_MODE mode;
                    bool need_update;
            };
        }
    }
}

#endif
