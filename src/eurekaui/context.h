#pragma once
#include <vector>
#include <memory>
#include "element.h"
namespace EurekaUI
{
    /** EurekaUI context
     *
     */
    class Context
    {
    public:
        explicit Context();
        ~Context();
        // Non Copyable
        Context(const Context&) = delete;
        Context& operator = (const Context&) = delete;
        // Element Master Control
        Element* root() { return &mRoot; }

        // Locale Functions
        std::string w2cUtf8(const std::wstring& src);
        std::wstring c2wUtf8(const std::string& src);
        std::string getActiveLang() const;
        std::string getLocaleResourcePath() const;
        void setActiveLang(const std::string& name);
        void setLocaleResourcePath(const std::string& path);
        void popLocaleNamespace();
        void pushLocaleNamespace(const std::string& ns);
        std::string getLocaleStr(const std::string& key);
    private:
        Element mRoot;
        struct LocaleImpl;
        std::unique_ptr<LocaleImpl> mLocaleImpl;
    };
}
