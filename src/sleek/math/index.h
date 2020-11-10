#pragma once

#include "../define.h"

namespace sleek
{
    namespace math
    {
        template<u32 n>
        struct index
        {
            static const int size = n;

            index() noexcept : vertex{0}
            {
            }

            template<typename ...Args>
            index(Args... args) noexcept : vertex{args...}
            {
                #ifdef __DEBUG
                std::cout << "new index >> ";
                for(u32 i = 0; i<n; ++i)
                    std::cout << vertex[i] << " ";
                std::cout << std::endl;
                #endif
            }

            ~index() noexcept
            {
            }

            template<typename ...Args>
            void set(Args... args) noexcept
            {
                vertex = {args...};
            }

            void operator = (const u16 *other) noexcept
            {
                for(u32 i = 0; i<n; ++i)
                    vertex[i] = other[i];
            }
            void operator = (const index<n> other) noexcept
            {
                for(u32 i = 0; i<n; ++i)
                    vertex[i] = other.vertex[i];
            }

            u32 vertex[n];
        };
    }
}
