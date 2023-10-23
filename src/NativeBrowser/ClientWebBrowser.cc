#include "ClientWebBrowser.hh"
#include "WebCore.hh"


ClientWebBrowser::ClientWebBrowser(void)
{
  m_pWebView = WebCore::GetInstance()->CreateWebView(1, 1, true);
  m_pWebView->SetWebBrowserEvents(this);
}

ClientWebBrowser::~ClientWebBrowser(void)
{
  Unlink();
}

std::string ClientWebBrowser::GetUrl(void)
{
  return m_pWebView->GetUrl();
}


void ClientWebBrowser::Unlink()
{
    // Mark as being destroyed (DirectX surfaces won't be available anymore)
    // if (m_pWebView)
    //     m_pWebView->SetBeingDestroyed(true);

    // CClientRenderElement::Unlink();
}

// bool ClientWebBrowser::IsLoading()
// {
//     return m_pWebView->IsLoading();
// }

// bool ClientWebBrowser::LoadURL(const std::string& strURL, bool bFilterEnabled, const std::string& strPostData, bool bURLEncoded)
// {
//     return m_pWebView->LoadURL(strURL, bFilterEnabled, strPostData, bURLEncoded);
// }

// const std::string& ClientWebBrowser::GetTitle()
// {
//     return m_pWebView->GetTitle();
// }

// std::string ClientWebBrowser::GetURL()
// {
//     return m_pWebView->GetURL();
// }

// void ClientWebBrowser::SetRenderingPaused(bool bPaused)
// {
//     m_pWebView->SetRenderingPaused(bPaused);
// }

// void ClientWebBrowser::Focus()
// {
//     m_pWebView->Focus();
// }

// bool ClientWebBrowser::ExecuteJavascript(const std::string& strJavascriptCode)
// {
//     // Don't allow javascript code execution on remote websites
//     if (!m_pWebView->IsLocal())
//         return false;

//     m_pWebView->ExecuteJavascript(strJavascriptCode);
//     return true;
// }

// bool ClientWebBrowser::SetProperty(const std::string& strKey, const std::string& strValue)
// {
//     return m_pWebView->SetProperty(strKey, strValue);
// }

// bool ClientWebBrowser::GetProperty(const std::string& strKey, std::string& outValue)
// {
//     return m_pWebView->GetProperty(strKey, outValue);
// }

// void ClientWebBrowser::InjectMouseMove(int iPosX, int iPosY)
// {
//     m_pWebView->InjectMouseMove(iPosX, iPosY);
// }

// void ClientWebBrowser::InjectMouseDown(eWebBrowserMouseButton mouseButton)
// {
//     m_pWebView->InjectMouseDown(mouseButton);
// }

// void ClientWebBrowser::InjectMouseUp(eWebBrowserMouseButton mouseButton)
// {
//     m_pWebView->InjectMouseUp(mouseButton);
// }

// void ClientWebBrowser::InjectMouseWheel(int iScrollVert, int iScrollHorz)
// {
//     m_pWebView->InjectMouseWheel(iScrollVert, iScrollHorz);
// }

// bool ClientWebBrowser::IsLocal()
// {
//     return m_pWebView->IsLocal();
// }

// float ClientWebBrowser::GetAudioVolume()
// {
//     return m_pWebView->GetAudioVolume();
// }

// bool ClientWebBrowser::SetAudioVolume(float fVolume)
// {
//     return m_pWebView->SetAudioVolume(fVolume);
// }

// void ClientWebBrowser::GetSourceCode(const std::function<void(const std::string& code)>& callback)
// {
//     return m_pWebView->GetSourceCode(callback);
// }

// void ClientWebBrowser::Resize(const CVector2D& size)
// {
//     m_pWebView->Resize(size);
// }

// bool ClientWebBrowser::CanGoBack()
// {
//     return m_pWebView->CanGoBack();
// }

// bool ClientWebBrowser::CanGoForward()
// {
//     return m_pWebView->CanGoForward();
// }

// bool ClientWebBrowser::GoBack()
// {
//     return m_pWebView->GoBack();
// }

// bool ClientWebBrowser::GoForward()
// {
//     return m_pWebView->GoForward();
// }

// void ClientWebBrowser::Refresh(bool bIgnoreCache)
// {
//     m_pWebView->Refresh(bIgnoreCache);
// }

// ////////////////////////////////////////////////////////////////////////////
// //                                                                        //
// //            CWebBrowserEventsInterface implementation                   //
// //                                                                        //
// ////////////////////////////////////////////////////////////////////////////
// void ClientWebBrowser::Events_OnCreated()
// {
//     CLuaArguments Arguments;
//     CallEvent("onClientBrowserCreated", Arguments, false);
// }

// void ClientWebBrowser::Events_OnLoadingStart(const std::string& strURL, bool bMainFrame)
// {
//     CLuaArguments Arguments;
//     Arguments.PushString(strURL);
//     Arguments.PushBoolean(bMainFrame);
//     CallEvent("onClientBrowserLoadingStart", Arguments, false);
// }

// void ClientWebBrowser::Events_OnDocumentReady(const std::string& strURL)
// {
//     CLuaArguments Arguments;
//     Arguments.PushString(strURL);
//     CallEvent("onClientBrowserDocumentReady", Arguments, false);
// }

