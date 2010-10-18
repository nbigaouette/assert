#ifndef INC_ASSERT_hpp
#define INC_ASSERT_hpp

#include <cstdlib>

#include <StdCout.hpp>

#define DEBUGP(x)  std_cout << __FILE__ << ":" << __LINE__ << ":\n    " << x;
// Quote something, usefull to quote a macro's value
#define _QUOTEME(x) #x
#define QUOTEME(x) _QUOTEME(x)

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
template <class T>
inline void Assert_isinf_isnan(T value)
{
#ifndef __SUNPRO_CC
//     if (isinf(value))
//     {
//         std_cout << "value is inf!!! value = " << value << "\n";
//         std_cout << "Aborting\n";
//     }
    assert(!isinf(value));
#endif // #ifndef __SUNPRO_CC
//     if (isnan(value))
//     {
//         std_cout << "value is NaN!!! value = " << value << "\n";
//         std_cout << "Aborting\n";
//     }
    assert(!isnan(value));
}

#endif // INC_ASSERT_hpp

// ********** End of file ***************************************
