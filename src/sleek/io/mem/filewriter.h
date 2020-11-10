#ifndef __MEM_FILE_WRITER__
#define __MEM_FILE_WRITER__

#include "../filewriter.h"
#include <cstring>

namespace sleek
{
    namespace io
    {
        class mem_filewriter : public filewriter
        {
            public:
                mem_filewriter(const std::string &filename, std::vector<char> &s)
                    : stream(s), fn(filename), cursor(0)
                {
                }

                ~mem_filewriter()
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

                virtual void put(const char c) noexcept
                {
                    if(cursor < stream.size())
                        stream[cursor] = c;
                    else
                        stream.push_back(c);
                    cursor++;
                }

                virtual void write(const void *data, u32 size) noexcept
                {
                    if(size >= stream.size()-cursor)
                        stream.resize(cursor);
                    std::memcpy(&stream[0], data, size);
                }

                virtual void seek(u32 pos, bool relative = false) noexcept
                {
                    cursor = relative ? cursor+pos : pos;
                    if(cursor > stream.size())
                        stream.resize(cursor);
                }

                virtual u32 pos() noexcept
                {
                    return cursor;
                }
            protected:
                std::vector<char> &stream;
                std::string fn;
                u32 cursor;
        };
    }
}

#endif // __FILE_WRITER__
