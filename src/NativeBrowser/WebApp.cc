#include "common.hh"
#include "WebApp.hh"

#include <include/wrapper/cef_stream_resource_handler.h>
#include <include/cef_parser.h>

CefRefPtr<CefResourceHandler> WebApp::HandleError(const std::string& strError, unsigned int uiError)
{
    auto stream = CefStreamReader::CreateForData((void*)strError.c_str(), strError.length());
    return new CefStreamResourceHandler(uiError, strError, "text/plain", CefResponse::HeaderMap(), stream);
}

void WebApp::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar)
{

}

void WebApp::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
{

}

CefRefPtr<CefResourceHandler> WebApp::Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name,
                                              CefRefPtr<CefRequest> request)
{

    return nullptr;
}
