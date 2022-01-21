
// ---------------------------------------------------------------------------
// kcpplib::scope_resource  == std::experimental::unique_resource
// kcpplib::scope_exit      == std::experimental::scope_exit
//
#pragma once
#include <type_traits>

namespace kcpplib {

template <typename T, typename TReleaseFunctor>
class scope_resource
{
public:
    using this_type = scope_resource<T, TReleaseFunctor>;
    using value_type = T;

    ~scope_resource() noexcept { TReleaseFunctor()(m_Resource); }

    scope_resource() = default;

    scope_resource(T Resource) : m_Resource(Resource) {}

    value_type get() const noexcept { return m_Resource; }

    void reset(value_type Resource = nullptr) noexcept
    {
        TReleaseFunctor()(m_Resource);
        m_Resource = Resource;
    }

    value_type release() noexcept
    {
        auto res = m_Resource;
        m_Resource = nullptr;
        return res;
    }

    void swap(this_type &Other) noexcept
    {
        auto other = Other.m_Resource;
        Other.m_Resource = m_Resource;
        m_Resource = other;
    }

    value_type operator*() const noexcept { return m_Resource; }

    value_type *operator&() noexcept { return &m_Resource; }

    this_type &operator=(T Resource)
    {
        reset(Resource);
        return *this;
    }

    operator value_type() { return get(); }

private:
    value_type m_Resource = nullptr;
};

template <typename T>
class scope_exit
{
public:
    scope_exit(T &&Callable) : m_Callable(std::move(Callable)) {}

    ~scope_exit()
    {
        if (m_Execute)
        {
            m_Callable();
        }
    }

    void release() { m_Execute = false; }

private:
    bool m_Execute = true;
    T m_Callable;
};

} // namespace std
