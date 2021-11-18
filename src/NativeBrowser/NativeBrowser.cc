#include "NativeBrowser.hh"
// #include "common.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//#include "CCefApp.h"
#include <string>
#include <map>
#include <algorithm>
#include <cassert>
#include <include/cef_sandbox_win.h>

//#define CEF_ENABLE_SANDBOX
#ifdef CEF_ENABLE_SANDBOX
    #pragma comment(lib, "cef_sandbox.lib")
#endif

#include <include/cef_app.h>
#include "WebCore.hh"

Napi::FunctionReference NativeBrowser::constructor;

Napi::Object NativeBrowser::Init(Napi::Env env, Napi::Object exports)
{
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "NativeBrowser", {
    InstanceMethod("loadUrl", &NativeBrowser::LoadUrl),
    InstanceMethod("getUrl", &NativeBrowser::GetUrl),
    InstanceMethod("getTextureId", &NativeBrowser::GetTextureId),
    InstanceMethod("bindTexture", &NativeBrowser::BindTexture),
    InstanceMethod("update", &NativeBrowser::Update),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("NativeBrowser", func);

  return exports;
}



NativeBrowser::NativeBrowser(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<NativeBrowser>(info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  //auto self = reinterpret_cast<NativeBrowser *>(inner_obj_);

  //salve self instance to pass in callback in future
  // get object from option parammeter
  Napi::Object options = info[0].As<Napi::Object>();


  // get hwnd
  if(options.Has("hwnd"))
  {
    HWND hwnd = (HWND)options.Get("hwnd").As<Napi::Number>().Int64Value();
    WebCore::GetInstance()->SetWindowHandle(hwnd);
  }

  // get url
  std::string url = "";
  if (options.Has("url")) {
    url = options.Get("url").As<Napi::String>();
  }

  // get width
  int width = 800;
  if (options.Has("width")) {
    width = options.Get("width").As<Napi::Number>();
  }

  // get height
  int height = 600;
  if (options.Has("height")) {
    height = options.Get("height").As<Napi::Number>();
  }

  // get title
  std::string title = "";
  if (options.Has("title")) {
    title = options.Get("title").As<Napi::String>();
  }

  // get toolbar
  bool toolbar = false;
  if (options.Has("toolbar")) {
    toolbar = options.Get("toolbar").As<Napi::Boolean>();
  }

  // get resizable
  bool resizable = false;
  if (options.Has("resizable")) {
    resizable = options.Get("resizable").As<Napi::Boolean>();
  }

  // get fullscreen
  bool fullscreen = false;
  if (options.Has("fullscreen")) {
    fullscreen = options.Get("fullscreen").As<Napi::Boolean>();
  }

  // get minWidth
  int minWidth = 0;
  if (options.Has("minWidth")) {
    minWidth = options.Get("minWidth").As<Napi::Number>();
  }

  // get minHeight
  int minHeight = 0;
  if (options.Has("minHeight")) {
    minHeight = options.Get("minHeight").As<Napi::Number>();
  }

  // get maxWidth
  int maxWidth = 0;
  if (options.Has("maxWidth")) {
    maxWidth = options.Get("maxWidth").As<Napi::Number>();
  }

  // get maxHeight
  int maxHeight = 0;
  if (options.Has("maxHeight")) {
    maxHeight = options.Get("maxHeight").As<Napi::Number>();
  }

  // get transparent
  bool transparent = false;
  if (options.Has("transparent")) {
    transparent = options.Get("transparent").As<Napi::Boolean>();
  }

  // get frame
  bool frame = false;
  if (options.Has("frame")) {
    frame = options.Get("frame").As<Napi::Boolean>();
  }

  // get show
  bool show = true;
  if (options.Has("show")) {
    show = options.Get("show").As<Napi::Boolean>();
  }

  // get backgroundColor
  std::string backgroundColor = "";
  if (options.Has("backgroundColor")) {
    backgroundColor = options.Get("backgroundColor").As<Napi::String>();
  }

  m_pClientWebBrowser = new ClientWebBrowser();

  if (options.Has("onCreated")) {
    // save NativeBrowser api instance
    Napi::Function func = options.Get("onCreated").As<Napi::Function>();
    //if(func.IsFunction()) {
      m_pClientWebBrowser->m_onCreatedCallback = Napi::Persistent(func);
      m_pClientWebBrowser->m_onCreatedCallback.SuppressDestruct();
    //}
  }

  if (options.Has("onClose")) {
    Napi::Function func = options.Get("onClose").As<Napi::Function>();
    // if(func.IsFunction()) {
      m_pClientWebBrowser->m_onCloseCallback = Napi::Persistent(func);
      m_pClientWebBrowser->m_onCloseCallback.SuppressDestruct();
    // }
  }

  if (options.Has("onError")) {
    Napi::Function func = options.Get("onError").As<Napi::Function>();
    // if(func.IsFunction()) {
      m_pClientWebBrowser->m_onErrorCallback = Napi::Persistent(func);
      m_pClientWebBrowser->m_onErrorCallback.SuppressDestruct();
    // }
  }

  // m_pClientWebBrowser->GetWebView()->SetSize(width, height);
  // m_pClientWebBrowser->GetWebView()->SetTransparent(transparent);
  // m_pClientWebBrowser->GetWebView()->SetShow(show);
  // m_pClientWebBrowser->GetWebView()->SetBackgroundColor(backgroundColor);
  // m_pClientWebBrowser->GetWebView()->SetFrame(frame);
  // m_pClientWebBrowser->GetWebView()->SetResizable(resizable);
  // m_pClientWebBrowser->GetWebView()->SetFullscreen(fullscreen);
  // m_pClientWebBrowser->GetWebView()->SetMinSize(minWidth, minHeight);
  // m_pClientWebBrowser->GetWebView()->SetMaxSize(maxWidth, maxHeight);
  // m_pClientWebBrowser->GetWebView()->SetToolbar(toolbar);
  // m_pClientWebBrowser->GetWebView()->SetTitle(title);

}

Napi::Value NativeBrowser::LoadUrl(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  std::string url = info[0].As<Napi::String>();
  m_pClientWebBrowser->GetWebView()->LoadURL(url.c_str());
  return env.Undefined();
}

Napi::Value NativeBrowser::GetUrl(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  std::string url = m_pClientWebBrowser->GetUrl();
  return Napi::String::New(env, url);
}

Napi::Value NativeBrowser::GetTextureId(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  auto webView = m_pClientWebBrowser->GetWebView();

  int textureId = 0;

  if (webView) {
    textureId = webView->GetTextureId();
  }

  return Napi::Number::New(env, textureId);
}

Napi::Value NativeBrowser::BindTexture(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

Napi::Value NativeBrowser::Update(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}


Napi::Value init(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  std::string basePath = info[0].As<Napi::String>();
  WebCore::GetInstance()->Initialise(basePath);
  return env.Undefined();
}

Napi::Value NativeBrowserUpdate(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  WebCore::GetInstance()->Update();

  return env.Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("init", Napi::Function::New(env, init));
  exports.Set("NativeBrowserUpdate", Napi::Function::New(env, NativeBrowserUpdate));
  return NativeBrowser::Init(env, exports);
}

NODE_API_MODULE(init, Init)
