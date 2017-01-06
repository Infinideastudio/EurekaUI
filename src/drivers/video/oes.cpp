#include "base.h"
#include "GLES2/gl2.h"
#include <functional>

namespace EurekaUI
{
    namespace GraphicLib
    {
        class DriverOES :public Driver
        {
        public:
            GLuint gCurrentTex = 0;
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
            using tGetter = void* (const char*);
            template <class T>
            inline T getGLFunc(const char* name)
            {
                return reinterpret_cast<T>(mGetter(name));
            }

            DriverOES(tGetter* function)
                :mGetter(function)
            {
                // Texture
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

            void activeTexture(size_t i) override
            {
                fActiveTexture(GL_TEXTURE0 + i);
            }


            //////////////////////////////
            // Begin Texture Object
            //////////////////////////////
            class TextureOES :public Texture
            {
            public:
                TextureOES(DriverOES* ctx) : mContext(ctx)
                {
                    mContext->fGenTextures(1, &mHandle);
                }

                ~TextureOES()
                {
                    if (mHandle != 0) mContext->fDeleteTextures(1, &mHandle);
                }

                TextureOES(TextureOES&& rhs) : mHandle(rhs.mHandle) { rhs.mHandle = 0; }

                TextureOES& operator = (TextureOES&& rhs) { mHandle = rhs.mHandle; rhs.mHandle = 0; }

                void bind() override
                {
                    if (mContext->gCurrentTex != mHandle)
                    {
                        mContext->fBindTexture(GL_TEXTURE_2D, mHandle);
                        mContext->gCurrentTex = mHandle;
                    }
                }

                void texData(int MipmapLevel, PixFormat internalformat, size_t width, size_t height, PixFormat format,
                    DataFormat type, const void *data) override
                {
                    bind();
                    mContext->fTexImage2D(GL_TEXTURE_2D, MipmapLevel, static_cast<unsigned int>(internalformat),
                        width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(type), data);
                }


                void texSubData(int level, int xoffset, int yoffset,
                    size_t width, size_t height, PixFormat format, DataFormat type,
                    const void *pixels) override
                {
                    bind();
                    mContext->fTexSubImage2D(GL_TEXTURE_2D, level, xoffset, yoffset, width, height, static_cast<unsigned int>(format),
                        static_cast<unsigned int>(type), pixels);
                }

                void
                    texDataCompressed(int level, PixFormat internalformat, size_t width, size_t height, size_t imageSize,
                        const void *data) override
                {
                    bind();
                    mContext->fCompressedTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(internalformat), width, height, 0, imageSize, data);
                }

                void texSubDataCompressed(int level, int xoffset, int yoffset, size_t width, size_t height,
                    PixFormat format, size_t imageSize, const void *data) override
                {
                    bind();
                    mContext->fCompressedTexSubImage2D(GL_TEXTURE_2D, level, xoffset, yoffset, width, height, static_cast<unsigned int>(format), imageSize, data);
                }


                void copyTexData(int level, PixFormat internalformat, int x, int y, size_t width, size_t height) override
                {
                    bind();
                    mContext->fCopyTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(internalformat), x, y, width, height, 0);
                }

                void copyTexSubData(int level, int xoffset, int yoffset, int x, int y, size_t width, size_t height) override
                {
                    bind();
                    mContext->fCopyTexSubImage2D(GL_TEXTURE_2D, level, xoffset, yoffset, x, y, width, height);
                }

                void setWarpS(WarpMode mode) override
                {
                    bind();
                    mContext->fTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(mode));
                }

                void setWarpT(WarpMode mode) override
                {
                    bind();
                    mContext->fTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(mode));
                }

                void setMinFilter(MinFilter filter) override
                {
                    bind();
                    mContext->fTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(filter));
                }

                void setMagFilter(MagFilter filter) override
                {
                    bind();
                    mContext->fTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(filter));
                }

                void generateMipmap() override
                {
                    bind();
                    mContext->fGenerateMipmap(GL_TEXTURE_2D);
                }
            private:
                GLuint mHandle;
                DriverOES* mContext;
            };

            Texture* createTexture() override
            {
                return new TextureOES(this);
            }

            void deleteTexture(Texture* tex) override
            {
                delete reinterpret_cast<TextureOES*>(tex);
            }

            //////////////////////////////
            // End Texture Object
            //////////////////////////////

        private:
            tGetter* mGetter;
        };

        Driver* InitDriverOES(void* dat)
        {
            return new DriverOES(reinterpret_cast<DriverOES::tGetter*>(dat));
        }

    }
}
