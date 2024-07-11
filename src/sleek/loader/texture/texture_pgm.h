#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        class texture_pgm : public mimetype, public textureloader, public texturewriter
        {
            public:
                std::shared_ptr<driver::texture> read(io::filereader*) const noexcept override;

                const char *getTypeName() const noexcept override { return "texture_pgm"; }

                int check_header(io::filereader*) const noexcept override;

                bool write(driver::texture*, io::filewriter*) const noexcept override;

                bool match(const std::string&) const noexcept override;
        };
    }
}
