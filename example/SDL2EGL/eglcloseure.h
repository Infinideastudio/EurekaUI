#pragma once
#include <eurekaui/graphicbase.h>
#include <GLES2/gl2.h>

namespace EGLCloseures
{
    class Texture :public EurekaUI::GraphicLib::Texture
    {
    public:
        void texData(int MipmapLevel, Format internalformat,
            size_t width, size_t height, Format format, Data type, void *data) override;
        static void coInitialize();
    private:
        unsigned int mHandle;
        unsigned int format2uint(Format fmt);
        unsigned int data2uint(Data dat);
        typedef void (GL_APIENTRYP FNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
        static FNGLTEXIMAGE2DPROC fTexImage2D;
    };
}
