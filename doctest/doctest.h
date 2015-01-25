#pragma once

// internal macros for string concatenation and anonymous variable name generation
#define DOCTEST_STR_CONCAT_IMPL(s1, s2) s1##s2
#define DOCTEST_STR_CONCAT(s1, s2) DOCTEST_STR_CONCAT_IMPL(s1, s2)
#ifdef __COUNTER__ // not standard and may be missing for some compilers
#define DOCTEST_ANONYMOUS(x) DOCTEST_STR_CONCAT(x, __COUNTER__)
#else // __COUNTER__
#define DOCTEST_ANONYMOUS(x) DOCTEST_STR_CONCAT(x, __LINE__)
#endif // __COUNTER__

// internal macro for making a string
#define DOCTEST_TOSTR_IMPL(x) #x
#define DOCTEST_TOSTR(x) DOCTEST_TOSTR_IMPL(x)

// internal macro for concatenating 2 literals and making the result a string
#define DOCTEST_STR_CONCAT_TOSTR(s1, s2) DOCTEST_TOSTR(DOCTEST_STR_CONCAT(s1, s2))

namespace doctest
{
// a dummy function that can be used for initializing globals (for silencing warnings)
inline int dummy()
{
    return 0;
}
} // namespace doctest_generated

// if registering is not disabled
#if !defined(DOCTEST_GLOBAL_DISABLE)

// if the user wants to include this header himself somewhere and not
// everywhere doctest.h is included (no unnecessary header inclusion)
#if !defined(DOCTEST_DONT_INCLUDE_IMPLEMENTATION)
#include "doctest_impl.h"
#else  // DOCTEST_DONT_INCLUDE_IMPLEMENTATION
namespace doctest
{
namespace detail
{
    // forward declarations of the function used by the registering macros
    int regTest(void (*f)(void), unsigned line, const char* file, const char* name);
    int setTestSuiteName(const char* name);
} // namespace detail
// forward declarations of the functions intended for direct use
void* createParams(int argc, char** argv);
void addFilter(void* params_struct, const char* filter, const char* value);
void setOption(void* params_struct, const char* option, int value);
void freeParams(void* params_struct);
void setTestExecutionWrapper(void* params_struct, int (*f)(void (*)(void)));
int runTests(void* params_struct);
} // namespace doctest
#endif // DOCTEST_DONT_INCLUDE_IMPLEMENTATION

// internal registering macros
#define DOCTEST_REGISTER_FUNCTION(f, name)                                                         \
    static int DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_VAR_) =                                           \
        doctest::detail::regTest(f, __LINE__, __FILE__, #name);

#define DOCTEST_IMPLEMENT_FIXTURE(der, base, func, name)                                           \
    namespace                                                                                      \
    {                                                                                              \
        struct der : base {                                                                        \
            void f();                                                                              \
        };                                                                                         \
        static void func()                                                                         \
        {                                                                                          \
            der v;                                                                                 \
            v.f();                                                                                 \
        }                                                                                          \
        DOCTEST_REGISTER_FUNCTION(func, name)                                                      \
    }                                                                                              \
    inline void der::f()

#define DOCTEST_CREATE_AND_REGISTER_FUNCTION(f, name)                                              \
    static void f();                                                                               \
    DOCTEST_REGISTER_FUNCTION(f, name)                                                             \
    inline void f()

// for registering doctests
#define doctest_test(name)                                                                         \
    DOCTEST_CREATE_AND_REGISTER_FUNCTION(DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_FUNC_), name)
#define doctest_test_noname                                                                        \
    DOCTEST_CREATE_AND_REGISTER_FUNCTION(DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_FUNC_), noname)

// for registering doctests with a fixture
#define doctest_fixture(c, name)                                                                   \
    DOCTEST_IMPLEMENT_FIXTURE(DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_CLASS_), c,                        \
                              DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_FUNC_), name)
#define doctest_fixture_noname(c)                                                                  \
    DOCTEST_IMPLEMENT_FIXTURE(DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_CLASS_), c,                        \
                              DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_FUNC_), noname)

