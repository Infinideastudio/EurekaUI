#pragma once
#include <GLES2/gl2.h>
#ifdef __cplusplus
extern "C"
{
#endif
#ifdef DO_GET_GETFUNCTIONS
    extern PFNGLGETSHADERIVPROC glGetShaderiv;
    extern PFNGLDELETESHADERPROC glDeleteShader;
    extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
    extern PFNGLCREATESHADERPROC glCreateShader;
    extern PFNGLSHADERSOURCEPROC glShaderSource;
    extern PFNGLCOMPILESHADERPROC glCompileShader;
    extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
    extern PFNGLGETERRORPROC glGetError;
    extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
    extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
    extern PFNGLCREATEPROGRAMPROC glCreateProgram;
    extern PFNGLDELETESHADERPROC glDeleteShader;
    extern PFNGLATTACHSHADERPROC glAttachShader;
    extern PFNGLLINKPROGRAMPROC glLinkProgram;
    extern PFNGLCLEARCOLORPROC glClearColor;
    extern PFNGLVIEWPORTPROC glViewport;
    extern PFNGLCLEARPROC glClear;
    extern PFNGLUSEPROGRAMPROC glUseProgram;
    extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
    extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
    extern PFNGLDRAWARRAYSPROC glDrawArrays;
    extern PFNGLGETSTRINGPROC glGetString;
#endif
    void LoadFuncs();
#ifdef __cplusplus
}
#endif
