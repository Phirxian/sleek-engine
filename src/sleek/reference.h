#ifndef REFERENCE
#define REFERENCE

#include "math/aabbox.h"
#include "define.h"

#include <vector>
#include <string>
#include <memory>

namespace sleek
{
    struct attribute
    {
        attribute()
        {
            name = "undefined";
        }

        attribute(const std::string &_name, const std::string &_value)
            : name(std::move(_name)), value(std::move(_value))
        {
        }

        attribute(const std::string &&_name, const std::string &&_value)
            : name(std::move(_name)), value(std::move(_value))
        {
        }

        std::string name;
        std::string value;
    };

    class reference// : public virtual std::enable_shared_from_this<reference>
    {
        public:
            reference(const u32 id = 0) noexcept;
            virtual ~reference() noexcept;

//            inline std::shared_ptr<reference> getptr() noexcept
//            {
//                return shared_from_this();
//            }

            virtual std::string getSerialiseName() const noexcept { return "Reference"; }

            /// added othe bloc in this bloc
            virtual void operator += (reference*) noexcept;
            virtual void egals(const reference*) noexcept;

            virtual void clear() noexcept;
            virtual void clearAttribute() noexcept;
            virtual void clearBloc() noexcept;

            virtual void addBloc(reference*) noexcept;
            virtual reference* getBloc(const u32 index) const noexcept;
            virtual reference* getBloc(const std::string &name) const noexcept;
            virtual void removeBloc(const std::string &name) noexcept;
            virtual void removeBloc(const u32 index) noexcept;
            virtual u32 getNumberBloc() const noexcept;

            virtual void addAttribute(const std::string &name, const std::string &value = "") noexcept;
            virtual std::string getAttribute(const std::string &name) const noexcept;
            virtual std::string getAttribute(const u32 index) const noexcept;
            virtual void removeAttribute(const std::string &name) noexcept;
            virtual void removeAttribute(const u32 index) noexcept;
            virtual u32 getNumberAttribute() const noexcept;

            virtual std::string serialise(const char *tablature = "") const noexcept;
            virtual void unserialise(const std::string&) noexcept;

            virtual inline void setId(const u32 i) noexcept { id = i; }
            virtual inline u32 getId() const noexcept { return id; }

            virtual inline void setUser(void *i) noexcept { userdata = i; }
            virtual inline void* getUser() const noexcept { return userdata; }
        protected:
            void *userdata;
            std::vector<reference*> bloc;
            std::vector<attribute> info;
            std::string TypeName;
            u32 id;
    };
}

#endif // REFERENCE
