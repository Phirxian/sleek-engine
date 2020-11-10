#ifndef __HARDWARE_IDENTIFIER_HEADER__
#define __HARDWARE_IDENTIFIER_HEADER__

#include <memory>

namespace sleek
{
    namespace driver
    {
        enum HARDWARE_IDENTIFIER_TYPE : int
        {
            HIT_NULL,
            HIT_TEXTURE,
            HIT_FBO,
            HIT_VAO,
            HIT_SHADER,
            HIT_USER_TYPE
        };

        enum VAO_ALIGNMENT
        {
            VAO_STATIC,
            VAO_DYNAMIC,
            VAO_STREAM,
        };

        struct identifier : public std::enable_shared_from_this<identifier>
        {
            identifier(void *o) noexcept : owner(o) { }
            virtual ~identifier() { }

            virtual HARDWARE_IDENTIFIER_TYPE getType() const noexcept
            {
                return HIT_NULL;
            }

            virtual void* getHardwareTarget() const noexcept = 0;
            virtual void* getHardwareLink() const noexcept = 0;

            virtual void update() noexcept = 0;
            virtual void bind() noexcept = 0;
            virtual void unbind() noexcept = 0;

            inline std::shared_ptr<identifier> getptr() noexcept
            {
                return shared_from_this();
            }

            void *owner;
        };

        struct local_bind
        {
            local_bind(std::shared_ptr<identifier> s = nullptr) noexcept
                : i(s), bind(false)
            {
                if(i)
                {
                    i->bind();
                    bind = true;
                }
            }

            ~local_bind() noexcept
            {
                if(i) i->unbind();
            }

            identifier* getIdentifier() const noexcept
            {
                return i.get();
            }

            // used to bind vbo
            inline void* ifNotBind(void *data) const noexcept
            {
                return (void*) (~(-bind) & (uintptr_t)data);
            }

            // used to bind vbo
            inline int ifNotBind(int data) const noexcept
            {
                return (-bind) & data;
            }

            std::shared_ptr<identifier> i;
            bool bind;
        };
    }
}

#endif // __HARDWARE_IDENTIFIER_HEADER__
