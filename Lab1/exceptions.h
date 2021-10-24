#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include<string>

namespace TOOLS
{
    //Components of the UI
    enum class Component
    {
        Global,
        Login,
        JSONReader
    };
    template<typename T = const char*>
    class Exceptions
    {
        Component m_comp;
        const T& m_msg;
    public:
        Exceptions(const T& msg, const Component comp = Component::Global):
            m_comp(comp),
            m_msg(msg)
        {}
        const Component where() const
        {
            return m_comp;
        }
        const T& what() const noexcept
        {
            return m_msg;
        }
    };
}


#endif // EXCEPTIONS_H
