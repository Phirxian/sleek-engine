#include "Skinning.h"
#include "opengl/gl.h"

#include <cstring>

namespace sample
{
    Skinning::Skinning(std::shared_ptr<sleek::driver::mesh> t, weight_definition_callback wdc)
        : buffer(t), callback(nullptr)
    {
        weight.resize(buffer->vertices.size(), sleek::math::vec4f(0));
        boneid.resize(buffer->vertices.size(), sleek::math::vec4c(0));

        buffer->datas.push_back({weight.data(), GL_FLOAT,         4, sizeof(sleek::math::vec4f), weight.size()});
        buffer->datas.push_back({boneid.data(), GL_UNSIGNED_BYTE, 4, sizeof(sleek::math::vec4c), boneid.size()});
    }

    Skinning::~Skinning()
    {
    }

    void Skinning::getCurrentFrame(std::shared_ptr<sleek::driver::mesh> out) const noexcept
    {
        out->vertices.resize(buffer->vertices.size());
        out->indices.resize(buffer->indices.size());

        std::memcpy(
            &out->indices[0], &buffer->indices[0],
            sizeof(sleek::math::index<3>)*buffer->indices.size()
        );

        for(int i = 0; i<buffer->vertices.size(); ++i)
        {
            sleek::math::vertex tmp = buffer->vertices[i];

            auto transform = build_animation_matrix(i);
            auto pos = transform * sleek::math::vec4f(tmp.Pos, 1.0);

            tmp.Pos.x = pos.x;
            tmp.Pos.y = pos.y;
            tmp.Pos.z = pos.z;

            // remove the translation for the Normal computation
            // transmation of the normal could be disabled for performance ...

            transform[3] = sleek::math::vec4f(0.0, 0.0, 0.0, 1.0);
            transform = glm::transpose(glm::inverse(transform));
            auto normal = transform * sleek::math::vec4f(tmp.Normal, 1.0);

            tmp.Normal.x = normal.x;
            tmp.Normal.y = normal.y;
            tmp.Normal.z = normal.z;

            out->vertices[i] = tmp;
        }

        if(out->getIdentifier())
            out->getIdentifier()->update();
    }
}

