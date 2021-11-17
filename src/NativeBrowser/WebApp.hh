#pragma once
#include <include/cef_app.h>
#include <include/cef_scheme.h>

class WebApp : public CefApp, public CefSchemeHandlerFactory
{
public:
    // Error Handler
    static CefRefPtr<CefResourceHandler> HandleError(const std::string& strError, unsigned int uiError);

    virtual void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) OVERRIDE;
    virtual void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) OVERRIDE;

    // CefSchemeHandlerFactory methods
    virtual CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name,
                                                 CefRefPtr<CefRequest> request) OVERRIDE;

    IMPLEMENT_REFCOUNTING(WebApp);
};
