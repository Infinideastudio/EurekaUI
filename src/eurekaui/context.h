#ifndef EUREKAUI_CONTEXT_H
#define EUREKAUI_CONTEXT_H
#include <vector>
#include <functional>
#include "element.h"

namespace EurekaUI
{
    /** EurekaUI context
     *
     */
    class Context
    {
    public:
        explicit Context(std::function<void* (const char*)> fGLGetFunction);
        Element* root() { return &mRoot; }
    private:
        Element mRoot;
    };
}

#endif
