#include "eurekaui/context.h"
#include <stack>
#include <codecvt>
#include <stdexcept>
#include "utils/jsonhelper.h"
namespace EurekaUI
{
    struct Context::LocaleImpl
    {
        // Locale
        Json mLangBase;
        std::stack<Json*> mLangStack;
        std::string mActiveLang, mBasePath;
        std::wstring_convert<std::codecvt_utf8<wchar_t>> mConv;
    };

    Context::Context()
            : mRoot(nullptr)
    {
    }

    Context::~Context() = default;

    std::string Context::w2cUtf8(const std::wstring& src)
    {
        return mLocaleImpl->mConv.to_bytes(src);
    }

    std::wstring Context::c2wUtf8(const std::string& src)
    {
        return mLocaleImpl->mConv.from_bytes(src);
    }

    std::string Context::getActiveLang() const
    {
        return mLocaleImpl->mActiveLang;
    }

    std::string Context::getLocaleResourcePath() const
    {
        return mLocaleImpl->mBasePath;
    }

    void Context::setActiveLang(const std::string& name)
    {
        mLocaleImpl->mActiveLang = name;
        mLocaleImpl->mLangBase = readJsonFromFile(mLocaleImpl->mBasePath + '/' + name + ".json");
        mLocaleImpl->mLangStack.swap(std::stack<Json*>());
        mLocaleImpl->mLangStack.push(&mLocaleImpl->mLangBase);
    }

    void Context::setLocaleResourcePath(const std::string& path)
    {
        mLocaleImpl->mBasePath = path;
        setActiveLang(getActiveLang());
    }

    void Context::popLocaleNamespace()
    {
        if (mLocaleImpl->mLangStack.size() > 0)
            mLocaleImpl->mLangStack.pop();
    }

    void Context::pushLocaleNamespace(const std::string& ns)
    {
        auto find = mLocaleImpl->mLangStack.top()->find(ns);
        if (!(find != mLocaleImpl->mLangStack.top()->end()) || find->is_object())
            mLocaleImpl->mLangStack.push(&(*find));
        else
            throw std::runtime_error("namespace not found!");
    }

    std::string Context::getLocaleStr(const std::string& key)
    {
        mLocaleImpl->mLangStack.top()->find(key);
    }

}

