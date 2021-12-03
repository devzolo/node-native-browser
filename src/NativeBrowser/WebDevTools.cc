#include "WebDevTools.hh"

bool WebDevTools::Show(WebView *pWebView)
{
  auto pBrowser = pWebView->GetCefBrowser();
  if (!pBrowser)
    return false;

  CefBrowserSettings settings;
  CefWindowInfo windowInfo;
  windowInfo.SetAsPopup(NULL, "NativeBrowser DevTools");

  // Create independent CefClient (to bypass access restrictions)
  CefRefPtr<CefClient> client{new WebDevToolsClient};

  pBrowser->GetHost()->ShowDevTools(windowInfo, client, settings, CefPoint());
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
