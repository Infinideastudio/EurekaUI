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
            Texture();
            Texture(Texture&& rhs) : mHandle(rhs.mHandle) { rhs.mHandle = 0; }
            Texture& operator = (Texture&& rhs) { mHandle = rhs.mHandle; rhs.mHandle = 0; }
            ~Texture();

            enum class PixFormat : size_t
            {
                Alpha = 0x1906, RGB, RGBA, Luminance, LuminanceAlpha
            };
            enum class DataFormat : size_t
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

            static void activeTex(int ID);

            void bind();

            void texData(int MipmapLevel, PixFormat internalformat, size_t width, size_t height, PixFormat format,
                         DataFormat type, const void *data);

            void texSubData(int level, int xoffset, int yoffset, size_t width, size_t height, PixFormat format,
                            DataFormat type, const void *pixels);


            void texDataCompressed(int level, PixFormat internalformat, size_t width, size_t height, size_t imageSize,
                                   const void *data);

            void
            texSubDataCompressed(int level, int xoffset, int yoffset, size_t width, size_t height, PixFormat format,
                                 size_t imageSize, const void *data);

            void copyTexData(int level, PixFormat internalformat, int x, int y, size_t width, size_t height);

            void copyTexSubData(int level, int xoffset, int yoffset, int x, int y, size_t width, size_t height);

            void setWarpS(WarpMode mode);

            void setWarpT(WarpMode mode);

            void setMinFilter(MinFilter filter);

            void setMagFilter(MagFilter filter);

            void generateMipmap();
        private:
            unsigned int mHandle;
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

        class Context : public Noncopyable, public Nonmoveable
        {
        public:
            void activeTexture(size_t i)
            {}

        protected:
            constexpr Context()
            {}

            ~Context()
            {}
        };
    }
}
