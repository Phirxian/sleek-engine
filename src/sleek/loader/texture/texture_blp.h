#ifndef TEXTURE_BLP_H
#define TEXTURE_BLP_H

#include "../ressource.h"

namespace sleek
{
    namespace loader
    {
        struct sharedheader
        {
            u32 compression;
            u32 flags;
            u32 width;
            u32 height;
            u32 alpha_depth;
            u32 mipmap_offsets[16];
            u32 mipmap_lengths[16];
            u32 palette[265];
        };

        struct blpheader_v1
        {
            u32 compression;
            u32 flags;
            u32 width;
            u32 height;
            u32 alpha_depth;
            u32 pictureSubType;
            u32 mipmap_offsets[16];
            u32 mipmap_lengths[16];
        };

        struct blpheader_v2
        {
            u32   type;               // 0 = JPG, 1 = BLP / DXTC / Uncompressed
            u8    compression;        // 1 = BLP, 2 = DXTC, 3 = Uncompressed
            u8    alpha_depth;        // 0, 1, 4, or 8
            u8    alpha_type;         // 0, 1, 7, or 8
            u8    has_mips;           // 0 = no mips, 1 = has mips
            u32   width;              // Image width in pixels, usually a power of 2
            u32   height;             // Image height in pixels, usually a power of 2
            u32   mipmap_offsets[16]; // The file offsets of each mipmap, 0 for unused
            u32   mipmap_lengths[16]; // The length of each mipmap data block
        };

        class texture_blp : public mimetype, public textureloader, public texturewriter
        {
            public:
                enum Compression : int
                {
                    JPG = 0,
                    BLP = 1,
                    RAW = 2,
                    DXT = 3
                };
            public:
                std::shared_ptr<driver::texture> read(io::filereader*) const noexcept override;

                const char *getTypeName() const noexcept override { return "texture_blp"; }

                int check_header(io::filereader*) const noexcept override;

                bool write(driver::texture*, io::filewriter*) const noexcept override;

                bool match(const std::string&) const noexcept override;
            protected:
                std::shared_ptr<driver::texture> decompressBLP(const sharedheader&, char *, size_t) const;
                std::shared_ptr<driver::texture> decompressDXT(const sharedheader&, char *, size_t) const;
                std::shared_ptr<driver::texture> decompressRaw(const sharedheader&, char *, size_t) const;
                std::shared_ptr<driver::texture> decompressJpg(const sharedheader&, char *, size_t) const;
        };
    }
}

#endif // TEXTURE_BLP_H
