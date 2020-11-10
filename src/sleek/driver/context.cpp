#include "context.h"

#include "ogl3/ogl3_context.h"
//#include "ogl4/ogl4_context.h"

//#include "dx11/dx11_context.h"
//#include "dx12/dx12_context.h"
//#include "vk/vk_context.h"
//#include "metal/metal_context.h"

namespace sleek
{
    namespace driver
    {
        context::context(std::shared_ptr<device::Device> &d, std::shared_ptr<context> s) noexcept : win(d)
        {
            shared = s;
        }

        context::~context() noexcept
        {
        }

        std::shared_ptr<context> createContextRenderer(RENDER_CONTEXT cx, std::shared_ptr<device::Device> &d, std::shared_ptr<context> s) noexcept
        {
            switch(cx)
            {
                case RCTX_OGL3:
                    return std::make_shared<ogl3_context>(d, s);
                break;
//                case RCTX_OGL4:
//                    return std::make_shared<ogl4_context>(d, s);
//                break;
                #ifdef d3d_context_support
                case RCTX_D3D:
                    return std::make_shared<d3d_context>(d, s);
                break;
                #endif
            }
            return nullptr;
        }
    }
}
