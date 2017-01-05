#pragma once
#include "common/concepts.h"
#include <cstdlib>

namespace EurekaUI
{
    namespace GraphicLib
    {
        class Texture : public Noncopyable
        {
        public:
            enum class PixFormat : unsigned int
            {
                Alpha = 0x1906, RGB, RGBA, Luminance, LuminanceAlpha
            };
            enum class DataFormat : unsigned int
            {
                UByte = 0x1401, UShort4444 = 0x8033, UShort5551, UShort565
            };
            enum class WarpMode : int
            {
                ClampToEdge = 0x812F, Repeat = 0x2901, MirroredRepeat = 0x8370
            };
            enum class MinFilter : int
            {
                Nearest = 0x2600, Linear, NearestMipMapNearest = 0x2700, 
                LinearMipMapNearest, NearestMipMapLinear, LinearMipMapLinear
            };
            enum class MagFilter : int
            {
                Nearest = 0x2600, Linear
            };
            virtual void bind() = 0;
            virtual void texData(int MipmapLevel, PixFormat internalformat, size_t width, size_t height, PixFormat format,
                         DataFormat type, const void *data) = 0;
            virtual void texSubData(int level, int xoffset, int yoffset, size_t width, size_t height, PixFormat format,
                            DataFormat type, const void *pixels) = 0;
            virtual void texDataCompressed(int level, PixFormat internalformat, size_t width, size_t height, size_t imageSize,
                                   const void *data) = 0;
            virtual void
            texSubDataCompressed(int level, int xoffset, int yoffset, size_t width, size_t height, PixFormat format,
                                 size_t imageSize, const void *data) = 0;
            virtual void copyTexData(int level, PixFormat internalformat, int x, int y, size_t width, size_t height) = 0;
            virtual void copyTexSubData(int level, int xoffset, int yoffset, int x, int y, size_t width, size_t height) = 0;
            virtual void setWarpS(WarpMode mode) = 0;
            virtual void setWarpT(WarpMode mode) = 0;
            virtual void setMinFilter(MinFilter filter) = 0;
            virtual void setMagFilter(MagFilter filter) = 0;
            virtual void generateMipmap();
        protected:
            virtual ~Texture() {}
        };

        class FrameBuffer : public Noncopyable, public Nonmoveable
        {
        public:
            enum class Attachment
            {
            };
            constexpr FrameBuffer()
            {}

            ~FrameBuffer()
            {}

            void bind()
            {};

            void attach(Attachment attachment, Texture &texture)
            {};

            void restoreDefault()
            {};

        protected:
        };

        class Driver : public Noncopyable
        {
        public:
            virtual void activeTexture(size_t i) = 0;
            virtual Texture* createTexture() = 0;
            virtual void deleteTexture(Texture* tex) = 0;
        protected:
            virtual ~Driver() {}
        };
    }
}
