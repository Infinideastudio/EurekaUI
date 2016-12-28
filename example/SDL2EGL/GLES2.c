#include <SDL2/SDL.h>
#include "GLES2.h"
#ifdef DO_GET_GETFUNCTIONS
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETERRORPROC glGetError;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLCLEARCOLORPROC glClearColor;
PFNGLVIEWPORTPROC glViewport;
PFNGLCLEARPROC glClear;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLDRAWARRAYSPROC glDrawArrays;
PFNGLGETSTRINGPROC glGetString;
#endif

void LoadFuncs()
{
#ifdef DO_GET_GETFUNCTIONS
    glGetShaderiv = SDL_GL_GetProcAddress("glGetShaderiv");
    glDeleteShader = SDL_GL_GetProcAddress("glDeleteShader");
    glGetProgramiv = SDL_GL_GetProcAddress("glGetProgramiv");
    glCreateShader = SDL_GL_GetProcAddress("glCreateShader");
    glShaderSource = SDL_GL_GetProcAddress("glShaderSource");
    glCompileShader = SDL_GL_GetProcAddress("glCompileShader");
    glGetShaderInfoLog = SDL_GL_GetProcAddress("glGetShaderInfoLog");
    glGetError = SDL_GL_GetProcAddress("glGetError");
    glGetProgramInfoLog = SDL_GL_GetProcAddress("glGetProgramInfoLog");
    glDeleteProgram = SDL_GL_GetProcAddress("glDeleteProgram");
    glCreateProgram = SDL_GL_GetProcAddress("glCreateProgram");
    glDeleteShader = SDL_GL_GetProcAddress("glDeleteShader");
    glAttachShader = SDL_GL_GetProcAddress("glAttachShader");
    glLinkProgram = SDL_GL_GetProcAddress("glLinkProgram");
    glClearColor = SDL_GL_GetProcAddress("glClearColor");
    glViewport = SDL_GL_GetProcAddress("glViewport");
    glClear = SDL_GL_GetProcAddress("glClear");
    glUseProgram = SDL_GL_GetProcAddress("glUseProgram");
    glVertexAttribPointer = SDL_GL_GetProcAddress("glVertexAttribPointer");
    glEnableVertexAttribArray = SDL_GL_GetProcAddress("glEnableVertexAttribArray");
    glDrawArrays = SDL_GL_GetProcAddress("glDrawArrays");
    glGetString = SDL_GL_GetProcAddress("glGetString");
#endif
}
