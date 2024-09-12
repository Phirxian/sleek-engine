#include "../driver/context.h"
#include "material.h"
#include "shader.h"

namespace sleek
{
    namespace driver
    {
        shader::shader() noexcept
            : identifier(nullptr),
              callback(nullptr),
              compiled(0)
        {
        }

        shader::~shader() noexcept
        {
        }

        void shader::setLinkToMaterial(material* i) noexcept
        {
            link = i;
        }

        material* shader::getLinkFromMaterial() const noexcept
        {
            return link;
        }

        bool shader::compileShader() noexcept
        {
            return false;
        }

        std::string shader::getShader(const shader_type i) const noexcept
        {
            return source[i];
        }

        void shader::setCallback(const shader_callback i) noexcept
        {
            callback = i;
        }

        shader_callback shader::getCallback() const noexcept
        {
            return callback;
        }

        void shader::update() noexcept
        {
            if(callback)
                callback(this);
        }

        void shader::bind() noexcept
        {
        }

        void shader::unbind() noexcept
        {
        }
    }
}
