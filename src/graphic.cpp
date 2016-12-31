#include "eurekaui/graphic.h"

namespace EurekaUI
{
    namespace GraphicLib
    {
        Texture::TexImage2D *Texture::fTexImage2D = nullptr;
        Texture::TexSubImage2D *Texture::fTexSubImage2D = nullptr;
        Texture::CompressedTexImage2D *Texture::fCompressedTexImage2D = nullptr;
        Texture::CompressedTexSubImage2D *Texture::fCompressedTexSubImage2D = nullptr;
        Texture::ActiveTexture *Texture::fActiveTexture = nullptr;
        Texture::BindTexture *Texture::fBindTexture = nullptr;
        Texture::CopyTexImage2D *Texture::fCopyTexImage2D = nullptr;
        Texture::GenTextures *Texture::fGenTextures = nullptr;
        Texture::DeleteTextures *Texture::fDeleteTextures = nullptr;


        Texture::Texture()
        {
            fGenTextures(1, &mHandle);
        }

        Texture::~Texture()
        {
            fDeleteTextures(1, &mHandle);
        }

        void Texture::activeTex(int ID)
        {
            fActiveTexture(0x84C0 + ID);
        }

        void Texture::bind()
        {
            fBindTexture(0x0DE1, mHandle);
        }

        void Texture::texData(int MipmapLevel, PixFormat internalformat, size_t width, size_t height, PixFormat format,
                              DataFormat type, const void *data)
        {
            fTexImage2D(mHandle, MipmapLevel, static_cast<size_t>(internalformat),
                        width, height, 0, static_cast<size_t>(format), static_cast<size_t>(type), data);
        }


        void Texture::texSubData(int level, int xoffset, int yoffset,
                                 size_t width, size_t height, PixFormat format, DataFormat type,
                                 const void *pixels)
        {
            fTexSubImage2D(mHandle, level, xoffset, yoffset, width, height, static_cast<size_t>(format),
                           static_cast<size_t>(type), pixels);
        }

        void
        Texture::texDataCompressed(int level, PixFormat internalformat, size_t width, size_t height, size_t imageSize,
                                   const void *data)
        {
            fCompressedTexImage2D(mHandle, level, static_cast<size_t>(internalformat), width, height, 0, imageSize, data);
        }

        void Texture::texSubDataCompressed(int level, int xoffset, int yoffset, size_t width, size_t height,
                                           PixFormat format, size_t imageSize, const void *data)
        {
            fCompressedTexSubImage2D(mHandle, level, xoffset, yoffset, width, height, static_cast<size_t>(format), imageSize, data);
        }


        void Texture::copyTexData(int level, PixFormat internalformat, int x, int y, size_t width, size_t height)
        {
            fCopyTexImage2D(mHandle, level, static_cast<size_t>(internalformat), x, y, width, height, 0);
        }

    }
}
