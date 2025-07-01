#pragma once
#pragma once
#ifndef DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

extern "C"
{
    /**
     * Opens a random message box.
     */
    void call_my_function();
}