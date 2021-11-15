#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "CCefApp.h"
#include <string>
#include <include/cef_sandbox_win.h>
//#include <iostream>
//#define CEF_ENABLE_SANDBOX
#ifdef CEF_ENABLE_SANDBOX
    #pragma comment(lib, "cef_sandbox.lib")
#endif

int _declspec(dllexport) InitCEF()
{
    // Get absolute CEFLauncher.exe path
    TCHAR buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring currentFileName(buffer);

    // Extract path and set DLL directory (absolute path is required here)
    size_t       pos = currentFileName.find_last_of(L'\\');
    std::wstring cefPath = currentFileName.substr(0, pos);            // Strip "CEFLauncher.exe"
    SetDllDirectory(cefPath.c_str());

    //std::cout << "SetDllDirectory=" << cefPath.c_str() << "\n";

    // Load CEF
    CefMainArgs        mainArgs(GetModuleHandle(NULL));
    CefRefPtr<CCefApp> app{new CCefApp};

    void* sandboxInfo = nullptr;
#ifdef CEF_ENABLE_SANDBOX
    CefScopedSandboxInfo scopedSandbox;
    sandboxInfo = scopedSandbox.sandbox_info();
#endif

    return CefExecuteProcess(mainArgs, app, sandboxInfo);
}
