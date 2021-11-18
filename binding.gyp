{
  'variables': {
    'platform': '<(OS)',
    'build_arch': '<!(node -p "process.arch")',
    'build_win_platform': '<!(node -p "process.arch==\'ia32\'?\'Win32\':process.arch")',
    'cef_build_root_dir': 'deps/cef3',
  },
  'conditions': [
    ['platform == "mac"', {'variables': {'platform': 'darwin'}}],
    ['platform == "win"', {'variables': {'platform': 'win32'}}],
  ],
  'targets': [
    {
      'target_name': 'CEFLauncherDLL',
      'type': 'shared_library',
      'sources': [
        'src/ceflauncher_DLL/Main.cc'
      ],
      'defines' : ['UNICODE'],
      'libraries': [
        'libcef', 'libcef_dll_wrapper'
      ],
      'include_dirs' : ['./','./deps/cef3'],
      'library_dirs' : ['<(module_root_dir)/deps/cef3/Release'],
    },
    {
      'target_name': 'CEFLauncher',
      'type': 'executable',
      'sources': [
        'src/ceflauncher/Main.cc'
      ],
      'defines' : ['UNICODE'],
      'dependencies': ['CEFLauncherDLL'],
      "conditions": [
        ['OS=="win"', {
          'msvs_settings': {
            'VCLinkerTool': {
              'SubSystem' : 2, # Windows
              'EntryPointSymbol': 'WinMainCRTStartup'
            }
          }
        }]
      ]
    },
    {
      'target_name': 'native-browser',
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      'sources': [
        'src/NativeBrowser/GLCore.cc',
        'src/NativeBrowser/WebDevTools.cc',
        'src/NativeBrowser/WebView.cc',
        'src/NativeBrowser/WebCore.cc',
        'src/NativeBrowser/WebApp.cc',
        'src/NativeBrowser/ClientWebBrowser.cc',
        'src/NativeBrowser/NativeBrowser.cc',
      ],
      'defines' : ['PSAPI_VERSION=1', 'NOMINMAX', 'NAPI_DISABLE_CPP_EXCEPTIONS','UNICODE'],
      'libraries': [
        'libcef', 'libcef_dll_wrapper',
        'Psapi', 'version', 'Winmm', 'Ws2_32', 'DbgHelp', 'opengl32', 'glew32'
      ],
      'library_dirs' : [
        '<(module_root_dir)/deps/cef3/Release',
        '<(module_root_dir)/deps/glew-2.1.0/lib/Release/x64'
      ],
      'include_dirs' : [
        "<!@(node -p \"require('node-addon-api').include\")",
        './','./deps/cef3',
        './deps/glew-2.1.0/include'
      ],
    },
    {
      "target_name": "copy_modules",
      "type":"none",
      "dependencies" : [ "native-browser" ],
      "copies":[
        {
          'destination': '<(module_root_dir)/bin/<(platform)/<(target_arch)',
          'files': [
            # CEF CEFLauncher
            '<(module_root_dir)/build/Release/CEFLauncher.exe',
            # CEF CEFLauncherDLL
            '<(module_root_dir)/build/Release/CEFLauncherDLL.dll',
            # CEF native-browser
            '<(module_root_dir)/build/Release/native-browser.node',
            # # CEF Release Files
            # '<(module_root_dir)/<(cef_build_root_dir)/Release/*',
            # # CEF Resource Files
            # '<(module_root_dir)/<(cef_build_root_dir)/Resources/*'
          ]
        },
        # {
        #   'destination': '<(module_root_dir)/bin/<(platform)/<(target_arch)/locales',
        #   'files': [
        #     '<(module_root_dir)/deps/glew-2.1.0/bin/Release/x64/locales/*',
        #   ]
        # },
        # {
        #   'destination': '<(module_root_dir)/bin/<(platform)/<(target_arch)/swiftshader',
        #   'files': [
        #     '<(module_root_dir)/deps/glew-2.1.0/bin/Release/x64/swiftshader/*',
        #   ]
        # },
        {
          'destination': '<(module_root_dir)/bin/<(platform)/<(target_arch)',
          'files': [
            '<(module_root_dir)/deps/glew-2.1.0/bin/Release/x64/*',
          ]
        },
        # {
        #   'destination': '<(module_root_dir)/bin/<(platform)/<(target_arch)/swiftshader',
        #   'files': [
        #     '<(module_root_dir)/<(cef_build_root_dir)/Release/swiftshader/*',
        #   ]
        # },
        # {
        #   'destination': '<(module_root_dir)/bin/<(platform)/<(target_arch)/locales',
        #   'files': [
        #     '<(module_root_dir)/<(cef_build_root_dir)/Resources/locales/*',
        #   ]
        # },
        {
          'destination': '<(module_root_dir)\\dist',
          'files': [
            '<(module_root_dir)\\src\\@types\\index.d.ts',
          ]
        }
      ]
    }
  ]
}
