#pragma once
#include "common/concepts.h"
#include <cstdlib>
#include "../KHR/khrplatform.h"

namespace EurekaUI
{
    namespace GraphicLib
    {
        using GLint = int;
        using GLsizei = int;
        using GLvoid = void;
        using GLchar = char;
        using GLshort = short;
        using GLenum = unsigned int;
        using GLuint = unsigned int;
        using GLbitfield = unsigned int;
        using GLboolean = unsigned char;
        using GLushort = unsigned short;
        using GLbyte = khronos_int8_t;
        using GLubyte = khronos_uint8_t;
        using GLfixed = khronos_int32_t;
        using GLint64 = khronos_int64_t;
        using GLfloat = khronos_float_t;
        using GLclampf = khronos_float_t;
        using GLuint64 = khronos_uint64_t;
        using GLintptr = khronos_intptr_t;
        using GLsizeiptr = khronos_ssize_t;

        class Texture : public Noncopyable, public Nonmoveable
        {
        public:
            Texture();
            ~Texture();

            enum class PixFormat : size_t
            {
                Alpha = 0x1906, RGB, RGBA, Luminance, LuminanceAlpha
            };
            enum class DataFormat : size_t
            {
                UByte = 0x1401, UShort4444 = 0x8033, UShort5551, UShort565
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

        private:
            using ActiveTexture =
            void(GLenum texture);

            using BindTexture =
            void(GLenum target, GLuint texture);

            using TexImage2D =
            void(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border,
                 GLenum format, GLenum type, const void *pixels);

            using TexSubImage2D =
            void(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format,
                 GLenum type, const void *pixels);

            using CompressedTexImage2D =
            void(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border,
                 GLsizei imageSize, const void *data);

            using CompressedTexSubImage2D =
            void(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format,
                 GLsizei imageSize, const void *data);

            using CopyTexImage2D =
            void(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height,
                 GLint border);

            using GenTextures =
            void(GLsizei n, GLuint *textures);

            using DeleteTextures =
            void(GLsizei n, const GLuint *textures);

            static GenTextures *fGenTextures;
            static DeleteTextures *fDeleteTextures;
            static TexImage2D *fTexImage2D;
            static TexSubImage2D *fTexSubImage2D;
            static CompressedTexImage2D *fCompressedTexImage2D;
            static CompressedTexSubImage2D *fCompressedTexSubImage2D;
            static ActiveTexture *fActiveTexture;
            static BindTexture *fBindTexture;
            static CopyTexImage2D *fCopyTexImage2D;
            GLenum mHandle;
        };

        class FrameBuffer : public Noncopyable, public Nonmoveable
        {
        public:
            enum class Attachment
            {
            };

            void bind()
            {};

            void attach(Attachment attachment, Texture &texture)
            {};

            void restoreDefault()
            {};

        protected:
            constexpr FrameBuffer()
            {}

            ~FrameBuffer()
            {}
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
