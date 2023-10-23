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
  command_line->AppendSwitch("disable-gpu-compositing");
  command_line->AppendSwitch("disable-gpu");
  command_line->AppendSwitch("enable-begin-frame-scheduling");
  if (process_type.empty()) {
    // command_line->AppendSwitchWithValue("media_use_ffmpeg", "true");
    // command_line->AppendSwitchWithValue("media_use_libvpx", "true");
    // command_line->AppendSwitchWithValue("proprietary_codecs", "true");
    // command_line->AppendSwitchWithValue("ffmpeg_branding", "Chrome");
    command_line->AppendSwitchWithValue("autoplay-policy", "no-user-gesture-required");
    command_line->AppendSwitchWithValue("enable-blink-features", "ShadowDOMV0,CustomElementsV0,HTMLImports");
  }
}

CefRefPtr<CefResourceHandler> WebApp::Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name,
                                              CefRefPtr<CefRequest> request)
{
  if (!browser || !frame)
    return nullptr;
  return nullptr;
}
