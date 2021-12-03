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

  Napi::Function func = DefineClass(
      env,
      "NativeBrowser",
      {
          InstanceMethod("getTextureId", &NativeBrowser::GetTextureId),
          InstanceMethod("update", &NativeBrowser::Update),
          InstanceMethod("canNavigateBack", &NativeBrowser::CanNavigateBack),
          InstanceMethod("canNavigateForward", &NativeBrowser::CanNavigateForward),
          InstanceMethod("executeJavascript", &NativeBrowser::ExecuteJavascript),
          InstanceMethod("focus", &NativeBrowser::Focus),
          InstanceMethod("getProperty", &NativeBrowser::GetProperty),
          InstanceMethod("getSettings", &NativeBrowser::GetSettings),
          InstanceMethod("getSource", &NativeBrowser::GetSource),
          InstanceMethod("getTitle", &NativeBrowser::GetTitle),
          InstanceMethod("getURL", &NativeBrowser::GetURL),
          InstanceMethod("injectMouseDown", &NativeBrowser::InjectMouseDown),
          InstanceMethod("injectMouseUp", &NativeBrowser::InjectMouseUp),
          InstanceMethod("injectMouseMove", &NativeBrowser::InjectMouseMove),
          InstanceMethod("injectMouseWheel", &NativeBrowser::InjectMouseWheel),
          InstanceMethod("injectKeyboardEvent", &NativeBrowser::InjectKeyboardEvent),
          InstanceMethod("isFocused", &NativeBrowser::IsFocused),
          InstanceMethod("isLoading", &NativeBrowser::IsLoading),
          InstanceMethod("isRenderingPaused", &NativeBrowser::IsRenderingPaused),
          InstanceMethod("loadURL", &NativeBrowser::LoadURL),
          InstanceMethod("navigateBack", &NativeBrowser::NavigateBack),
          InstanceMethod("navigateForward", &NativeBrowser::NavigateForward),
          InstanceMethod("reloadPage", &NativeBrowser::ReloadPage),
          InstanceMethod("resize", &NativeBrowser::Resize),
          InstanceMethod("setAjaxHandler", &NativeBrowser::SetAjaxHandler),
          InstanceMethod("setProperty", &NativeBrowser::SetProperty),
          InstanceMethod("setRenderingPaused", &NativeBrowser::SetRenderingPaused),
          InstanceMethod("setVolume", &NativeBrowser::SetVolume),
          InstanceMethod("toggleDevTools", &NativeBrowser::ToggleDevTools),
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
  if (options.Has("hwnd"))
  {
    HWND hwnd = (HWND)options.Get("hwnd").As<Napi::Number>().Int64Value();
    WebCore::GetInstance()->SetWindowHandle(hwnd);
  }

  // get url
  std::string url = "";
  if (options.Has("url"))
  {
    url = options.Get("url").As<Napi::String>();
  }

  // get width
  int width = 800;
  if (options.Has("width"))
  {
    width = options.Get("width").As<Napi::Number>();
  }

  // get height
  int height = 600;
  if (options.Has("height"))
  {
    height = options.Get("height").As<Napi::Number>();
  }

  // get title
  std::string title = "";
  if (options.Has("title"))
  {
    title = options.Get("title").As<Napi::String>();
  }

  // get toolbar
  bool toolbar = false;
  if (options.Has("toolbar"))
  {
    toolbar = options.Get("toolbar").As<Napi::Boolean>();
  }

  // get resizable
  bool resizable = false;
  if (options.Has("resizable"))
  {
    resizable = options.Get("resizable").As<Napi::Boolean>();
  }

  // get fullscreen
  bool fullscreen = false;
  if (options.Has("fullscreen"))
  {
    fullscreen = options.Get("fullscreen").As<Napi::Boolean>();
  }

  // get minWidth
  int minWidth = 0;
  if (options.Has("minWidth"))
  {
    minWidth = options.Get("minWidth").As<Napi::Number>();
  }

  // get minHeight
  int minHeight = 0;
  if (options.Has("minHeight"))
  {
    minHeight = options.Get("minHeight").As<Napi::Number>();
  }

  // get maxWidth
  int maxWidth = 0;
  if (options.Has("maxWidth"))
  {
    maxWidth = options.Get("maxWidth").As<Napi::Number>();
  }

  // get maxHeight
  int maxHeight = 0;
  if (options.Has("maxHeight"))
  {
    maxHeight = options.Get("maxHeight").As<Napi::Number>();
  }

  // get transparent
  bool transparent = false;
  if (options.Has("transparent"))
  {
    transparent = options.Get("transparent").As<Napi::Boolean>();
  }

  // get frame
  bool frame = false;
  if (options.Has("frame"))
  {
    frame = options.Get("frame").As<Napi::Boolean>();
  }

  // get show
  bool show = true;
  if (options.Has("show"))
  {
    show = options.Get("show").As<Napi::Boolean>();
  }

  // get backgroundColor
  std::string backgroundColor = "";
  if (options.Has("backgroundColor"))
  {
    backgroundColor = options.Get("backgroundColor").As<Napi::String>();
  }

  m_pClientWebBrowser = new ClientWebBrowser();

  if (options.Has("onCreated"))
  {
    Napi::Function func = options.Get("onCreated").As<Napi::Function>();
    m_pClientWebBrowser->m_onCreatedCallback = Napi::Persistent(func);
    m_pClientWebBrowser->m_onCreatedCallback.SuppressDestruct();
  }

  if (options.Has("onClose"))
  {
    Napi::Function func = options.Get("onClose").As<Napi::Function>();
    m_pClientWebBrowser->m_onCloseCallback = Napi::Persistent(func);
    m_pClientWebBrowser->m_onCloseCallback.SuppressDestruct();
  }

  if (options.Has("onError"))
  {
    Napi::Function func = options.Get("onError").As<Napi::Function>();
    m_pClientWebBrowser->m_onErrorCallback = Napi::Persistent(func);
    m_pClientWebBrowser->m_onErrorCallback.SuppressDestruct();
  }
}

Napi::Value NativeBrowser::GetTextureId(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  auto webView = m_pClientWebBrowser->GetWebView();

  int textureId = 0;

  if (webView)
  {
    textureId = webView->GetTextureId();
  }

  return Napi::Number::New(env, textureId);
}

Napi::Value NativeBrowser::Update(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// canNavigateBack(): boolean;
Napi::Value NativeBrowser::CanNavigateBack(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// canNavigateForward(): boolean;
Napi::Value NativeBrowser::CanNavigateForward(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// executeJavascript(jsCode: string): boolean;
Napi::Value NativeBrowser::ExecuteJavascript(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  std::string jsCode = info[0].As<Napi::String>();
  auto webView = m_pClientWebBrowser->GetWebView();
  if(webView) {
    webView->ExecuteJavaScript(jsCode);
  }
  return env.Undefined();
}

// focus(): boolean;
Napi::Value NativeBrowser::Focus(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  bool state = info[0].As<Napi::Boolean>();

  auto webView = m_pClientWebBrowser->GetWebView();
  if (webView)
    webView->Focus(state);

  return env.Undefined();
}

// getProperty(key : string): boolean;
Napi::Value NativeBrowser::GetProperty(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  std::string key = info[0].As<Napi::String>();

  auto webView = m_pClientWebBrowser->GetWebView();
  if (webView)
  {
    std::string value;
    webView->GetProperty(key, value);
    return Napi::String::New(env, value);
  }
  return env.Undefined();
}

// getSettings(): Record<string, any>;
Napi::Value NativeBrowser::GetSettings(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// getSource(callback:(code: string) => void): boolean;
Napi::Value NativeBrowser::GetSource(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// getTitle(): string;
Napi::Value NativeBrowser::GetTitle(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// getURL(): string;
Napi::Value NativeBrowser::GetURL(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  std::string url = m_pClientWebBrowser->GetUrl();
  return Napi::String::New(env, url);
}

// injectMouseMove(posX: number,  posY: number): boolean;
Napi::Value NativeBrowser::InjectMouseMove(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// injectMouseDown(mouseButton: string): boolean;
Napi::Value NativeBrowser::InjectMouseDown(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);


  return env.Undefined();
}

// injectMouseUp(mouseButton: string): boolean;
Napi::Value NativeBrowser::InjectMouseUp(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// injectMouseWheel(verticalScroll: number, horizontalScroll: number): boolean;
Napi::Value NativeBrowser::InjectMouseWheel(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// injectKeyboardEvent(windowKeyCode: number,  keyCode: number,  modifiers: number, isSystemKey: boolean, type: number): boolean;
Napi::Value NativeBrowser::InjectKeyboardEvent(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  CefKeyEvent keyEvent;
  keyEvent.windows_key_code = info[0].As<Napi::Number>();
  keyEvent.native_key_code = info[1].As<Napi::Number>();
  keyEvent.modifiers = info[2].As<Napi::Number>();
  keyEvent.is_system_key = info[3].As<Napi::Boolean>() ? TRUE: FALSE;
  keyEvent.type = (cef_key_event_type_t)info[4].As<Napi::Number>().Int32Value();

  auto webView = m_pClientWebBrowser->GetWebView();
  if (webView) {
    webView->InjectKeyboardEvent(keyEvent);
  }
  return env.Undefined();
}

// isFocused(): boolean;
Napi::Value NativeBrowser::IsFocused(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// isLoading(): boolean;
Napi::Value NativeBrowser::IsLoading(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  bool isLoading = false;

  auto webView = m_pClientWebBrowser->GetWebView();
  if (webView)
    isLoading = webView->IsLoading();

  return Napi::Boolean::New(env, isLoading);
}

// isRenderingPaused(): boolean;
Napi::Value NativeBrowser::IsRenderingPaused(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// loadURL(url: string, postData?: string, urlEncoded?: boolean): boolean;
Napi::Value NativeBrowser::LoadURL(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  std::string url = info[0].As<Napi::String>();
  m_pClientWebBrowser->GetWebView()->LoadURL(url.c_str());
  return env.Undefined();
}

// navigateBack(): boolean;
Napi::Value NativeBrowser::NavigateBack(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  auto webView = m_pClientWebBrowser->GetWebView();

  bool result = false;

  if (webView)
    result = webView->GoBack();

  return Napi::Boolean::New(env, result);
}

// navigateForward(): boolean;
Napi::Value NativeBrowser::NavigateForward(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  auto webView = m_pClientWebBrowser->GetWebView();

  bool result = false;

  if (webView)
    result = webView->GoForward();

  return Napi::Boolean::New(env, result);
}

// reloadPage(ignoreCache: boolean): boolean;
Napi::Value NativeBrowser::ReloadPage(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  bool bIgnoreCache = info[0].As<Napi::Boolean>();

  bool result = false;
  auto webView = m_pClientWebBrowser->GetWebView();

  if (webView) {
    webView->Reload(bIgnoreCache);
    result = true;
  }
  return Napi::Boolean::New(env, result);
}

// resize(width: number, height: number): boolean;
Napi::Value NativeBrowser::Resize(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int width = info[0].As<Napi::Number>();
  int height = info[1].As<Napi::Number>();

  auto webView = m_pClientWebBrowser->GetWebView();

  if (webView)
    webView->Resize(width, height);

  return env.Undefined();
}

// setAjaxHandler( url: string, handler: (props: {get: any, post: any}) => void) : boolean;
Napi::Value NativeBrowser::SetAjaxHandler(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// setProperty(key: string, value: string): boolean;
Napi::Value NativeBrowser::SetProperty(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  std::string key = info[0].As<Napi::String>();
  std::string value = info[1].As<Napi::String>();

  auto webView = m_pClientWebBrowser->GetWebView();

  if (webView)
    webView->SetProperty(key.c_str(), value.c_str());

  return env.Undefined();
}

// setRenderingPaused(paused: boolean): boolean;
Napi::Value NativeBrowser::SetRenderingPaused(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  return env.Undefined();
}

// setVolume(volume: number): boolean;
Napi::Value NativeBrowser::SetVolume(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int volume = info[0].As<Napi::Number>();

  auto webView = m_pClientWebBrowser->GetWebView();

  bool success = false;

  if (webView) {
    success = webView->SetAudioVolume(volume);
  }

  return Napi::Boolean::New(env, success);
}

// toggleDevTools(visible: boolean): boolean;
Napi::Value NativeBrowser::ToggleDevTools(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  bool visible = info[0].As<Napi::Boolean>();

  auto webView = m_pClientWebBrowser->GetWebView();

  if (webView)
    return Napi::Boolean::New(env, webView->ToggleDevTools(visible));

  return env.Undefined();
}

//------------------------------------------------------------------------------

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

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("init", Napi::Function::New(env, init));
  exports.Set("NativeBrowserUpdate", Napi::Function::New(env, NativeBrowserUpdate));
  return NativeBrowser::Init(env, exports);
}

NODE_API_MODULE(init, Init)
