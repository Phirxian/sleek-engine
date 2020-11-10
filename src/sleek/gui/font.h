#ifndef GUI_FONT
#define GUI_FONT

#include "../driver/texture.h"
#include "../math/aabbox.h"

class FT_LibraryRec_;
typedef struct FT_LibraryRec_  *FT_Library;

class FT_FaceRec_;
typedef struct FT_FaceRec_*  FT_Face;

namespace sleek
{
    namespace gui
    {
        class interface;
        class frame;

        struct fontcache : public std::enable_shared_from_this<fontcache>
        {
            math::vec2i size;
            driver::texture *data;

            inline std::shared_ptr<fontcache> getptr() noexcept
            {
                return shared_from_this();
            }
        };

        class font : public std::enable_shared_from_this<font>
        {
            public:
                font(interface*, void*, int) noexcept;
                font(interface*, const std::string &ttf) noexcept;
                ~font();

                inline std::shared_ptr<font> getptr() noexcept
                {
                    return shared_from_this();
                }

                std::shared_ptr<fontcache> build(gui::frame*) noexcept;
                std::string getFilename() const noexcept;
            protected:
                interface *mom;
                std::string file;
            private:
                FT_Library library;
                FT_Face face;
        };
    }
}

#endif
