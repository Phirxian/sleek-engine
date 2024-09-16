#include "filereader.h"
#include <iostream>

namespace sleek
{
    namespace io
    {
        std_filereader::std_filereader(const std::string &filename) : fn(filename)
        {
            stream.open(filename, std::ios::binary | std::ios::ate);

            if (!stream.is_open())
            {
                std::cout << "Failed to open from file: " + filename << std::endl;
                throw std::runtime_error("Failed to open file: " + filename);
            }

            length = stream.tellg();
            stream.seekg(0, std::ios_base::beg);
        }

        std_filereader::~std_filereader()
        {
            stream.close();
        }

        bool std_filereader::is_open() const noexcept
        {
            return stream.is_open();
        }

        const std::string &std_filereader::filename() const noexcept
        {
            return fn;
        }

        void std_filereader::read(void *data, u32 size) noexcept
        {
            if (!stream.read(static_cast<char*>(data), size))
                std::cout << "Failed to read from file: " + filename() << std::endl;
        }

        void std_filereader::seek(u32 pos, bool relative) noexcept
        {
            stream.seekg(pos, relative ? stream.cur : stream.beg);
                
            if (!stream.good())
                std::cout << "Failed to seek in file: " + filename() << std::endl;
        }

        u32 std_filereader::pos() const noexcept
        {
            return const_cast<std_filereader*>(this)->stream.tellg();
        }

        u32 std_filereader::size() const noexcept
        {
            return length;
        }

        void std_filereader::getline(std::string &buff) noexcept
        {
            // std::getline(stream, buff);
            stream >> buff;
        }

        std::string std_filereader::readAll() noexcept
        {
            /*
            std::string o;
            stream.seekg(0, std::ios_base::beg);
            o.assign(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
            return o;
            */
           
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
    }
}