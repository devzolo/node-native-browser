#ifndef NATIVEBROWSER_H
#define NATIVEBROWSER_H

#include <napi.h>
#include "common.hh"

class ClientWebBrowser;

class NativeBrowser : public Napi::ObjectWrap<NativeBrowser>
{
public:
  void *inner_obj_;
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  NativeBrowser(const Napi::CallbackInfo &info);

private:
  ClientWebBrowser *m_pClientWebBrowser;

  static Napi::FunctionReference constructor;
  Napi::Value GetTextureId(const Napi::CallbackInfo &info);
  Napi::Value Update(const Napi::CallbackInfo &info);
  Napi::Value CanNavigateBack(const Napi::CallbackInfo &info);
  Napi::Value CanNavigateForward(const Napi::CallbackInfo &info);
  Napi::Value ExecuteJavascript(const Napi::CallbackInfo &info);
  Napi::Value Focus(const Napi::CallbackInfo &info);
  Napi::Value GetProperty(const Napi::CallbackInfo &info);
  Napi::Value GetSettings(const Napi::CallbackInfo &info);
  Napi::Value GetSource(const Napi::CallbackInfo &info);
  Napi::Value GetTitle(const Napi::CallbackInfo &info);
  Napi::Value GetURL(const Napi::CallbackInfo &info);
  Napi::Value InjectMouseMove(const Napi::CallbackInfo &info);
  Napi::Value InjectMouseDown(const Napi::CallbackInfo &info);
  Napi::Value InjectMouseUp(const Napi::CallbackInfo &info);
  Napi::Value InjectMouseWheel(const Napi::CallbackInfo &info);
  Napi::Value InjectKeyboardEvent(const Napi::CallbackInfo &info);
  Napi::Value IsFocused(const Napi::CallbackInfo &info);
  Napi::Value IsLoading(const Napi::CallbackInfo &info);
  Napi::Value IsRenderingPaused(const Napi::CallbackInfo &info);
  Napi::Value LoadURL(const Napi::CallbackInfo &info);
  Napi::Value NavigateBack(const Napi::CallbackInfo &info);
  Napi::Value NavigateForward(const Napi::CallbackInfo &info);
  Napi::Value ReloadPage(const Napi::CallbackInfo &info);
  Napi::Value Resize(const Napi::CallbackInfo &info);
  Napi::Value SetAjaxHandler(const Napi::CallbackInfo &info);
  Napi::Value SetProperty(const Napi::CallbackInfo &info);
  Napi::Value SetRenderingPaused(const Napi::CallbackInfo &info);
  Napi::Value SetVolume(const Napi::CallbackInfo &info);
  Napi::Value ToggleDevTools(const Napi::CallbackInfo &info);
};

#endif //NATIVEBROWSER_H
