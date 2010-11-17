#ifndef INC_ASSERT_hpp
#define INC_ASSERT_hpp

#include <cstdlib>
#include <cmath>

#include <StdCout.hpp>

#ifndef DEBUGP
#define DEBUGP(x)  std_cout << __FILE__ << ":" << __LINE__ << ":\n    " << x;
#endif // #ifndef DEBUGP

// Quote something, usefull to quote a macro's value
#ifndef _QUOTEME
#define _QUOTEME(x) #x
#endif // #ifndef _QUOTEME
#ifndef QUOTEME
#define QUOTEME(x) _QUOTEME(x)
#endif // #ifndef QUOTEME

// **************************************************************
// http://stackoverflow.com/questions/389180/assert-and-ndebug
// #ifdef YDEBUG

// Undefine assert() to use our own
#ifdef assert
#undef assert
#endif

#define assert(x)                                       \
    if (!(x)) {                                         \
        std_cout                                        \
            << "##########################"             \
            << "##########################"             \
            << "##########################\n"           \
            << "Assertion failed in \"" << __FILE__     \
            << "\", line " << __LINE__ << ": "          \
            << "!(" << QUOTEME(x) << ")\n"              \
            << "##########################"             \
            << "##########################"             \
            << "##########################\n";          \
        std_cout.Flush();                               \
        abort();                                        \
    }
//     else   // This 'else' exists to catch the user's following semicolon
// #endif // #ifdef YDEBUG

// **************************************************************
/*
template <class T>
inline void Assert_isinf_isnan(T value)
{
    if (isinf(value))
    {
        std_cout << "value is inf!!! value = " << value << "\n";
        std_cout << "Aborting\n";
    }
    assert(!std::isinf(value));

    if (isnan(value))
    {
        std_cout << "value is NaN!!! value = " << value << "\n";
        std_cout << "Aborting\n";
    }
    assert(!std::isnan(value));
}
*/
#define Assert_isinf_isnan(value)                                   \
{                                                                   \
    if (std::isinf((value)))                                        \
    {                                                               \
        std_cout << "value is inf!!! value = " << (value) << "\n";  \
        std_cout << "Aborting\n";                                   \
    }                                                               \
    assert(!std::isinf((value)));                                   \
                                                                    \
    if (std::isnan((value)))                                        \
    {                                                               \
        std_cout << "value is NaN!!! value = " << (value) << "\n";  \
        std_cout << "Aborting\n";                                   \
    }                                                               \
    assert(!std::isnan((value)));                                   \
}

#endif // INC_ASSERT_hpp

// ********** End of file ***************************************
