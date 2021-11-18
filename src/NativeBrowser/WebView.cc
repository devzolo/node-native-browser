#include "WebView.hh"

#include <include/cef_parser.h>
#include <include/cef_task.h>
#include "UTF8.hh"
#include "WebCore.hh"

WebView::WebView(bool bTransparent)
{
  m_bIsTransparent = bTransparent;
  Initialize();
}

WebView::~WebView()
{
  m_pWebView = nullptr;
}

void WebView::Initialize(void)
{
  // std::string vert =
  //   "attribute vec4 a_position;\n"
  //   "attribute vec2 a_texcoord;\n"
  //   "uniform mat4 u_mvp;\n"
  //   "varying vec2 v_texcoord;\n"
  //   "void main() {\n"
  //   "  v_texcoord = a_texcoord;\n"
  //   "  gl_Position = u_mvp * a_position;\n"
  //   "}\n";

  // std::string frag =
  //   "precision mediump float;\n"
  //   "varying vec2 v_texcoord;\n"
  //   "uniform sampler2D s_tex;\n"
  //   "void main() {\n"
  //   "  gl_FragColor = texture2D(s_tex, v_texcoord);\n"
  //   "}\n";

  // GLuint prog = GLCore::createShaderProgramFromCode(vert.c_str(), frag.c_str());

  // if(prog != 0) {
  //   MessageBox(NULL, L"shader compile failed", L"Error", MB_OK);
  //   return;
  // }

  // pos_loc = glGetAttribLocation(prog, "a_position");
	// texcoord_loc = glGetAttribLocation(prog, "a_texcoord");
	// tex_loc = glGetUniformLocation(prog, "s_tex");
	// mvp_loc = glGetUniformLocation(prog, "u_mvp");

  glGenTextures(1, &tex_);
	glBindTexture(GL_TEXTURE_2D, tex_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// dummy texture data - for debugging
	const unsigned char data[] = {
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255,
		255, 255, 255, 255,
	};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);

  //settings.log_severity = cef_log_severity_t::LOGSEVERITY_INFO;
  CefBrowserSettings browserSettings;
  browserSettings.windowless_frame_rate = 30;
  browserSettings.webgl = cef_state_t::STATE_ENABLED;
  browserSettings.plugins = cef_state_t::STATE_DISABLED;


  // Set background color to opaque white if transparency is disabled
  if (!m_bIsTransparent)
    browserSettings.background_color = 0xffffffff;

  CefWindowInfo windowInfo;

  HWND hWnd = GetConsoleWindow();//WebCore::GetInstance()->GetWindowHandle();

  windowInfo.SetAsWindowless(hWnd);

  CefBrowserHost::CreateBrowser(windowInfo, this, "", browserSettings, nullptr, nullptr);
}

std::string WebView::GetUrl(void)
{
  if (!m_pWebView)
    return "";

  return UTF16ToMbUTF8(m_pWebView->GetMainFrame()->GetURL());
}

void WebView::CloseBrowser(void)
{
  if (m_pWebView)
  {
    m_pWebView->GetHost()->CloseBrowser(true);
  }
}

bool WebView::LoadURL(const char *url)
{
  if (!m_pWebView)
  {
    return false;
  }

  if (!url)
  {
    return false;
  }

  CefURLParts urlParts;

  if (!CefParseURL(url, urlParts))
  {
    return false;
  }

  CefString cefUrl(url);

  auto pFrame = m_pWebView->GetMainFrame();

  pFrame->LoadURL(cefUrl);

  return true;
}


////////////////////////////////////////////////////////////////////
//                                                                //
// Implementation: CefRenderHandler::GetViewRect                  //
// http://magpcss.org/ceforum/apidocs3/projects/(default)/CefRenderHandler.html#GetViewRect(CefRefPtr%3CCefBrowser%3E,CefRect&) //
//                                                                //
////////////////////////////////////////////////////////////////////
void WebView::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    rect.x = 0;
    rect.y = 0;

    // if (m_bBeingDestroyed)
    // {
    //     rect.width = 1;
    //     rect.height = 1;
    //     return;
    // }

    // rect.width = static_cast<int>(m_pWebBrowserRenderItem->m_uiSizeX);
    // rect.height = static_cast<int>(m_pWebBrowserRenderItem->m_uiSizeY);


  rect.width = static_cast<int>(800);
  rect.height = static_cast<int>(600);
}

////////////////////////////////////////////////////////////////////
//                                                                //
// Implementation: CefRenderHandler::OnPopupShow                  //
// http://magpcss.org/ceforum/apidocs3/projects/(default)/CefRenderHandler.html#OnPopupShow(CefRefPtr<CefBrowser>,bool) //
//                                                                //
////////////////////////////////////////////////////////////////////
void WebView::OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)
{
    // std::lock_guard<std::mutex> lock{m_RenderData.dataMutex};
    // m_RenderData.popupShown = show;

    // // Free popup buffer memory if hidden
    // if (!show)
    //     m_RenderData.popupBuffer.reset();
}


