#include "video/base.h"
namespace EurekaUI
{
    namespace GraphicLib
    {
        Driver* InitDriverOES(void* dat);
        Driver* InitDriver(GraphicType type, void* dat)
        {
            switch (type)
            {
            case GraphicType::OES:
                return InitDriverOES(dat);
            default:
                break;
            }
            return nullptr;
        }
    }
}
