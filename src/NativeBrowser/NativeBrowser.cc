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
#include "gl_core.hh"
#include "web_core.hh"
#include "render_handler.hh"


std::weak_ptr<WebCore> web_core;
WebCoreManager g_web_core_manager;

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

bool initialize_glew_context()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// Problem: glewInit failed, something is seriously wrong
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return false;
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	return true;
}

GLint pos_loc = -1;
GLint texcoord_loc = -1;
GLint tex_loc = -1;
GLint mvp_loc = -1;


Napi::FunctionReference NativeBrowser::constructor;

Napi::Object NativeBrowser::Init(Napi::Env env, Napi::Object exports)
{
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "NativeBrowser", {
    InstanceMethod("GetUrl", &NativeBrowser::GetUrl),
    // InstanceMethod("getBufferLength", &NativeBrowser::GetBufferLength),
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

  if (info.Length() < 1 || !info[0].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return;
  }

  int exit_code = 0;
  bool success = g_web_core_manager.setUp( &exit_code );
	if ( !success ) {
    Napi::TypeError::New(env, "Failed to initialize web core").ThrowAsJavaScriptException();
    return;
  }

	int width = 800;
	int height = 600;

  bool glew_init_success = initialize_glew_context();
	if (!glew_init_success) {
		g_web_core_manager.shutDown();
    Napi::TypeError::New(env, "Failed to initialize GLEW").ThrowAsJavaScriptException();
    return;
  }

  std::string url = info[0].As<Napi::String>();
  web_core = g_web_core_manager.createBrowser(url);
  web_core.lock()->reshape(width, height);
  GLuint prog = GLCore::createShaderProgram("shaders/tex.vert", "shaders/tex.frag");
  pos_loc = glGetAttribLocation(prog, "pos");

  if(prog != 0) {
    g_web_core_manager.shutDown();
    Napi::TypeError::New(env, "shader compile failed").ThrowAsJavaScriptException();
    return;
  }

	pos_loc = glGetAttribLocation(prog, "a_position");
	texcoord_loc = glGetAttribLocation(prog, "a_texcoord");
	tex_loc = glGetUniformLocation(prog, "s_tex");
	mvp_loc = glGetUniformLocation(prog, "u_mvp");

  {
    glUseProgram(prog);
    glBindTexture(GL_TEXTURE_2D, web_core.lock()->render_handler()->tex());
    g_web_core_manager.update();
  }

	GLCore::deleteProgram(prog);

	// close cef
	g_web_core_manager.removeBrowser( web_core );
	g_web_core_manager.shutDown();


}

Napi::Value NativeBrowser::GetUrl(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  std::string url = "";
  if (info.Length() > 0 && info[0].IsString())
  {
    url = info[0].As<Napi::String>();
  }
  return Napi::String::New(env, url);
}


// #include "gl_core.h"
// #include "render_handler.h"
// #include "web_core.h"

Napi::String HelloMethod(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::String::New(env, "world");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "hello"), Napi::Function::New(env, HelloMethod));
  return exports;
}

NODE_API_MODULE(hello, Init)