// for starting a testsuite block
#define doctest_testsuite(name)                                                                    \
    static int DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_VAR_) = doctest::detail::setTestSuiteName(#name); \
    static int DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_GIVE_ME_COMMA_) = doctest::dummy()

// for ending a testsuite block
#define doctest_testsuite_end                                                                      \
    static int DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_VAR_) = doctest::detail::setTestSuiteName("");    \
    static int DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_GIVE_ME_COMMA_) = doctest::dummy()

// =============================================================================
// == WHAT FOLLOWS IS VERSIONS OF THE MACROS THAT DO NOT DO ANY REGISTERING!  ==
// == THIS CAN BE ENABLED BY DEFINING DOCTEST_GLOBAL_DISABLE GLOBALLY!        ==
// =============================================================================
#else // DOCTEST_GLOBAL_DISABLE

// clang-format off
namespace doctest
{
inline void* createParams(int, char**) { return 0; }
inline void addFilter(void*, const char*, const char*) {}
inline void setOption(void*, const char*, int) {}
inline void freeParams(void*) {}
inline void setTestExecutionWrapper(void*, int (*)(void (*)(void))) {}
inline int runTests(void*) { return 0; }
} // namespace doctest
// clang-format on

#define DOCTEST_IMPLEMENT_FIXTURE(der, base, func, name)                                           \
    namespace                                                                                      \
    {                                                                                              \
        struct der : base {                                                                        \
            void f();                                                                              \
        };                                                                                         \
        static void func()                                                                         \
        {                                                                                          \
            der v;                                                                                 \
            v.f();                                                                                 \
        }                                                                                          \
    }                                                                                              \
    inline void der::f()

#define DOCTEST_CREATE_AND_REGISTER_FUNCTION(f, name) static inline void f()

// for registering doctests
#define doctest_test(name)                                                                         \
    DOCTEST_CREATE_AND_REGISTER_FUNCTION(DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_FUNC_), name)
#define doctest_test_noname                                                                        \
    DOCTEST_CREATE_AND_REGISTER_FUNCTION(DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_FUNC_), noname)

// for registering doctests with a fixture
#define doctest_fixture(x, name)                                                                   \
    DOCTEST_IMPLEMENT_FIXTURE(DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_CLASS_), x,                        \
                              DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_FUNC_), name)
#define doctest_fixture_noname(x)                                                                  \
    DOCTEST_IMPLEMENT_FIXTURE(DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_CLASS_), x,                        \
                              DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_FUNC_), noname)

// for starting a testsuite block
#define doctest_testsuite(name)                                                                    \
    static int DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_GIVE_ME_COMMA_) = doctest::dummy()

// for ending a testsuite block
#define doctest_testsuite_end                                                                      \
    static int DOCTEST_ANONYMOUS(DOCTEST_AUTOGEN_GIVE_ME_COMMA_) = doctest::dummy()

#endif // DOCTEST_GLOBAL_DISABLE

// == THIS SUPPLIES A MAIN FUNCTION AND SHOULD BE DONE ONLY IN ONE TRANSLATION UNIT
#ifdef DOCTEST_CONFIG_MAIN
// Standard C/C++ main entry point
int main(int argc, char** argv)
{
    void* params = doctest::createParams(argc, argv);
    int res = doctest::runTests(params);
    doctest::freeParams(params);
    return res;
}
#endif

// == SHORT VERSIONS OF THE TEST/FIXTURE/TESTSUITE MACROS
#ifdef DOCTEST_SHORT_MACRO_NAMES

#define test(name) doctest_test(name)
#define test_noname doctest_test_noname
#define fixture(c, name) doctest_fixture(c, name)
#define fixture_noname(c) doctest_fixture_noname(c)
// static method missing - TODO!
#define testsuite(name) doctest_testsuite(name)
#define testsuite_end doctest_testsuite_end

#endif // DOCTEST_SHORT_MACRO_NAMES