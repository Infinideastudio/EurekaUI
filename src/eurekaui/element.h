#ifndef EUREKAUI_ELEMENT_H
#define EUREKAUI_ELEMENT_H
#include <unordered_map>
#include <string>
#include <list>

namespace EurekaUI
{
    class Context;
    /**
     *
     */
    class Element
    {
        friend class Context;
    public:
        template<class T> Element *createChild()
        {
            Element *e = new T(*this);
            mChildren.push_back(e);
            return e;
        };
        
        template<class T> Element *createChild(const std::string &&Id)
        {
            Element *e = createChild<T>();
            mChildrenById[Id] = e;
            return e;
        }
        
        Element *getParent(){return mParent;}
    private:
        explicit Element(Element *parent);
        ~Element();
        
        Element *mParent;
        std::list<Element*> mChildren;
        std::unordered_map<std::string,Element*> mChildrenById;
    };
}

#endif
