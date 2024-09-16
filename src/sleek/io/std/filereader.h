#pragma once

#include "../filereader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

namespace sleek
{
    namespace io
    {
        class std_filereader : public filereader
        {
            public:
                std_filereader(const std::string &filename);
                ~std_filereader();

                virtual bool is_open() const noexcept;

                virtual const std::string &filename() const noexcept;

                virtual void read(void *data, u32 size) noexcept;
                virtual void seek(u32 pos, bool relative = false) noexcept;

                virtual u32 pos() const noexcept;
                virtual u32 size() const noexcept;

                virtual void getline(std::string &buff) noexcept;
                virtual std::string readAll() noexcept;

            protected:
                std::ifstream stream;
                std::string fn;
                int length;
        };
    } // namespace io
} // namespace sleek
