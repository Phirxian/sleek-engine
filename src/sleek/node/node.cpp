#include "scene.h"
#include "node.h"

#include "../library/glm/detail/func_geometric.hpp"
#include "../library/glm/gtx/transform.hpp"

namespace sleek
{
    namespace scene3d
    {
        Node::Node(Scene *m) noexcept
            : smgr(m), reference(), enabled(true)
        {
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
            math::mat4f model;
            model = glm::translate(model, pos);
            model = glm::scale(model, sca);
//            model = glm::rotate(model, 90.f, rot);
            return model;
        }

        std::shared_ptr<driver::material> Node::getMaterial() noexcept
        {
            return mat;
        }

        bool Node::operator < (Node *other)
        {
            if(!other->getMaterial())
                return false;

            if(other->getMaterial()->mat == driver::rmt_solid)
                return false;

            return other && (
                glm::distance(pos, smgr->getCamera()->getPosition()) <
                glm::distance(other->pos, smgr->getCamera()->getPosition())
            );
        }

        void Node::render() noexcept
        {
            smgr->getDrawManager()->setActiveMaterial(mat);
        }
    }
}
