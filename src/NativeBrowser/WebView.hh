#pragma once

#include <gl/glew.h>
#include <gl/gl.h>
#include <napi.h>
#include <include/cef_app.h>
#include <include/cef_browser.h>
#include <include/cef_client.h>
#include <include/cef_render_handler.h>
#include <include/cef_life_span_handler.h>
#include <include/cef_context_menu_handler.h>
#include <include/cef_resource_request_handler.h>
#include "WebBrowserEventsInterface.hh"

class WebView : public CefClient,
                public CefRenderHandler,
                // private CefLoadHandler,
                // private CefRequestHandler,
                // private CefResourceRequestHandler,
                public CefLifeSpanHandler //,
                                          // private CefJSDialogHandler,
                                          // private CefDisplayHandler,
                                          //private CefContextMenuHandler
{
public:
  WebView(bool bTransparent);
  ~WebView(void);
  void Initialize(void);
  void SetWebBrowserEvents(WebBrowserEventsInterface* pInterface) { m_pEventsInterface = pInterface; };
  void CloseBrowser(void);
  bool LoadURL(const char *url);
  inline CefRefPtr<CefBrowser> GetCefBrowser(void) { return m_pWebView; }
  virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE { return this; };
  // virtual CefRefPtr<CefLoadHandler>        GetLoadHandler() override { return this; };
  // virtual CefRefPtr<CefRequestHandler>     GetRequestHandler() override { return this; };
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE { return this; };
  // virtual CefRefPtr<CefJSDialogHandler>    GetJSDialogHandler() override { return this; };
  // virtual CefRefPtr<CefDialogHandler>      GetDialogHandler() override { return this; };
  // virtual CefRefPtr<CefDisplayHandler>     GetDisplayHandler() override { return this; };
  // virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override { return this; };
  std::string GetUrl(void);

  // CefRenderHandler methods
  virtual void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) OVERRIDE;
  virtual void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show) OVERRIDE;
  virtual void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect &rect) OVERRIDE;
  virtual void OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType paintType, const CefRenderHandler::RectList &dirtyRects,
                       const void *buffer, int width, int height) OVERRIDE;

  // CefLifeSpawnHandler methods
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
  virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString &target_url, const CefString &target_frame_name,
                             CefLifeSpanHandler::WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures &popupFeatures,
                             CefWindowInfo &windowInfo, CefRefPtr<CefClient> &client, CefBrowserSettings &settings, CefRefPtr<CefDictionaryValue> &extra_info,
                             bool *no_javascript_access) OVERRIDE;
  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;


  void UpdateTexture();
  int GetTextureId();

  inline void Resize(int width, int height) { m_iWidth = width; m_iHeight = height; };



  struct
  {
      bool                    changed = false;
      std::mutex              dataMutex;
      std::mutex              cvMutex;
      std::condition_variable cv;

      const void*                buffer;
      int                        width, height;
      CefRenderHandler::RectList dirtyRects;

      CefRect                 popupRect;
      bool                    popupShown = false;
      std::unique_ptr<byte[]> popupBuffer;
  } m_RenderData;
private:
  WebBrowserEventsInterface* m_pEventsInterface;
  CefRefPtr<CefBrowser> m_pWebView;

  bool m_bBeingDestroyed = false;



  bool m_bIsTransparent;
  int m_iWidth = 1;
	int m_iHeight = 1;
	unsigned int tex_;

  GLuint prog = 0;
  GLint pos_loc = -1;
  GLint texcoord_loc = -1;
  GLint tex_loc = -1;
  GLint mvp_loc = -1;

  IMPLEMENT_REFCOUNTING(WebView);
};
