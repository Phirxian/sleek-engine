#ifndef CPUID
#define CPUID

#include "os.h"
#include <string>
#include <vector>
#include <memory>

namespace sleek
{
    namespace device
    {
        namespace tool
        {
            struct processor
            {
                std::string Manufacturer;
                std::string ProcessorName;

                s8 CoresPerPackage, LogicalPerPackage;
                s8 Family, Model, Stepping;
                s8 BrandID, APICID;
                s32 Clock, MHtz;

                std::vector<const s8*> features;
                std::vector<s8*> caches;
            };

            class cpuid : public std::enable_shared_from_this<cpuid>
            {
                public:
                    cpuid() noexcept;
                    ~cpuid() noexcept;

                    void detectVirtualProcessor() noexcept;
                    u32  getVirtualNumberProcessor() const noexcept;
                    processor getVirtualProcessor(const u32) const noexcept;
                    void updateVirtualProcessorInfo(const u32) noexcept;

                    void printQuickDescription() const noexcept;
                protected:
                    std::vector<processor> proc;
                private:
            };
        }
    }
}

#endif
