#ifndef EUREKAUI_ELEMENT_H
#define EUREKAUI_ELEMENT_H
#include <unordered_map>
#include <string>
#include <list>
#include <cassert>

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
        template<class T> Element* createChild()
        {
            Element* e = new T(*this);
            mChildren.push_back(e);
            return e;
        };
        
        template<class T> Element* createChild(const std::string& id)
        {
            assert(mChildrenById.find(id) == mChildrenById.end());
            Element* e = createChild<T>();
            mChildrenById[id] = e;
            return e;
        }
        
        Element* getParent() const noexcept { return mParent; }
    private:
        explicit Element(Element* parent);
        ~Element();
        
        Element* mParent;
        std::list<Element*> mChildren;
        std::unordered_map<std::string, Element*> mChildrenById;
    };
}

#endif
