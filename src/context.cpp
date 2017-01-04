#include "eurekaui/context.h"

namespace EurekaUI
{
    namespace GraphicLib
    {
        void coInitialize(std::function<void* (const char*)> fGLGetFunction);
    }

    Context::Context(std::function<void* (const char*)> fGLGetFunction)
            : mRoot(nullptr)
    {
        GraphicLib::coInitialize(fGLGetFunction);
    }
    
}
