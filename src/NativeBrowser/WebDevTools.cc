#include "WebDevTools.hh"

bool WebDevTools::Show(WebView *pWebView)
{
  auto pBrowser = pWebView->GetCefBrowser();
  if (!pBrowser)
    return false;

  CefBrowserSettings settings;
  CefWindowInfo windowInfo;
  windowInfo.SetAsPopup(NULL, "NativeBrowser DevTools");

  CefRefPtr<CefClient> pClient{new WebDevToolsClient};
  return false;
}

bool WebDevTools::Close(WebView *pWebView)
{
  auto pBrowser = pWebView->GetCefBrowser();
  if (!pBrowser)
    return false;

  pBrowser->GetHost()->CloseDevTools();
  return true;
}
