#ifndef __ZIP_FILE_READER__
#define __ZIP_FILE_READER__

#include "../filereader.h"
#include <cstring>
#include <zip.h>

namespace sleek
{
    namespace io
    {
        class zip_filereader : public filereader
        {
            public:
                zip_filereader(zip *archive, const std::string &filename)
                    : fn(filename), cursor(0)
                {
                    struct zip_stat st;
                    zip_stat_init(&st);
                    zip_stat(archive, fn.c_str(), 0, &st);

                    zip_file_t *file = zip_fopen(archive, filename.c_str(), 0);
                    data.resize(st.size);
                    zip_fread(file, &data[0], st.size);
                    zip_fclose(file);
                }

                ~zip_filereader()
                {
                }

                virtual bool is_open() const noexcept
                {
                    return true;
                }

                virtual const std::string& filename() const noexcept
                {
                    return fn;
                }

                virtual void read(void *dst, u32 size) noexcept
                {
                    size = std::min(size, (u32)data.size()-cursor);
                    std::memcpy(dst, &data[cursor], size);
                    cursor += size;
                }

                virtual void seek(u32 pos, bool relative = false) noexcept
                {
                    cursor = cursor*relative + pos;
                }

                virtual u32 pos() const noexcept
                {
                    return cursor;
                }

                virtual u32 size() const noexcept
                {
                    return data.size();
                }

                virtual void getline(std::string &buff) noexcept
                {
                    auto next = data.find_first_of('\n', cursor);

                    if(next == std::string::npos)
                        next = data.size();

                    buff.reserve(buff.size() + cursor-next);
                    buff += data.substr(cursor, cursor-next);
                }

                virtual std::string readAll() noexcept
                {
                    return data;
                }
            protected:
                u32 cursor;
                std::string data;
                std::string fn;
        };
    }
}

#endif // __FILE_READER__
