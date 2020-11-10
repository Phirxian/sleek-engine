#pragma once

#include "math.h"

namespace sleek
{
    namespace math
    {
        template <typename T>
        class aabbox2d
        {
            public:
                aabbox2d(const T x0, const T y0, const T x1, const T y1){ upperleft = vec2<T>(x0,y0); lowerright = vec2<T>(x1,y1); }
                aabbox2d(const vec2<T> &min = vec2<T>(0,0), const vec2<T> &max = vec2<T>(0,0)){ upperleft = min; lowerright = max; }
                virtual ~aabbox2d(){}

                inline void clear() { upperleft = lowerright = vec2<T>((T)0, (T)0); }
                inline void setUpperLeft(const vec2<T> &a) { upperleft = a; }
                inline void setLowerRight(const vec2<T> &a){ lowerright = a; }
                inline void setCenterBox(const vec2<T> &a) { upperleft = a-(getSize()/2); lowerright = a+(getSize()/2); }

                inline aabbox2d<T> operator + (const vec2<T> i) const { return aabbox2d<T>(upperleft+i, lowerright+i); }
                inline void operator = (const aabbox2d<T> &i) { upperleft = i.upperleft; lowerright = i.lowerright; }

                inline void setSizeFromUpperLeft(const vec2<T> &a) { lowerright = upperleft+a; }
                inline void setSizeFromLowerRight(const vec2<T> &a){ upperleft = lowerright-a; }
                inline void setSizeFromCenter(const vec2<T> &a)    { vec2<T> center = getCenter(); upperleft = center-(a/2); lowerright = center+(a/2); }

                inline vec2<T> getUpperLeft()  const { return upperleft; }
                inline vec2<T> getLowerRight() const { return lowerright; }
                inline vec2<T> getCenter()     const { return upperleft+getSize()/2; }
                inline vec2<T> getSize()       const { return lowerright-upperleft; }

                inline bool intersect(const vec2<T> &a) const
                {
                    return upperleft.x < a.x && lowerright.x > a.x &&
                           upperleft.y < a.y && lowerright.y > a.y;
                }
                inline aabbox2d<T> minimise() const
                {
                    vec2<T> size = getSize();
                    return aabbox2d<T>(vec2<T>(), size);
                }
                inline vec2<T> center() const
                {
                    vec2<T> pos = getCenter(), size = getSize();
                    return aabbox2d<T>(pos-(size/2), pos+(size/2));
                }
                inline void addInternalPoint(const math::vec2<T> &a)
                {
                    if(a.width > lowerright.width) lowerright.width = a.width;
                    if(a.height > lowerright.height) lowerright.width = a.height;

                    if(a.width < upperleft.width) upperleft.width = a.width;
                    if(a.height < upperleft.height) upperleft.width = a.height;
                }
                inline void merge(const aabbox2d<T> &a)
                {
                    addInternalPoint(a.upperleft);
                    addInternalPoint(a.lowerright);
                }
            public:
                vec2<T> upperleft, lowerright;
        };
        template <typename T>
        class aabbox3d
        {
            public:
                aabbox3d(const T x0, const T y0, const T z0, const T x1, const T y1, const T z1){ upperleft = vec3<T>(x0,y0,z0); lowerright = vec3<T>(x1,y1,z1); }
                aabbox3d(const vec3<T> &min = vec3<T>(0,0,0), const vec3<T> &max = vec3<T>(0,0,0)){ upperleft = min; lowerright = max; }
                virtual ~aabbox3d(){}

                inline void clear() { upperleft = lowerright = vec3<T>((T)0, (T)0, T(0)); }
                inline void setUpperLeft(const vec3<T> &a) { upperleft = a; }
                inline void setLowerRight(const vec3<T> &a){ lowerright = a; }
                inline void setCenterBox(const vec3<T> &a) { upperleft = a-(getSize()/2); lowerright = a+(getSize()/2); }

                inline aabbox3d<T> operator + (const vec3<T> &i) const { return aabbox3d<T>(upperleft+i, lowerright+i); }
                inline void operator = (const aabbox3d<T> &i) { upperleft = i.upperleft; lowerright = i.lowerright; }

                inline void setSizeFromUpperLeft(const vec3<T> &a) { lowerright = upperleft+a; }
                inline void setSizeFromLowerRight(const vec3<T> &a){ upperleft = lowerright-a; }
                inline void setSizeFromCenter(const vec3<T> &a)    { vec3<T> center = getCenter(); upperleft = center-(a/2); lowerright = center+(a/2); }

                inline vec3<T> getUpperLeft()  const { return upperleft; }
                inline vec3<T> getLowerRight() const { return lowerright; }
                inline vec3<T> getCenter()     const { return upperleft+(getSize()/vec3<T>(2)); }
                inline vec3<T> getSize()       const { return lowerright-upperleft; }

                inline bool intersect(const vec3<T> &a) const
                {
                    if(upperleft < a && lowerright > a)
                        return true;
                    return false;
                }
                inline aabbox3d<T> minimise() const
                {
                    vec2<T> size = getSize();
                    return aabbox2d<T>(vec2<T>(), size);
                }
                inline vec3<T> center() const
                {
                    vec2<T> pos = getCenter(), size = getSize();
                    return aabbox2d<T>(pos-(size/2), pos+(size/2));
                }
                inline void addInternalPoint(const math::vec3<T> &a)
                {
                    if(a.x > lowerright.x) lowerright.x = a.x;
                    if(a.y > lowerright.y) lowerright.x = a.y;
                    if(a.z > lowerright.z) lowerright.x = a.z;

                    if(a.x < upperleft.x) upperleft.x = a.x;
                    if(a.y < upperleft.y) upperleft.x = a.y;
                    if(a.z < upperleft.z) upperleft.x = a.z;
                }
                inline void merge(const aabbox3d<T> &a)
                {
                    addInternalPoint(a.upperleft);
                    addInternalPoint(a.lowerright);
                }
            public:
                vec3<T> upperleft, lowerright;
        };


        typedef aabbox2d<u8>  aabbox2dc;
        typedef aabbox2d<f32> aabbox2df;
        typedef aabbox2d<int> aabbox2di;
        typedef aabbox2d<u32> aabbox2du;
        typedef aabbox2d<s32> aabbox2ds;

        typedef aabbox3d<u8>  aabbox3dc;
        typedef aabbox3d<f32> aabbox3df;
        typedef aabbox3d<int> aabbox3di;
        typedef aabbox3d<u32> aabbox3du;
        typedef aabbox3d<s32> aabbox3ds;
    }
}
