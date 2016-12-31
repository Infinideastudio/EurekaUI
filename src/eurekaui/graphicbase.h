#pragma once
#include "common/concepts.h"
#include <cstdlib>

namespace EurekaUI
{
    namespace GraphicLib
    {
        class Texture :public Noncopyable
        {
        public:
            enum class Format :size_t { Alpha, RGB, RGBA, Luminance, LuminanceAlpha };
            enum class Data :size_t { UByte, UShort4444, UShort5551, UShort565 };
            void texData(int MipmapLevel, Format internalformat, size_t width, size_t height, Format format, Data type, void *data) = 0;
        protected:
            constexpr Texture() {}
            constexpr FrameBuffer(FrameBuffer&&) {}
            ~Texture();
            ~FrameBuffer() {}
            FrameBuffer& operator = (FrameBuffer&&) { return *this; }
        };

        class FrameBuffer :public Noncopyable
        {
        public:
            enum class Attachment {};
            void bind() = 0;
            void attach(Attachment attachment, Texture& texture) = 0;
            void restoreDefault() = 0;
        protected:
            constexpr FrameBuffer() {}
            constexpr FrameBuffer(FrameBuffer&&) {}
            ~FrameBuffer() {}
            FrameBuffer& operator = (FrameBuffer&&) { return *this; }
        };

        class Context :public Noncopyable
        {
        public:
            void activeTexture(size_t i) = 0;
            Texture& createTexture() = 0;
            FrameBuffer& createFrameBuffer() = 0;
        protected:
            constexpr Context() {}
            constexpr Context(Context&&) {}
            ~Context() {}
            Context& operator = (Context&&) { return *this; }
        };
    }
}
