#ifndef NATIVEBROWSER_H
#define NATIVEBROWSER_H

#include <napi.h>
#include "common.hh"

class ClientWebBrowser;

class NativeBrowser : public Napi::ObjectWrap<NativeBrowser>
{
public:
  void * inner_obj_;
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  NativeBrowser(const Napi::CallbackInfo &info);

private:
  ClientWebBrowser* m_pClientWebBrowser;

  static Napi::FunctionReference constructor;
  Napi::Value LoadUrl(const Napi::CallbackInfo &info);
  Napi::Value GetUrl(const Napi::CallbackInfo &info);
  Napi::Value GetTextureId(const Napi::CallbackInfo &info);
  Napi::Value Update(const Napi::CallbackInfo &info);
  Napi::Value BindTexture(const Napi::CallbackInfo &info);
//   // Napi::Value SetUrl(const Napi::CallbackInfo &info);
//   // Napi::Value GetTitle(const Napi::CallbackInfo &info);
//   // Napi::Value GetWidth(const Napi::CallbackInfo &info);
//   // Napi::Value GetHeight(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsLoading(const Napi::CallbackInfo &info);
//   // Napi::Value GetCanGoBack(const Napi::CallbackInfo &info);
//   // Napi::Value GetCanGoForward(const Napi::CallbackInfo &info);
//   // Napi::Value GetCanReload(const Napi::CallbackInfo &info);
//   // Napi::Value GetCanStop(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsCrashed(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsFullscreen(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsPointerLocked(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsDevToolsOpen(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsWaitingForResponse(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsWaitingForResponseFromActiveFrame(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsWaitingForResponseFromAnyFrame(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsWaitingForResponseFromSpecificFrame(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsWaitingForNavigation(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsWaitingForNavigationOfActiveFrame(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsWaitingForNavigationOfAnyFrame(const Napi::CallbackInfo &info);
//   // Napi::Value GetIsWaitingForNavigationOfSpecificFrame(const Napi::CallbackInfo &info);
// public:
//   // void OnLoadStarted();
//   // void OnLoadStopped();
//   // void OnLoadFailed(const std::string &error);
//   // void OnLoadFinished();
//   // void OnTitleChanged(const std::string &title);
//   // void OnUrlChanged(const std::string &url);
//   // void OnWidthChanged(int width);
//   // void OnHeightChanged(int height);
//   // void OnIsLoadingChanged(bool isLoading);
//   // void OnCanGoBackChanged(bool canGoBack);
//   // void OnCanGoForwardChanged(bool canGoForward);
//   // void OnCanReloadChanged(bool canReload);
//   // void OnCanStopChanged(bool canStop);
//   // void OnIsCrashedChanged(bool isCrashed);
//   // void OnIsFullscreenChanged(bool isFullscreen);
//   // void OnIsPointerLockedChanged(bool isPointerLocked);
//   // void OnIsDevToolsOpenChanged(bool isDevToolsOpen);
//   // void OnIsWaitingForResponseChanged(bool isWaitingForResponse);
//   // void OnIsWaitingForResponseFromActiveFrameChanged(bool isWaitingForResponseFromActiveFrame);
//   // void OnIsWaitingForResponseFromAnyFrameChanged(bool isWaitingForResponseFromAnyFrame);
//   // void OnIsWaitingForResponseFromSpecificFrameChanged(bool isWaitingForResponseFromSpecificFrame);
//   // void OnIsWaitingForNavigationChanged(bool isWaitingForNavigation);
//   // void OnIsWaitingForNavigationOfActiveFrameChanged(bool isWaitingForNavigationOfActiveFrame);
//   // void OnIsWaitingForNavigationOfAnyFrameChanged(bool isWaitingForNavigationOfAnyFrame);
//   // void OnIsWaitingForNavigationOfSpecificFrameChanged(bool isWaitingForNavigationOfSpecificFrame);
//   // void OnDevToolsOpened();
//   // void OnDevToolsClosed();

// private:
//   // std::string url;
//   // std::string title;
//   // int width;
//   // int height;
//   // bool isLoading;
//   // bool canGoBack;
//   // bool canGoForward;
//   // bool canReload;
//   // bool canStop;
//   // bool isCrashed;
//   // bool isFullscreen;
//   // bool isPointerLocked;
//   // bool isDevToolsOpen;
//   // bool isWaitingForResponse;
//   // bool isWaitingForResponseFromActiveFrame;
//   // bool isWaitingForResponseFromAnyFrame;
//   // bool isWaitingForResponseFromSpecificFrame;
//   // bool isWaitingForNavigation;
//   // bool isWaitingForNavigationOfActiveFrame;
//   // bool isWaitingForNavigationOfAnyFrame;
//   // bool isWaitingForNavigationOfSpecificFrame;
//   // Napi::FunctionReference onLoadStartedCallback;
//   // Napi::FunctionReference onLoadStoppedCallback;
//   // Napi::FunctionReference onLoadFailedCallback;
//   // Napi::FunctionReference onLoadFinishedCallback;
//   // Napi::FunctionReference onTitleChangedCallback;
//   // Napi::FunctionReference onUrlChangedCallback;
//   // Napi::FunctionReference onWidthChangedCallback;
//   // Napi::FunctionReference onHeightChangedCallback;
//   // Napi::FunctionReference onIsLoadingChangedCallback;
//   // Napi::FunctionReference onCanGoBackChangedCallback;
//   // Napi::FunctionReference onCanGoForwardChangedCallback;
//   // Napi::FunctionReference onCanReloadChangedCallback;
//   // Napi::FunctionReference onCanStopChangedCallback;
//   // Napi::FunctionReference onIsCrashedChangedCallback;
//   // Napi::FunctionReference onIsFullscreenChangedCallback;
//   // Napi::FunctionReference onIsPointerLockedChangedCallback;
//   // Napi::FunctionReference onIsDevToolsOpenChangedCallback;
//   // Napi::FunctionReference onIsWaitingForResponseChangedCallback;
//   // Napi::FunctionReference onIsWaitingForResponseFromActiveFrameChangedCallback;
//   // Napi::FunctionReference onIsWaitingForResponseFromAnyFrameChangedCallback;
};

#endif //NATIVEBROWSER_H
