#ifndef __STD_FILE_WRITER__
#define __STD_FILE_WRITER__

#include "../filewriter.h"
#include <fstream>

namespace sleek
{
    namespace io
    {
        class std_filewriter : public filewriter
        {
            public:
                std_filewriter(const std::string &filename) : fn(filename)
                {
                    stream.open(filename);
                }

                ~std_filewriter()
                {
                    stream.close();
                }

                virtual bool is_open() const noexcept
                {
                    return stream.is_open();
                }

                virtual const std::string& filename() const noexcept
                {
                    return fn;
                }

                virtual void put(const char c) noexcept
                {
                    stream.put(c);
                }

                virtual void write(const void *data, u32 size) noexcept
                {
                    stream.write(static_cast<const char*>(data), size);
                }

                virtual void seek(u32 pos, bool relative = false) noexcept
                {
                    stream.seekp(pos, relative ? stream.cur : stream.beg);
                }

                virtual u32 pos() noexcept
                {
                    return stream.tellp();
                }
            protected:
                std::ofstream stream;
                std::string fn;
        };
    }
}

#endif // __FILE_WRITER__
