#pragma once

#include "common.hh"
#include "WebBrowserEventsInterface.hh"


class NativeBrowser;

class ClientWebBrowser : public WebBrowserEventsInterface
{
public:
  ClientWebBrowser(void);
  ~ClientWebBrowser();

  std::string GetUrl(void);

  void Unlink();
  void Events_OnCreated() OVERRIDE;
  inline WebView* GetWebView() { return m_pWebView; }

  Napi::FunctionReference m_onCreatedCallback;
  Napi::FunctionReference m_onCloseCallback;
  Napi::FunctionReference m_onErrorCallback;
private:
    WebView*                 m_pWebView;
    // std::map<std::string, ajax_callback_t> m_mapAjaxCallback;
};
