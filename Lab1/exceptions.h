#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include<string>

namespace TOOLS {
    enum class Component
    {
        Global,
        Login,
        JSONReader
    };
    template<typename T = const char*>
    class Exceptions;
}

#define THROW_ERROR_IF(cond, type, what) \
    if(cond){                                  \
         THROW_ERROR(type, what)         \
    }

#define THROW_ERROR(type, what) throw TOOLS::Exceptions<type>(what);


namespace TOOLS
{
    //Components of the UI
    template<typename T>
    class Exceptions
    {
        const T& m_msg;
    public:
        Exceptions(const T& msg);
        const T& what() const noexcept;
    };

    template<typename T>
    Exceptions<T>::Exceptions(const T& msg):
        m_msg(msg)
    {}

    template<typename T>
    const T& Exceptions<T>::what() const noexcept
    {
        return m_msg;
    }
}


#endif // EXCEPTIONS_H
