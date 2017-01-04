#include "eurekaui/graphic.h"
#include "GLES2/gl2.h"
#include <functional>

namespace EurekaUI
{
    namespace GraphicLib
    {
        //////////////////////////////
        // Begin Texture Object
        //////////////////////////////
        static GLuint gCurrentTex = 0;
        PFNGLTEXIMAGE2DPROC fTexImage2D = nullptr;
        PFNGLTEXSUBIMAGE2DPROC fTexSubImage2D = nullptr;
        PFNGLCOMPRESSEDTEXIMAGE2DPROC fCompressedTexImage2D = nullptr;
        PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC fCompressedTexSubImage2D = nullptr;
        PFNGLACTIVETEXTUREPROC fActiveTexture = nullptr;
        PFNGLBINDTEXTUREPROC fBindTexture = nullptr;
        PFNGLCOPYTEXIMAGE2DPROC fCopyTexImage2D = nullptr;
        PFNGLCOPYTEXSUBIMAGE2DPROC fCopyTexSubImage2D = nullptr;
        PFNGLTEXPARAMETERIPROC fTexParameteri = nullptr;
        PFNGLGENERATEMIPMAPPROC fGenerateMipmap = nullptr;
        PFNGLGENTEXTURESPROC fGenTextures = nullptr;
        PFNGLDELETETEXTURESPROC fDeleteTextures = nullptr;

        Texture::Texture()
        {
            fGenTextures(1, &mHandle);
        }

        Texture::~Texture()
        {
            if (mHandle != 0) fDeleteTextures(1, &mHandle);
        }

        void Texture::activeTex(int ID)
        {
            fActiveTexture(GL_TEXTURE0 + ID);
        }

        void Texture::bind()
        {
            if (gCurrentTex != mHandle) 
            {
                fBindTexture(GL_TEXTURE_2D, mHandle); 
                gCurrentTex = mHandle;
            }
        }

        void Texture::texData(int MipmapLevel, PixFormat internalformat, size_t width, size_t height, PixFormat format,
                              DataFormat type, const void *data)
        {
            bind();
            fTexImage2D(GL_TEXTURE_2D, MipmapLevel, static_cast<unsigned int>(internalformat),
                        width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(type), data);
        }


        void Texture::texSubData(int level, int xoffset, int yoffset,
                                 size_t width, size_t height, PixFormat format, DataFormat type,
                                 const void *pixels)
        {
            bind();
            fTexSubImage2D(GL_TEXTURE_2D, level, xoffset, yoffset, width, height, static_cast<unsigned int>(format),
                           static_cast<unsigned int>(type), pixels);
        }

        void
        Texture::texDataCompressed(int level, PixFormat internalformat, size_t width, size_t height, size_t imageSize,
                                   const void *data)
        {
            bind();
            fCompressedTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(internalformat), width, height, 0, imageSize, data);
        }

        void Texture::texSubDataCompressed(int level, int xoffset, int yoffset, size_t width, size_t height,
                                           PixFormat format, size_t imageSize, const void *data)
        {
            bind();
            fCompressedTexSubImage2D(GL_TEXTURE_2D, level, xoffset, yoffset, width, height, static_cast<unsigned int>(format), imageSize, data);
        }


        void Texture::copyTexData(int level, PixFormat internalformat, int x, int y, size_t width, size_t height)
        {
            bind();
            fCopyTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(internalformat), x, y, width, height, 0);
        }

        void Texture::copyTexSubData(int level, int xoffset, int yoffset, int x, int y, size_t width, size_t height)
        {
            bind();
            fCopyTexSubImage2D(GL_TEXTURE_2D, level, xoffset, yoffset, x, y, width, height);
        }

        void Texture::setWarpS(WarpMode mode)
        {
            bind();
            fTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(mode));
        }

        void Texture::setWarpT(WarpMode mode)
        {
            bind();
            fTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(mode));
        }

        void Texture::setMinFilter(MinFilter filter)
        {
            bind();
            fTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(filter));
        }

        void Texture::setMagFilter(MagFilter filter)
        {
            bind();
            fTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(filter));
        }

        void Texture::generateMipmap()
        {
            bind();
            fGenerateMipmap(GL_TEXTURE_2D);
        }

        //////////////////////////////
        // End Texture Object
        //////////////////////////////
        std::function<void* (const char*)> fGLGetFunction;
        template <class T>
        inline T getGLFunc(const char* name)
        {
            return reinterpret_cast<T>(fGLGetFunction(name));
        }

        void coInitialize(std::function<void* (const char*)> function)
        {
            fGLGetFunction = function;
            fTexImage2D = getGLFunc<PFNGLTEXIMAGE2DPROC>("glTexImage2D");
            fTexSubImage2D = getGLFunc<PFNGLTEXSUBIMAGE2DPROC>("glTexSubImage2D");
            fCompressedTexImage2D = getGLFunc<PFNGLCOMPRESSEDTEXIMAGE2DPROC>("glCompressedTexImage2D");
            fCompressedTexSubImage2D = getGLFunc<PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC>("glCompressedTexSubImage2D");
            fActiveTexture = getGLFunc<PFNGLACTIVETEXTUREPROC>("glActiveTexture");
            fBindTexture = getGLFunc<PFNGLBINDTEXTUREPROC>("glBindTexture");
            fCopyTexImage2D = getGLFunc<PFNGLCOPYTEXIMAGE2DPROC>("glCopyTexImage2D");
            fCopyTexSubImage2D = getGLFunc<PFNGLCOPYTEXSUBIMAGE2DPROC>("glCopyTexSubImage2D");
            fTexParameteri = getGLFunc<PFNGLTEXPARAMETERIPROC>("glTexParameteri");
            fGenerateMipmap = getGLFunc<PFNGLGENERATEMIPMAPPROC>("glGenerateMipmap");
            fGenTextures = getGLFunc<PFNGLGENTEXTURESPROC>("glGenTextures");
            fDeleteTextures = getGLFunc<PFNGLDELETETEXTURESPROC>("glDeleteTextures");
        }

    }
}
