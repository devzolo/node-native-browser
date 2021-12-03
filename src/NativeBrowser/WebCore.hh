#pragma once

#include "common.hh"

enum eWebBrowserMouseButton
{
    BROWSER_MOUSEBUTTON_LEFT = 0,
    BROWSER_MOUSEBUTTON_MIDDLE = 1,
    BROWSER_MOUSEBUTTON_RIGHT = 2
};

class WebCore
{
public:
    struct EventEntry
    {
        std::function<void()> callback;
        WebView*              pWebView;
        EventEntry(const std::function<void()>& callback_, WebView* pWebView_) : callback(callback_), pWebView(pWebView_) {}
    };

  //GetInstance
  static WebCore* GetInstance() {
    static WebCore instance;
    return &instance;
  }
public:
  WebCore(void);
  ~WebCore(void);
  bool Initialise(std::string basePath);
  void Update();
  inline HWND GetWindowHandle() { return m_hWnd; }
  inline void SetWindowHandle(HWND hWnd) { m_hWnd = hWnd; }
  WebView* CreateWebView(unsigned int uiWidth, unsigned int uiHeight, bool bTransparent);
  void AddEventToEventQueue(std::function<void()> event, WebView* pWebView, const std::string& name);
  void RemoveWebViewEvents(WebView* pWebView);
  void DoEventQueuePulse();
  std::list<CefRefPtr<WebView>> m_WebViews;
  std::list<EventEntry>         m_EventQueue;
  std::mutex                    m_EventQueueMutex;
private:
  HWND m_hWnd;

};
