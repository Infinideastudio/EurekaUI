#pragma once
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
        template<class T, class... Ts>
        T& createChild(Ts &&... args)
        {
            T *newEle = new T(*this, std::forward<Ts>(args)...);
            mChildren.push_back(newEle);
            return *newEle;
        };

        template<class T, class... Ts>
        T& createChildWithId(const std::string &id, Ts &&... args)
        {
            assert(mChildrenById.find(id) == mChildrenById.end());
            T *newEle = &createChild(std::forward<Ts>(args)...);
            mChildrenById.insert(std::pair<std::string, Element *>(id, newEle));
            return *newEle;
        }

        class RootGetParentException:public std::exception{};
        virtual Element &getParent() const throw(RootGetParentException)
        { if(mParent == nullptr) throw RootGetParentException();return *mParent; }
    private:
        explicit Element(Element *parent);
        ~Element();

        Element *mParent;
        std::list<Element*> mChildren;
        std::unordered_map<std::string, Element*> mChildrenById;
    };
    
}
