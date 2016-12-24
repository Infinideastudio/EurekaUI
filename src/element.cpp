#include "eurekaui/element.h"

namespace EurekaUI
{
    Element::Element(Element *parent)
        :mParent(parent)
    {
    }
    
    Element::~Element()
    {
        // Free memory;
        for(auto child:mChildren)
        {
            delete child;
        }
    }
}
