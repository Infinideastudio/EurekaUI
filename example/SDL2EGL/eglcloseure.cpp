#include "eglcloseure.h"
#include <SDL2/SDL.h>

namespace EGLCloseures
{
    Texture::FNGLTEXIMAGE2DPROC Texture::fTexImage2D;
    
    void Texture::coInitialize()
    {
        fTexImage2D = reinterpret_cast<Texture::FNGLTEXIMAGE2DPROC>(SDL_GL_GetProcAddress("glTexImage2D"));
    }

    unsigned int Texture::format2uint(Format fmt)
    {
        switch (fmt)
        {
        case Format::Alpha: return GL_ALPHA; 
        case Format::RGB: return GL_RGB;
        case Format::RGBA: return GL_RGBA;
        case Format::Luminance: return GL_LUMINANCE;
        case Format::LuminanceAlpha: return GL_LUMINANCE_ALPHA;
        }
        return 0;
    }

    unsigned int Texture::data2uint(Data dat)
    {
        switch (dat)
        {
        case Data::UByte: return GL_UNSIGNED_BYTE;
        case Data::UShort4444: return GL_UNSIGNED_SHORT_4_4_4_4;
        case Data::UShort5551: return GL_UNSIGNED_SHORT_5_5_5_1;
        case Data::UShort565: return GL_UNSIGNED_SHORT_5_6_5;
        }
        return 0;
    }

    void Texture::texData(int MipmapLevel, Format internalformat, size_t width, size_t height, Format format, Data type, void * data)
    {
        fTexImage2D(mHandle, MipmapLevel, format2uint(internalformat),
            width, height, 0, format2uint(format), data2uint(type), data);
    }

}
