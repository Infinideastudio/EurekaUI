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
}
