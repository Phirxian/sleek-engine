#include "scene.h"
#include "node.h"
#include <cmath>

#define GLM_Precision glm::precision::mediump
#include "../library/glm/detail/func_geometric.hpp"
#include "../library/glm/gtx/transform.hpp"

namespace sleek
{
    namespace scene3d
    {
        Node::Node(Scene *m) noexcept
            : smgr(m), reference(), enabled(true)
        {
            mat = std::make_shared<driver::material>();
            rot = math::vec3f(0, 0, 0);
            sca = math::vec3f(1, 1, 1);
        }

        Node::~Node() noexcept
        {
        }

        void Node::setMaterial(std::shared_ptr<driver::material> i) noexcept
        {
            mat = i;
        }

        void Node::setEnable(bool i) noexcept
        {
            enabled = i;
        }

        void Node::setPosition(const math::vec3f &i) noexcept
        {
            pos = i;
        }

        void Node::setRotation(const math::vec3f &i) noexcept
        {
            rot = i;
        }

        void Node::setScale(const math::vec3f &i) noexcept
        {
            sca = i;
        }

        math::vec3f Node::getScale() const noexcept
        {
            return sca;
        }

        math::vec3f Node::getPosition() const noexcept
        {
            return pos;
        }

        math::vec3f Node::getRotation() const noexcept
        {
            return rot;
        }

        bool Node::getEnable() const noexcept
        {
            return enabled;
        }

        math::mat4f Node::getModelMatrix() const noexcept
        {
            auto npos = pos;
            auto nrot = rot;
            auto nsca = sca;

            auto pxyz = npos.x+npos.y+npos.z;
            auto rxyz = nrot.x+nrot.y+nrot.z;
            auto sxyz = nsca.x+nsca.y+nsca.z;

            if (std::isnan(pxyz) || std::isinf(pxyz))
                npos = {0,0,0};

            if (std::isnan(rxyz) || std::isinf(rxyz))
                nrot = {0,0,0};

            if (sxyz < 1e-2 || std::isnan(sxyz) || std::isinf(sxyz))
                nsca = {1,1,1};

            math::mat4f model = glm::mat4(1.0f);
            model = glm::translate(model, npos);

            math::quatf rotationQuat = glm::quat(glm::radians(nrot));
            math::mat4f rotationMatrix = glm::mat4_cast(rotationQuat);

            model = model * rotationMatrix;

            model = glm::scale(model, nsca);
            return model;
        }

        std::shared_ptr<driver::material> Node::getMaterial() noexcept
        {
            return mat;
        }

        bool Node::operator < (const Node *other) const
        {
            if(!other || !other->mat)
                return false;

            if(other->mat->getMaterialRender() == driver::rmt_solid)
                return false;

            return glm::distance(pos, smgr->getCamera()->getPosition()) <
                   glm::distance(other->pos, smgr->getCamera()->getPosition());
        }

        void Node::render() noexcept
        {
            smgr->getDrawManager()->setActiveMaterial(mat);
        }
    }
}
