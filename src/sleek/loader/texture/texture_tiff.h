#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class texture_tiff : public mimetype, public textureloader
        {
            public:
                std::shared_ptr<driver::texture> read(io::filereader*) const noexcept override;

                const char *getTypeName() const noexcept override { return "texture_tiff"; }

                bool match(const std::string&) const noexcept override;
        };
    }
}
