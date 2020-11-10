#ifndef __STD_FILE_READER__
#define __STD_FILE_READER__

#include "../filereader.h"

#include <fstream>
#include <iostream>
#include <string.h>
#include <iterator>

namespace sleek
{
    namespace io
    {
        class std_filereader : public filereader
        {
            public:
                std_filereader(const std::string &filename) : fn(filename)
                {
                    stream.open(filename);
                    stream.seekg(0, stream.end);
                    length = pos();
                    seek(0);
                }

                ~std_filereader()
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

                virtual void read(void *data, u32 size) noexcept
                {
                    stream.read(static_cast<char*>(data), size);
                }

                virtual void seek(u32 pos, bool relative = false) noexcept
                {
                    stream.seekg(pos, relative ? stream.cur : stream.beg);
                }

                virtual u32 pos() const noexcept
                {
                    return const_cast<std_filereader*>(this)->stream.tellg();
                }

                virtual u32 size() const noexcept
                {
                    return length;
                }

                virtual void getline(std::string &buff) noexcept
                {
                    std::getline(stream, buff);
                    //stream >> buff;
                }

                virtual std::string readAll() noexcept
                {
                    std::string o;
                    std::string buff;

                    try
                    {
                        while(stream.good())
                        {
                            std::getline(stream,buff);
                            buff += "\n";
                            o += buff;
                        }
                    }
                    catch(std::ifstream::failure e)
                    {
                        std::cerr << "Exception happened [\"" << fn.c_str() << "\"]: "
                                  << e.what() << "\n"
                                  << "Error bits are: "
                                  << "\nfailbit: " << stream.fail()
                                  << "\neofbit: " << stream.eof()
                                  << "\nbadbit: " << stream.bad()
                                  << "\ndata loaded >> {" << buff.c_str()
                                  << "}" << std::endl;
                    }

                    return o;
                }
            protected:
                std::ifstream stream;
                std::string fn;
                int length;
        };
    }
}

#endif // __FILE_READER__