////////////////////////////////////////////////////////////////////
//                                                                //
// Implementation: CefRenderHandler::OnPopupSize                  //
// http://magpcss.org/ceforum/apidocs3/projects/(default)/CefRenderHandler.html#OnPopupSize(CefRefPtr<CefBrowser>,constCefRect&) //
//                                                                //
////////////////////////////////////////////////////////////////////
void WebView::OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect)
{
    // std::lock_guard<std::mutex> lock{m_RenderData.dataMutex};

    // // Update rect
    // m_RenderData.popupRect = rect;

    // // Resize buffer
    // m_RenderData.popupBuffer.reset(new byte[rect.width * rect.height * 4]);
}

////////////////////////////////////////////////////////////////////
//                                                                //
// Implementation: CefRenderHandler::OnPaint                      //
// http://magpcss.org/ceforum/apidocs3/projects/(default)/CefRenderHandler.html#OnPaint(CefRefPtr%3CCefBrowser%3E,PaintElementType,constRectList&,constvoid*,int,int)
// //
//                                                                //
////////////////////////////////////////////////////////////////////
void WebView::OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType paintType, const CefRenderHandler::RectList& dirtyRects,
                       const void* buffer, int width, int height)
{
    if (m_bBeingDestroyed)
        return;

    {
        std::lock_guard<std::mutex> lock(m_RenderData.dataMutex);

        // Copy popup buffer
        if (paintType == PET_POPUP)
        {
            if (m_RenderData.popupBuffer)
            {
                memcpy(m_RenderData.popupBuffer.get(), buffer, width * height * 4);
            }

            return;            // We don't have to wait as we've copied the buffer already
        }

        // Store render data
        m_RenderData.buffer = buffer;
        m_RenderData.width = width;
        m_RenderData.height = height;
        m_RenderData.dirtyRects = dirtyRects;
        m_RenderData.changed = true;
    }

    // Wait for the main thread to handle drawing the texture
    std::unique_lock<std::mutex> lock(m_RenderData.cvMutex);
    m_RenderData.cv.wait(lock);
}


void WebView::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
  // // Remove events owned by this webview and invoke left callbacks
  WebCore::GetInstance()->RemoveWebViewEvents(this);

  m_pWebView = nullptr;

  MessageBox(NULL, L"TESTE", L"WebView::OnBeforeClose", MB_OK);

  // // Remove focused web view reference
  // if (g_pCore->GetWebCore()->GetFocusedWebView() == this)
  //     g_pCore->GetWebCore()->SetFocusedWebView(nullptr);
}

bool WebView::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString &target_url, const CefString &target_frame_name,
                            CefLifeSpanHandler::WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures &popupFeatures,
                            CefWindowInfo &windowInfo, CefRefPtr<CefClient> &client, CefBrowserSettings &settings, CefRefPtr<CefDictionaryValue> &extra_info,
                            bool *no_javascript_access)
{
  // // ATTENTION: This method is called on the IO thread

  // // Trigger the popup/new tab event
  // SString strTagetURL = UTF16ToMbUTF8(target_url);
  // SString strOpenerURL = UTF16ToMbUTF8(frame->GetURL());

  // // Queue event to run on the main thread
  // auto func = std::bind(&CWebBrowserEventsInterface::Events_OnPopup, m_pEventsInterface, strTagetURL, strOpenerURL);
  // g_pCore->GetWebCore()->AddEventToEventQueue(func, this, "OnBeforePopup");

  // Block popups generally
  return true;
}

void WebView::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
  // // Set web view reference
  m_pWebView = browser;
  // //put compile date in message
  // std::stringstream ss;
  // ss << "Compiled on " << __DATE__ << " at " << __TIME__;
  // std::string s = ss.str();

  // // Call created event callback
  auto func = std::bind(&WebBrowserEventsInterface::Events_OnCreated, m_pEventsInterface);
  WebCore::GetInstance()->AddEventToEventQueue(func, this, "OnAfterCreated");
}

void WebView::UpdateTexture() {
  std::lock_guard<std::mutex> lock(m_RenderData.dataMutex);

  // Update view area
  if (m_RenderData.changed)
  {
    // Update changed state
    m_RenderData.changed = false;

    auto sourceData = static_cast<const byte*>(m_RenderData.buffer);

    glBindTexture(GL_TEXTURE_2D, tex_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, sourceData);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
  // Resume CEF render thread
  m_RenderData.cv.notify_all();
}


  // //call javascript callback in main thread
  // Napi::Env env = g_pCore->GetNapiEnv();
  // Napi::HandleScope scope(env);
  // Napi::Function cb = Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
  //   Napi::Env env = info.Env();
  //   Napi::HandleScope scope(env);
  //   Napi::Object obj = info[0].As<Napi::Object>();
  //   Napi::Value cb = obj.Get("callback");
  //   Napi::Function cbFunc = cb.As<Napi::Function>();
  //   cbFunc.Call(env.Global(), {Napi::String::New(env, "Hello from C++")});
  // });

  // Napi::Object obj = Napi::Object::New(env);
  // obj.Set("callback", cb);

  // Napi::Function func = Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
  //   Napi::Env env = info.Env();
  //   Napi::HandleScope scope(env);
  //   Napi::Object obj = info[0].As<Napi::Object>();
  //   Napi::Value cb = obj.Get("callback");
  //   Napi::Function cbFunc = cb.As<Napi::Function>();
  //   cbFunc.Call(env.Global(), {Napi::String::New(env, "Hello from C++")});
  // });


int WebView::GetTextureId() {
  return tex_;
}
