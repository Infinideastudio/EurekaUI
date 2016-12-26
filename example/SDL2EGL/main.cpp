#include <SDL2/SDL.h>
#include <GLES2/gl2.h>
#include <iostream>
#include "shader_utils.h"

SDL_Window *win;
SDL_GLContext ctx;

void InitVideoDriver()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    win = SDL_CreateWindow("", 400, 400, 400, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    ctx = SDL_GL_CreateContext(win);
}


class HelloTriangleSample
{
public:
    HelloTriangleSample()
    {}

    virtual bool initialize()
    {
        const std::string vs =
                "attribute vec4 vPosition;"
                        "void main()"
                        "{"
                        "gl_Position = vPosition;"
                        "}";

        const std::string fs =
                "precision mediump float;"
                        "void main()"
                        "{"
                        "gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
                        "}";

        mProgram = CompileProgram(vs, fs);
        if (!mProgram)
        {
            return false;
        }

        glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

        return true;
    }

    virtual void destroy()
    {
        glDeleteProgram(mProgram);
    }

    virtual void draw()
    {
        GLfloat vertices[] =
                {
                        0.0f, 0.5f, 0.0f,
                        -0.5f, -0.5f, 0.0f,
                        0.5f, -0.5f, 0.0f,
                };

        // Set the viewport
        glViewport(0, 0, 400, 400);

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the program object
        glUseProgram(mProgram);

        // Load the vertex data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    GLuint mProgram;
};


int main(int argc, char *argv[])
{
    SDL_Init(0);
    HelloTriangleSample sample;
    InitVideoDriver();
    sample.initialize();
    std::cout << glGetString(GL_VERSION) << std::endl;
    bool done = false;
    while (!done)
    {
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;
                default:
                    break;
            }
        }
        SDL_GL_MakeCurrent(win, ctx);
        sample.draw();
        SDL_GL_SwapWindow(win);
    }
    SDL_DestroyWindow(win);
    SDL_Quit();
    sample.destroy();
    return 0;
}

