#ifndef CLASS_VIDEO_MASTER_H_INC
#define CLASS_VIDEO_MASTER_H_INC

#include "../compile.h"
#include "../define.h"

#ifdef video_reader_support
#include "../math/math.h"
#include "../math/timer.h"
#include "../driver/texture.h"
#include "../driver/context.h"

#include <theora/TheoraPlayer.h>
#include "audio.h"
#include <vector>
#include <string>

namespace sleek
{
    namespace video
    {
        struct SVideoClip
        {
            TheoraVideoClip  *pTheoClip;
            driver::texture *pTex;
            std::string clipName;
        };
        class CVideoMaster : public std::enable_shared_from_this<CVideoMaster>
        {
            public:
                CVideoMaster(driver::context*, bool readAudio = true, u32 workerThreads = 1) noexcept;
                virtual ~CVideoMaster() noexcept;

                inline std::shared_ptr<CVideoMaster> getptr() noexcept
                {
                    return shared_from_this();
                }

                SVideoClip*      getClipByName (const std::string &clipname) noexcept;
                TheoraVideoClip* getTheoClipByName(const std::string &clipname) noexcept;
                driver::texture* getTextureByName (const std::string &clipname) noexcept;

                driver::texture* addVideoClip(
                    const std::string &filename,
                    const std::string &clipname,
                    bool repeatPlayback = false,
                    bool startPlayback = true,
                    bool preloadIntoRAM = false
                ) noexcept;

                bool removeVideoClip(const std::string &clipname, bool RemoveTexture = false) noexcept;
                void removeVideoClipAll(bool RemoveTexture = false) noexcept;

                void update() noexcept;
            private:
                void processFrames() noexcept;
                SVideoClip* getClipByName(const std::string &clipname, u32 &out_clipindex) noexcept;

                math::timer *mTimer;
                driver::context *context;

                TheoraVideoManager *mVmgr;
                #ifdef video_reader_audio_support
                CAudioInterfaceFactoryOpenAL *mAIF;
                #endif
                std::vector<SVideoClip*> mClip;
        };
    }
}
#else
namespace sleek
{
    namespace video
    {
        struct SVideoClip;
        class CVideoMaster;
    }
}
#endif
#endif
