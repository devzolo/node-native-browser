#include "WebCore.hh"
#include "UTF8.hh"

WebCore::WebCore()
{

}

WebCore::~WebCore()
{
}

bool WebCore::Initialise(std::string basePath)
{


  int exit_code;

  CefMainArgs mainArgs;
	exit_code = CefExecuteProcess(mainArgs, nullptr, nullptr);;
	if (exit_code >= 0) {
    MessageBox(NULL, L"CefExecuteProcess fail!!", L"failed", MB_OK);
		return false;
	}


  void *sandboxInfo = nullptr;
  CefRefPtr<WebApp> app(new WebApp);
  CefSettings settings;
  settings.log_severity = cef_log_severity_t::LOGSEVERITY_INFO;
  settings.multi_threaded_message_loop = true;
  settings.windowless_rendering_enabled = true;
  settings.no_sandbox = true;

  std::string browser_subprocess_path = basePath + "/CEFLauncher.exe";
  cef_string_utf8_to_utf16(browser_subprocess_path.c_str(), browser_subprocess_path.length(), &settings.browser_subprocess_path);

  std::string resources_dir_path = basePath;
  cef_string_utf8_to_utf16(resources_dir_path.c_str(), resources_dir_path.length(), &settings.resources_dir_path);

  std::string cache_path = basePath + "/cache";
  cef_string_utf8_to_utf16(cache_path.c_str(), cache_path.length(), &settings.cache_path);

  std::string locales_dir_path = basePath + "/locales";
  cef_string_utf8_to_utf16(locales_dir_path.c_str(), locales_dir_path.length(), &settings.locales_dir_path);

  std::string log_file = basePath + "/cefdebug.txt";
  cef_string_utf8_to_utf16(log_file.c_str(), log_file.length(), &settings.log_file);

  bool result = CefInitialize(mainArgs, settings, app, sandboxInfo);
	if (!result) {
		exit_code = -1;
		return false;
	}
  // LPWSTR lpBasePath = new WCHAR[basePath.length() + 1];

  // MultiByteToWideChar(CP_ACP, 0, basePath.c_str(), -1, lpBasePath, basePath.length() + 1);

  // MessageBox(NULL, L"Initialised", lpBasePath, MB_OK);
  return result;
}

WebView* WebCore::CreateWebView(unsigned int uiWidth, unsigned int uiHeight, bool bTransparent)
{
    // Create our webview implementation
    CefRefPtr<WebView> pWebView = new WebView(bTransparent);
    m_WebViews.push_back(pWebView);

    return static_cast<WebView*>(pWebView.get());
}

void WebCore::AddEventToEventQueue(std::function<void()> event, WebView* pWebView, const std::string& name)
{
    if (!pWebView)
        return;

    std::lock_guard<std::mutex> lock(m_EventQueueMutex);

    m_EventQueue.push_back(EventEntry(event, pWebView));
}

void WebCore::RemoveWebViewEvents(WebView* pWebView)
{
    std::lock_guard<std::mutex> lock(m_EventQueueMutex);

    for (auto iter = m_EventQueue.begin(); iter != m_EventQueue.end();)
    {
        // Increment iterator before we remove the element from the list (to guarantee iterator validity)
        auto tempIterator = iter++;
        if (tempIterator->pWebView == pWebView)
            m_EventQueue.erase(tempIterator);
    }
}


void WebCore::DoEventQueuePulse()
{
    std::list<EventEntry> eventQueue;
    {
        std::lock_guard<std::mutex> lock(m_EventQueueMutex);
        std::swap(eventQueue, m_EventQueue);
    }

    for (auto& event : eventQueue)
    {
        event.callback();
    }

    // Invoke paint method if necessary on the main thread
    for (auto& view : m_WebViews)
    {
        view->UpdateTexture();
    }
}

void WebCore::Update()
{
  DoEventQueuePulse();
}
