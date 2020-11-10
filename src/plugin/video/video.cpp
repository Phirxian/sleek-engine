#include "../driver/context.h"
#include "video.h"

#ifdef video_reader_support

#include <theora/TheoraDataSource.h>
#include <cstring>

namespace sleek
{
    namespace video
    {
        CVideoMaster::CVideoMaster(driver::context *cx, bool readAudio, u32 workerThreads) noexcept
            : mTimer(new math::timer), context(cx), mVmgr(0)
        {
            mVmgr = new TheoraVideoManager(std::max(workerThreads, 1u));
            #ifdef video_reader_audio_support
            if(readAudio)
            {
                mAIF = new CAudioInterfaceFactoryOpenAL();
                mVmgr->setAudioInterfaceFactory(mAIF);
            }
            else mAIF = nullptr;
            #endif
        }

        CVideoMaster::~CVideoMaster() noexcept
        {
            removeVideoClipAll();
            if(mVmgr) delete mVmgr;
            #ifdef video_reader_audio_support
            if(mAIF) delete mAIF;
            #endif
        }

        void CVideoMaster::processFrames() noexcept
        {
            for(u32 i = 0; i<mClip.size(); ++i)
            {
                TheoraVideoFrame* frame = mClip[i]->pTheoClip->getNextFrame();
                if(frame)
                {
                    driver::texture* pTex = mClip[i]->pTex;

                    void* imgData = pTex->getBuffer();
                    u8* frameData = frame->getBuffer();

                    if(imgData && frameData)
                    {
                        std::memcpy(imgData, frameData, pTex->getBufferSize());
                        pTex->getIdentifier()->update();
                    }

                    mClip[i]->pTheoClip->popFrame();
                }
                #ifdef _DEBUG
                    std::cout << mClip[i]->pTheoClip->getNumDisplayedFrames()
                              << "/" << mClip[i]->pTheoClip->getNumFrames()
                              << std::endl;
                #endif
            }
        }

        void CVideoMaster::update() noexcept
        {
            mTimer->update();

            processFrames();
            mVmgr->update(mTimer->getTimeSec());

            mTimer->reset();
        }

        SVideoClip* CVideoMaster::getClipByName(const std::string &clipname, u32 &out_clipindex) noexcept
        {
            for(u32 i = 0; i<mClip.size(); ++i)
            {
                if(mClip[i]->clipName == clipname)
                {
                    out_clipindex = i;
                    return mClip[i];
                }
            }
            return nullptr;
        }

        SVideoClip* CVideoMaster::getClipByName(const std::string &clipname) noexcept
        {
            for(u32 i = 0; i<mClip.size(); ++i)
                if(mClip[i]->clipName == clipname)
                    return mClip[i];
            return nullptr;
        }

        TheoraVideoClip* CVideoMaster::getTheoClipByName(const std::string &clipname) noexcept
        {
            for(u32 i = 0; i<mClip.size(); ++i)
                if(mClip[i]->clipName == clipname)
                    return mClip[i]->pTheoClip;
            return nullptr;
        }

        driver::texture* CVideoMaster::getTextureByName(const std::string &clipname) noexcept
        {
            for(u32 i = 0; i<mClip.size(); ++i)
                if(mClip[i]->clipName == clipname)
                    return mClip[i]->pTex;
            return nullptr;
        }

        driver::texture* CVideoMaster::addVideoClip(const std::string &filename, const std::string &clipname, bool repeatPlayback, bool startPlayback, bool preloadIntoRAM) noexcept
        {
            TheoraVideoClip *pClip = 0;

            if(filename != "" || clipname != "")
            {
                pClip = preloadIntoRAM ?
                    mVmgr->createVideoClip(new TheoraMemoryFileDataSource(filename), TH_RGB) :
                    mVmgr->createVideoClip(filename, TH_RGB);

                if(pClip)
                {
                    if(startPlayback) pClip->play();
                    else pClip->stop();

                    pClip->setAutoRestart(repeatPlayback);

                    const math::vec2i sizeClip(pClip->getWidth(), pClip->getHeight());

                    SVideoClip *temp = new SVideoClip();

                    temp->pTheoClip = pClip;
                    temp->pTex      = new driver::texture(sizeClip, driver::TXFMT_RGB);
                    temp->pTex->createIdentifier(context);
                    temp->clipName  = clipname;

                    mClip.push_back(temp);
                    return temp->pTex;
                }
            }

            if(pClip)
                mVmgr->destroyVideoClip(pClip);

            return nullptr;
        }

        bool CVideoMaster::removeVideoClip(const std::string &clipname, bool RemoveTexture) noexcept
        {
            u32 clipIndex;
            SVideoClip* pClip = getClipByName(clipname, clipIndex);
            if(!pClip) return false;

            if(pClip->pTheoClip)
                mVmgr->destroyVideoClip(pClip->pTheoClip);

            if(pClip->pTex && RemoveTexture)
                delete pClip->pTex;

            delete pClip;
            mClip.erase(mClip.begin()+clipIndex);
            return true;
        }

        void CVideoMaster::removeVideoClipAll(bool RemoveTexture) noexcept
        {
            while(!mClip.empty())
            {
                SVideoClip* pClip = mClip.back();
                if(pClip)
                {
                    if(pClip->pTheoClip)
                        mVmgr->destroyVideoClip(pClip->pTheoClip);
                    if(pClip->pTex && RemoveTexture)
                        delete pClip->pTex;
                    delete pClip;
                }
                mClip.erase(mClip.end()-1);
            }
        }
    }
}
#endif
