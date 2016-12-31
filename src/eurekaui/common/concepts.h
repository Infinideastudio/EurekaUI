#pragma once

namespace EurekaUI
{
    class Noncopyable
    {
    protected:
        constexpr Noncopyable() = default;
        ~Noncopyable() = default;
        Noncopyable(const Noncopyable&) = delete;
        Noncopyable& operator=(const Noncopyable&) = delete;
    };

    class Nonmoveable
    {
    protected:
        constexpr Nonmoveable() = default;
        ~Nonmoveable() = default;
        Nonmoveable(Noncopyable&&) = delete;
        Nonmoveable& operator=(Noncopyable&&) = delete;
    };
}
