#pragma once

#include <cassert>
#include <type_traits>

namespace EurekaUI
{
    namespace Common
    {
#ifdef NDEBUG
        void HalfSafe() noexcept {}
#else

        void HalfSafe()
        {}

#endif
    }
    namespace Iterators
    {
        template<class Tp, class Tc>
        class PlainPointerIterator
        {
        public:
#ifdef NDEBUG
            PlainPointerIterator(Tp cur, Tc*) noexcept :mPointer(cur) {}
#else

            PlainPointerIterator(Tp cur, Tc *parent) noexcept : mPointer(cur), mParent(parent)
            {}

#endif

            PlainPointerIterator operator+(size_t offset)
            const noexcept(noexcept(Common::HalfSafe))
            {
                assert(mPointer + offset <= mParent.end().mPointer);
                return PlainPointerIterator(mPointer + offset);
            }

            PlainPointerIterator operator-(size_t offset)
            const noexcept(noexcept(Common::HalfSafe))
            {
                assert(mPointer - offset >= mParent.begin().mPointer);
                return PlainPointerIterator(mPointer - offset);
            }

            PlainPointerIterator &operator+=(size_t offset)
            noexcept(noexcept(Common::HalfSafe))
            {
                assert(mPointer + offset <= mParent.end().mPointer);
                mPointer += offset;
                return *this;
            }

            PlainPointerIterator *operator-=(size_t offset)
            noexcept(noexcept(Common::HalfSafe))
            {
                assert(mPointer - offset >= mParent.begin().mPointer);
                mPointer -= offset;
                return *this;
            }

            PlainPointerIterator &operator++(size_t offset) noexcept(noexcept(Common::HalfSafe))
            {
                assert(*this != mParent.end());
                ++mPointer;
                return *this;
            }

            PlainPointerIterator &operator--(size_t offset) noexcept(noexcept(Common::HalfSafe))
            {
                assert(*this != mParent.begin());
                --mPointer;
                return *this;
            }

            PlainPointerIterator operator++(int) noexcept(noexcept(Common::HalfSafe))
            {
                assert(*this != mParent.end());
                return PlainPointerIterator(mPointer++);
            }

            PlainPointerIterator operator--(int) noexcept(noexcept(Common::HalfSafe))
            {
                assert(*this != mParent.begin());
                return PlainPointerIterator(mPointer--);
            }

            std::remove_pointer<Tp> &operator[](size_t offset) noexcept(noexcept(Common::HalfSafe))
            {
                assert(mPointer + offset < mParent.end().mPointer);
                return mPointer[offset];
            }

            Tp operator->() noexcept
            {
                return mPointer;
            }

            template<class T, class U, class Base>
            friend bool operator==(PlainPointerIterator<T, Base> left,
                                   PlainPointerIterator<U, Base> right)
            noexcept(noexcept(Common::HalfSafe))
            {
                assert(left.mParent == right.mParent);
                return (left.mPointer == right.mPointer);
            }

            template<class T, class U, class Base>
            friend bool operator!=(PlainPointerIterator<T, Base> left,
                                   PlainPointerIterator<U, Base> right)
            noexcept(noexcept(Common::HalfSafe))
            {
                assert(left.mParent == right.mParent);
                return (left.mPointer != right.mPointer);
            }

            template<class T, class U, class Base>
            friend bool operator<=(PlainPointerIterator<T, Base> left,
                                   PlainPointerIterator<U, Base> right)
            noexcept(noexcept(Common::HalfSafe))
            {
                assert(left.mParent == right.mParent);
                return (left.mPointer <= right.mPointer);
            }

            template<class T, class U, class Base>
            friend bool operator>=(PlainPointerIterator<T, Base> left,
                                   PlainPointerIterator<U, Base> right)
            noexcept(noexcept(Common::HalfSafe))
            {
                assert(left.mParent == right.mParent);
                return (left.mPointer >= right.mPointer);
            }

            template<class T, class U, class Base>
            friend bool operator==(PlainPointerIterator<T, Base> left,
                                   PlainPointerIterator<U, Base> right)
            noexcept(noexcept(Common::HalfSafe))
            {
                assert(left.mParent == right.mParent);
                return (left.mPointer == right.mPointer);
            }

            template<class T, class U, class Base>
            friend bool operator<(PlainPointerIterator<T, Base> left,
                                  PlainPointerIterator<U, Base> right)
            noexcept(noexcept(Common::HalfSafe))
            {
                assert(left.mParent == right.mParent);
                return (left.mPointer < right.mPointer);
            }

            template<class T, class U, class Base>
            friend bool operator>(PlainPointerIterator<T, Base> left,
                                  PlainPointerIterator<U, Base> right)
            noexcept(noexcept(Common::HalfSafe))
            {
                assert(left.mParent == right.mParent);
                return (left.mPointer > right.mPointer);
            }

        private:
            Tp mPointer;
#ifndef NDEBUG
            Tc *mParent;
#endif
        };

    }
}