// void ClientWebBrowser::Events_OnLoadingFailed(const std::string& strURL, int errorCode, const std::string& errorDescription)
// {
//     CLuaArguments Arguments;
//     Arguments.PushString(strURL);
//     Arguments.PushNumber(errorCode);
//     Arguments.PushString(errorDescription);
//     CallEvent("onClientBrowserLoadingFailed", Arguments, false);
// }

// void ClientWebBrowser::Events_OnNavigate(const std::string& strURL, bool bIsBlocked, bool bIsMainFrame)
// {
//     CLuaArguments Arguments;
//     Arguments.PushString(strURL);
//     Arguments.PushBoolean(bIsBlocked);
//     Arguments.PushBoolean(bIsMainFrame);
//     CallEvent("onClientBrowserNavigate", Arguments, false);
// }

// void ClientWebBrowser::Events_OnPopup(const std::string& strTargetURL, const std::string& strOpenerURL)
// {
//     CLuaArguments Arguments;
//     Arguments.PushString(strTargetURL);
//     Arguments.PushString(strOpenerURL);
//     CallEvent("onClientBrowserPopup", Arguments, false);
// }

// void ClientWebBrowser::Events_OnChangeCursor(unsigned char ucCursor)
// {
//     CLuaArguments Arguments;
//     Arguments.PushNumber(ucCursor);
//     CallEvent("onClientBrowserCursorChange", Arguments, false);
// }

// void ClientWebBrowser::Events_OnTriggerEvent(const std::string& strEventName, const std::vector<std::string>& arguments)
// {
//     CLuaArguments Arguments;
//     for (std::vector<std::string>::const_iterator iter = arguments.begin(); iter != arguments.end(); ++iter)
//     {
//         Arguments.PushString(*iter);
//     }

//     bool bWasCancelled;
//     CStaticFunctionDefinitions::TriggerEvent(strEventName, *this, Arguments, bWasCancelled);
// }

// void ClientWebBrowser::Events_OnTooltip(const std::string& strTooltip)
// {
//     CLuaArguments Arguments;
//     Arguments.PushString(strTooltip);
//     CallEvent("onClientBrowserTooltip", Arguments, false);
// }

// void ClientWebBrowser::Events_OnInputFocusChanged(bool bGainedFocus)
// {
//     CLuaArguments Arguments;
//     Arguments.PushBoolean(bGainedFocus);
//     CallEvent("onClientBrowserInputFocusChanged", Arguments, false);
// }

// bool ClientWebBrowser::Events_OnResourcePathCheck(std::string& strURL)
// {
//     // If no resource is set, we are allowed to use the requested file
//     if (!m_pResource)
//         return true;

//     CResource* pTempResource = m_pResource;            // Make a copy to ignore a changed resource

//     if (CResourceManager::ParseResourcePathInput(strURL, pTempResource, &strURL))
//         return true;

//     return false;
// }

// bool ClientWebBrowser::Events_OnResourceFileCheck(const std::string& strPath, CBuffer& outFileData)
// {
//     // If no resource is set, we do not require to verify the file
//     if (!m_pResource)
//         return true;

//     auto pFile = g_pClientGame->GetResourceManager()->GetDownloadableResourceFile(strPath.ToLower());

//     // If we did not download this file, it has been script or user generated, nothing to verify for us
//     if (pFile == nullptr)
//         return true;

//     pFile->GenerateClientChecksum(outFileData);
//     return pFile->DoesClientAndServerChecksumMatch();
// }

// void ClientWebBrowser::Events_OnResourceBlocked(const std::string& strURL, const std::string& strDomain, unsigned char reason)
// {
//     CLuaArguments Arguments;
//     Arguments.PushString(strURL);
//     Arguments.PushString(strDomain);
//     Arguments.PushNumber(reason);
//     CallEvent("onClientBrowserResourceBlocked", Arguments, false);
// }

// void ClientWebBrowser::Events_OnAjaxRequest(CAjaxResourceHandlerInterface* pHandler, const std::string& strURL)
// {
//     auto callbackMapEntry = m_mapAjaxCallback.find(strURL);

//     if (callbackMapEntry == m_mapAjaxCallback.end())
//     {
//         pHandler->SetResponse("");
//         return;
//     }

//     auto    callback = callbackMapEntry->second;
//     std::string result = callback(pHandler->GetGetData(), pHandler->GetPostData());
//     pHandler->SetResponse(result);
// }

// bool ClientWebBrowser::AddAjaxHandler(const std::string& strURL, ajax_callback_t& handler)
// {
//     if (!m_pWebView->RegisterAjaxHandler(strURL))
//         return false;

//     m_mapAjaxCallback.insert(std::make_pair(strURL, handler));
//     return true;
// }

// bool ClientWebBrowser::RemoveAjaxHandler(const std::string& strURL)
// {
//     if (!m_pWebView->UnregisterAjaxHandler(strURL))
//         return false;

//     return m_mapAjaxCallback.erase(strURL) == 1;
// }

// bool ClientWebBrowser::ToggleDevTools(bool visible)
// {
//     return m_pWebView->ToggleDevTools(visible);
// }


void ClientWebBrowser::Events_OnCreated()
{
  if(!m_onCreatedCallback.IsEmpty()) {
    //pass m_instrance to the callback as Napi::Value
    m_onCreatedCallback.Call({});
  }
}
