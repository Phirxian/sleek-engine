#ifndef __MEM_FILE_READER__
#define __MEM_FILE_READER__

#include "../filereader.h"

#include <fstream>
#include <iostream>
#include <string.h>
#include <iterator>

namespace sleek
{
    namespace io
    {
        class mem_filereader : public filereader
        {
            public:
                mem_filereader(const std::string &filename, const std::vector<char> &s)
                    : stream(s), fn(filename), cursor(0)
                {
                }

                ~mem_filereader()
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

                virtual void read(void *data, u32 size) noexcept
                {
                    cursor += size;
                }

                virtual void seek(u32 pos, bool relative = false) noexcept
                {
                    cursor = relative ? cursor+pos : pos;
                }

                virtual u32 pos() const noexcept
                {
                    return cursor;
                }

                virtual u32 size() const noexcept
                {
                    return stream.size();
                }

                virtual void getline(std::string &buff) noexcept
                {
                    // cursor += std::getline(stream, buff);
                }

                virtual std::string readAll() noexcept
                {
                    return std::string(stream.data(), stream.size());
                }
            protected:
                const std::vector<char> &stream;
                std::string fn;
                u32 cursor;
        };
    }
}

#endif // __FILE_READER__
