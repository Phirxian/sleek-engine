#include "audio.h"
#include <climits>
#include <iostream>

#ifdef video_reader_audio_support

namespace sleek
{
    namespace video
    {
        short CAudioInterfaceOpenAL::floatToShort(float f) noexcept
        {
            if(f >  1) f =  1;
            else if(f < -1) f = -1;
            return (short)(f * SHRT_MAX);
        }

        CAudioInterfaceOpenAL::CAudioInterfaceOpenAL(TheoraVideoClip* owner, int nChannels, int freq) noexcept
            : TheoraAudioInterface(owner, nChannels, freq), mBuffSize(0), mNumProcessedSamples(0), mTimeOffset(0), mNumPlayedSamples(0), mTempBuffer(0)
        {
            mMaxBuffSize = freq * mNumChannels * 2;
            mTempBuffer  = new short[mMaxBuffSize];
            alGenSources(1, &mSource);
            owner->setTimer(this);
        }

        void CAudioInterfaceOpenAL::destroy() noexcept
        {
        }

        CAudioInterfaceOpenAL::~CAudioInterfaceOpenAL() noexcept
        {
            if(mTempBuffer) delete mTempBuffer;
        }

        void CAudioInterfaceOpenAL::insertData(float** data, int nSamples) noexcept
        {
            for (int i = 0; i < nSamples; ++i)
            {
                if (mBuffSize < mMaxBuffSize)
                {
                    mTempBuffer[++mBuffSize] = floatToShort(data[0][i]);
                    if(mNumChannels == 2)
                        mTempBuffer[++mBuffSize] = floatToShort(data[1][i]);
                }
                if (mBuffSize == mFreq * mNumChannels / 4)
                {
                    SBufferOpenAL buff;
                    alGenBuffers(1, &buff.id);

                    ALuint format;
                    if (mNumChannels == 1) format = AL_FORMAT_MONO16;
                    else format = AL_FORMAT_STEREO16;

                    alBufferData(buff.id, format, mTempBuffer, mBuffSize * 2, mFreq);
                    alSourceQueueBuffers(mSource, 1, &buff.id);
                    buff.nSamples = mBuffSize / mNumChannels;
                    mNumProcessedSamples += mBuffSize / mNumChannels;
                    mBufferQueue.push(buff);

                    mBuffSize = 0;

                    int state;
                    alGetSourcei(mSource, AL_SOURCE_STATE, &state);
                    if(state != AL_PLAYING)
                    {
                        alSourcef(mSource, AL_SAMPLE_OFFSET, (float)mNumProcessedSamples - mFreq / 4);
                        alSourcePlay(mSource);
                    }
                }
            }
        }

        void CAudioInterfaceOpenAL::update(float time_increase) noexcept
        {
            SBufferOpenAL buff;
            int i, state, nProcessed;
            alGetSourcei(mSource, AL_BUFFERS_PROCESSED, &nProcessed);
            for (i = 0; i < nProcessed; ++i)
            {
                buff = mBufferQueue.front();
                mBufferQueue.pop();
                mNumPlayedSamples += buff.nSamples;
                alSourceUnqueueBuffers(mSource, 1, &buff.id);
                alDeleteBuffers(1, &buff.id);
            }
            alGetSourcei(mSource, AL_SOURCE_STATE, &state);
            if (state == AL_PLAYING)
            {
                alGetSourcef(mSource, AL_SEC_OFFSET, &mTime);
                mTime += (float)mNumPlayedSamples / mFreq;
                mTimeOffset = 0;
            }
            else
            {
                mTime = (float)mNumProcessedSamples / mFreq + mTimeOffset;
                mTimeOffset += time_increase;
            }
            float duration = mClip->getDuration();
            if (mTime > duration) mTime = duration;
        }

        void CAudioInterfaceOpenAL::pause() noexcept
        {
            alSourcePause(mSource);
            TheoraTimer::pause();
        }

        void CAudioInterfaceOpenAL::play() noexcept
        {
            alSourcePlay(mSource);
            TheoraTimer::play();
        }

        void CAudioInterfaceOpenAL::seek(float time) noexcept
        {
            SBufferOpenAL buff;
            alSourceStop(mSource);

            while (!mBufferQueue.empty())
            {
                buff = mBufferQueue.front();
                mBufferQueue.pop();
                alSourceUnqueueBuffers(mSource, 1, &buff.id);
                alDeleteBuffers(1, &buff.id);
            }
            mBuffSize = 0; mTimeOffset = 0;
            mNumPlayedSamples = mNumProcessedSamples = (int)time * mFreq;
        }

        /***********************************/

        const char* ErrorCheck(ALenum error) noexcept
        {
            if(error == AL_INVALID_NAME)
            {
                return "Invalid name";
            }
            else if(error == AL_INVALID_ENUM)
            {
                return " Invalid enum ";
            }
            else if(error == AL_INVALID_VALUE)
            {
                return " Invalid value ";
            }
            else if(error == AL_INVALID_OPERATION)
            {
                return " Invalid operation ";
            }
            else if(error == AL_OUT_OF_MEMORY)
            {
                return " Out of memory like! ";
            }

            return " Don't know ";
        }

        CAudioInterfaceFactoryOpenAL::CAudioInterfaceFactoryOpenAL() noexcept : gDevice(0), gContext(0)
        {
            gDevice = alcOpenDevice("");

            if(alcGetError(gDevice) == ALC_NO_ERROR)
            {
                gContext = alcCreateContext(gDevice, NULL);
                if(alcGetError(gDevice) == ALC_NO_ERROR)
                {
                    alcMakeContextCurrent(gContext);
                    if(alcGetError(gDevice) != ALC_NO_ERROR)
                    {
                        std::cout << ErrorCheck(alcGetError(gDevice)) << std::endl;
                        gDevice = NULL;
                    }
                }
                else
                {
                    std::cout << ErrorCheck(alcGetError(gDevice)) << std::endl;
                    gDevice  = NULL;
                }
            }
            else
            {
                gContext = NULL;
                gDevice  = NULL;
            }
        }

        CAudioInterfaceFactoryOpenAL::~CAudioInterfaceFactoryOpenAL() noexcept
        {
            if(gDevice)
            {
                alcMakeContextCurrent(NULL);
                alcDestroyContext(gContext);
                alcCloseDevice(gDevice);
            }
        }

        CAudioInterfaceOpenAL* CAudioInterfaceFactoryOpenAL::createInstance(TheoraVideoClip* owner, int nChannels, int freq) noexcept
        {
          return new CAudioInterfaceOpenAL(owner, nChannels, freq);
        }
    }
}

#endif
