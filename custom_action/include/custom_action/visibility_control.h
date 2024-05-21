#ifndef CUSTOM_ACTION_VISIBILITY_CONTROL_H
#define CUSTOM_ACTION_VISIBILITY_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    // https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
    #ifdef __GNUC__
        #define CUSTOM_ACTION_CPP_EXPORT __attribute__((dllexport))
        #define CUSTOM_ACTION_CPP_IMPORT __attribute__((dllimport))
    #else // __GNUC__
        #define CUSTOM_ACTION_CPP_EXPORT __declspec(dllexport)
        #define CUSTOM_ACTION_CPP_IMPORT __declspec(dllimport)
    #endif // __GNUC__
    #ifdef CUSTOM_ACTION_CPP_BUILDING_DLL
        #define CUSTOM_ACTION_CPP_PUBLIC CUSTOM_ACTION_CPP_EXPORT
    #else // CUSTOM_ACTION_CPP_BUILDING_DLL
        #define CUSTOM_ACTION_CPP_PUBLIC CUSTOM_ACTION_CPP_IMPORT
    #endif // CUSTOM_ACTION_CPP_BUILDING_DLL
    #define CUSTOM_ACTION_CPP_PUBLIC_TYPE CUSTOM_ACTION_CPP_PUBLIC
    #define CUSTOM_ACTION_CPP_LOCAL
#else // defined _WIN32 || defined __CYGWIN__
    #define CUSTOM_ACTION_CPP_EXPORT __attribute__((visibility("default")))
    #define CUSTOM_ACTION_CPP_IMPORT
    #if __GNUC__ >= 4
        #define CUSTOM_ACTION_CPP_PUBLIC __attribute__((visibility("default")))
        #define CUSTOM_ACTION_CPP_LOCAL __attribute__((visibility("hidden")))
    #else // __GNUC__ >= 4
        #define CUSTOM_ACTION_CPP_PUBLIC
        #define CUSTOM_ACTION_CPP_LOCAL
    #endif // __GNUC__ >= 4
    #define CUSTOM_ACTION_CPP_PUBLIC_TYPE
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CUSTOM_ACTION_VISIBILITY_CONTROL_H
