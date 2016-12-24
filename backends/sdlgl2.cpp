#include <SDL2/SDL.h>
#include <GL/glew.h>

class SDLGL2Window
{
public:
    SDLGL2Window(const std::string &name, int width, int height, int left, int top)
    {
        mWindow = SDL_CreateWindow(name.c_str(), left, top, width, height);
        mContext = SDL_GL_CreateContext(mWindow);
        SDL_GL_SetSwapInterval(1);
        glGenFramebuffers(1, &mFBO);
    }

    void beginUpdate()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    }

    void endUpdate()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void bindBuffer(GLuint texture, int width, int height)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
        glViewport(0, 0, width, height);
    }

    ~SDLGL2Window()
    {
        glDeleteFramebuffers(1, &mFBO);
        SDL_GL_DeleteContext(mContext);
        SDL_DestroyWindow(mWindow);
    }

private:
    SDL_Window *mWindow;
    SDL_GLContext mContext;
    GLuint mFBO;
};

void InitSDLGL2()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

void *SDLGL2CreateWindow(const std::string &name, int width, int height, int left, int top)
{
    return new SDLGL2Window(name, width, height, let, top);
}

void SDLGL2BeginUpdate(void *window)
{
    reinterpret_cast<SDLGL2Window *>(window)->beginUpdate();
}

void SDLGL2EndUpdate(void *window)
{
    reinterpret_cast<SDLGL2Window *>(window)->endUpdate();
}

void SDLGL2BindBuffer(void *window, void *buffer, int width, int height)
{
    reinterpret_cast<SDLGL2Window *>(window, reinterpret_cast<GLuint>(buffer, width, height));
}

void SDLGL2UnBindBuffer(void *window)
{
}

void SDLGL2DestoryWindow(void *window)
{
    delete reinterpret_cast<SDLGL2Window *>(window);
}

