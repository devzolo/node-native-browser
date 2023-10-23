#pragma once

#include "common.hh"

class WebDevTools
{
public:
  static bool Show(WebView* view);
  static bool Close(WebView* view);
};


class WebDevToolsClient : public CefClient
{
public:
  WebDevToolsClient() = default;

  IMPLEMENT_REFCOUNTING(WebDevToolsClient);
};
