#ifndef CLASS_AUDIO_INTERFACE_OPEN_AL_H_INC
#define CLASS_AUDIO_INTERFACE_OPEN_AL_H_INC

#include "../compile.h"
#ifdef video_reader_audio_support

#include <AL/al.h>
#include <AL/alc.h>
#include <theora/TheoraAudioInterface.h>
#include <theora/TheoraTimer.h>
#include <theora/TheoraVideoClip.h>
#include <queue>

namespace sleek
{
    namespace video
    {
        struct SBufferOpenAL
        {
            ALuint id;
            int    nSamples;
        };
        class CAudioInterfaceOpenAL : public TheoraAudioInterface, public TheoraTimer
        {
            public:
                CAudioInterfaceOpenAL(TheoraVideoClip* owner, int nChannels, int freq) noexcept;
                virtual ~CAudioInterfaceOpenAL() noexcept;

                short floatToShort(float f) noexcept;

                void insertData(float** data, int nSamples) noexcept;
                void destroy() noexcept;

                void play() noexcept;
                void pause() noexcept;
                void seek(float time) noexcept;

                void update(float time_increase) noexcept;
            protected:
                int mBuffSize;
                int mMaxBuffSize;

                int mNumProcessedSamples;
                int mNumPlayedSamples;

                float mTimeOffset;

                SBufferOpenAL mBuffers[1000];
                std::queue<SBufferOpenAL> mBufferQueue;

                ALuint mSource;

                short *mTempBuffer;
            private:
        };
        class CAudioInterfaceFactoryOpenAL : public TheoraAudioInterfaceFactory
        {
            public:
              CAudioInterfaceFactoryOpenAL() noexcept;
              virtual ~CAudioInterfaceFactoryOpenAL() noexcept;

              CAudioInterfaceOpenAL* createInstance(TheoraVideoClip* owner, int nChannels, int freq) noexcept;
            protected:
              ALCdevice  *gDevice;
              ALCcontext *gContext;
            private:
        };
    }
}

#endif
#endif
