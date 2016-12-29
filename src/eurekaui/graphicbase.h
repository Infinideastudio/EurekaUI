#pragma once
#include "common/concepts.h"

namespace EurekaUI
{
    namespace GraphicLib
    {
        class Texture :public Noncopyable
        {
        public:
            enum class Format :size_t { Alpha, RGB, RGBA, Luminance, LuminanceAlpha };
            enum class Data :size_t { UByte, UShort4444, UShort5551, UShort565 };
            virtual ~Texture() {}
            virtual void texData(
                int MipmapLevel, Format internalformat, 
                size_t width, size_t height,
                Format format, Data type, void *data) = 0;
        };

        class FrameBuffer :public Noncopyable
        {
        public:
            enum class Attachment {};
            virtual ~FrameBuffer() {}
            virtual void bind() = 0;
            virtual void attach(Attachment attachment, Texture& texture) = 0;
            virtual void restoreDefault() = 0;
        protected:
            constexpr FrameBuffer() {}
            constexpr FrameBuffer(FrameBuffer&&) {}
            FrameBuffer& operator = (FrameBuffer&&) { return *this; }
        };

        class Context :public Noncopyable
        {
        public:
            virtual ~Context() {}
            virtual void activeTexture(size_t i) = 0;
            virtual Texture& createTexture() = 0;
            virtual FrameBuffer& createFrameBuffer() = 0;
        protected:
            constexpr Context() {}
            constexpr Context(Context&&) {}
            Context& operator = (Context&&) { return *this; }
        };
    }
}
