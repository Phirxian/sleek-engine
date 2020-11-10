#include "cpuid.h"
#include <string.h>

#if defined __linux
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <linux/major.h>
#endif

namespace sleek
{
    namespace device
    {
        namespace tool
        {
            //! THANKS http://softpixel.com/~cwright/programming/simd/cpuid.php for asm instruction
            struct output_asm { long eax, ebx, ecx, edx; };
            inline char AsmoToChar(int data, int number) noexcept
            {
                if(number == 1) return (char)(data & 0xFF);
                if(number == 2) return (char)(data >> 8);
                if(number == 3) return (char)(data >> 16);
                if(number == 4) return (char)(data >> 24);
                return (char)0x00;
            }

            cpuid::cpuid() noexcept
            {
                proc.push_back(processor());
            }

            cpuid::~cpuid() noexcept
            {
            }

            void cpuid::detectVirtualProcessor() noexcept
            {
                output_asm tmp;
                char *translate = new char[12];
                memset(translate, 0, 12);
                asm volatile("cpuid;" : "=b" (tmp.ebx), "=c" (tmp.ecx), "=d" (tmp.edx) : "a" (0));
                    translate[ 0] = AsmoToChar(tmp.ebx, 1); translate[ 1] = AsmoToChar(tmp.ebx, 2); translate[ 2] = AsmoToChar(tmp.ebx, 3);
                    translate[ 3] = AsmoToChar(tmp.ebx, 4); translate[ 4] = AsmoToChar(tmp.edx, 1); translate[ 5] = AsmoToChar(tmp.edx, 2);
                    translate[ 6] = AsmoToChar(tmp.edx, 3); translate[ 7] = AsmoToChar(tmp.edx, 4); translate[ 8] = AsmoToChar(tmp.ecx, 1);
                    translate[ 9] = AsmoToChar(tmp.ecx, 2); translate[10] = AsmoToChar(tmp.ecx, 3); translate[11] = AsmoToChar(tmp.ecx, 4);
                proc[0].Manufacturer = translate;
                delete[] translate;

                translate = new char[49];
                memset(translate, 0, 49);
                unsigned _bstr[12 + 1] = {0};
                    asm volatile("cpuid;" :"=a"(_bstr[0]), "=b"(_bstr[1]), "=c"(_bstr[ 2]), "=d"(_bstr[ 3]) :"a"(0x80000002));
                    asm volatile("cpuid;" :"=a"(_bstr[4]), "=b"(_bstr[5]), "=c"(_bstr[ 6]), "=d"(_bstr[ 7]) :"a"(0x80000003));
                    asm volatile("cpuid;" :"=a"(_bstr[8]), "=b"(_bstr[9]), "=c"(_bstr[10]), "=d"(_bstr[11]) :"a"(0x80000004));
                    memmove(translate, _bstr, 49);
                proc[0].ProcessorName = translate;
                delete[] translate;
            }

            u32 cpuid::getVirtualNumberProcessor() const noexcept
            {
                return 0;
            }

            processor cpuid::getVirtualProcessor(const u32) const noexcept
            {
            }

            void cpuid::updateVirtualProcessorInfo(const u32) noexcept
            {
            }

            void cpuid::printQuickDescription() const noexcept
            {
                printf("Processor Name: %s\n", proc[0].ProcessorName.c_str());
                printf("Processor Manufacturer: %s\n", proc[0].Manufacturer.c_str());
            }
        }
    }
}
