#pragma once
#include "common/concepts.h"

namespace EurekaUI
{
    namespace GraphicLib
    {
        class Texture :public Noncopyable
        {
        public:
            enum class Format { Alpha, RGB, RGBA, Luminance, LuminanceAlpha };

        };

        class FrameBuffer :public Noncopyable
        {
        public:
            enum class Attachment {};
            FrameBuffer() = default;
            virtual void bind() = 0;
            virtual void attach(Attachment attachment, Texture& texture) = 0;
            virtual void restoreDefault() = 0;
        };
    }
}
