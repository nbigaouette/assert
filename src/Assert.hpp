#ifndef INC_ASSERT_hpp
#define INC_ASSERT_hpp

#include <cstdlib>
#include <cmath>
#include <limits>  // http://www.cplusplus.com/reference/std/limits/numeric_limits/

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
#define assert_always(x)                                \
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

#ifdef __INTEL_COMPILER
#define Assert_isinf_isnan(value)                                   \
{                                                                   \
    /* Disable warning #1572: "floating-point equality and          \
       inequality comparisons are unreliable" */                    \
    __pragma(warning(disable:1572))                                 \
    if ((value) != (value))                                         \
    {                                                               \
        std_cout                                                    \
            << "ERROR: The variable " << QUOTEME(value) << " is NaN!!! (" << (value) << ")\n" \
            << "In file \"" << __FILE__ << "\", "                   \
            << "line " << __LINE__ << "\n"                          \
            << "Aborting\n"                                         \
            << std::flush;                                          \
        std_cout.Flush();                                           \
        abort();                                                    \
    }                                                               \
    assert((value) == (value));                                     \
    /* FIXME: Add a isinf() equivalent */                           \
}
#else // #ifdef __INTEL_COMPILER
#ifdef __SUNPRO_CC
#define Assert_isinf_isnan(value)                                   \
{                                                                   \
    if ((value) != (value))                                         \
    {                                                               \
        std_cout                                                    \
            << "ERROR: The variable " << QUOTEME(value) << " is NaN!!! (" << (value) << ")\n" \
            << "In file \"" << __FILE__ << "\", "                   \
            << "line " << __LINE__ << "\n"                          \
            << "Aborting\n"                                         \
            << std::flush;                                          \
        std_cout.Flush();                                           \
        abort();                                                    \
    }                                                               \
    assert((value) == (value));                                     \
    /* FIXME: Add a isinf() equivalent */                           \
}
#else // #ifdef __SUNPRO_CC
#define Assert_isinf_isnan(value)                                   \
{                                                                   \
    if (std::isinf((value)))                                        \
    {                                                               \
        std_cout                                                    \
            << "ERROR: The variable " << QUOTEME(value) << " is infinite!!! (" << (value) << ")\n" \
            << "In file \"" << __FILE__ << "\", "                   \
            << "line " << __LINE__ << "\n"                          \
            << "Aborting\n"                                         \
            << std::flush;                                          \
        std_cout.Flush();                                           \
        abort();                                                    \
    }                                                               \
    assert(!std::isinf((value)));                                   \
                                                                    \
    if (std::isnan((value)))                                        \
    {                                                               \
        std_cout                                                    \
            << "ERROR: The variable " << QUOTEME(value) << " is NaN!!! (" << (value) << ")\n" \
            << "In file \"" << __FILE__ << "\", "                   \
            << "line " << __LINE__ << "\n"                          \
            << "Aborting\n"                                         \
            << std::flush;                                          \
        std_cout.Flush();                                           \
        abort();                                                    \
    }                                                               \
    assert(!std::isnan((value)));                                   \
}
#endif // #ifdef __SUNPRO_CC
#endif // #ifdef __INTEL_COMPILER

#endif // INC_ASSERT_hpp

// ********** End of file ***************************************
