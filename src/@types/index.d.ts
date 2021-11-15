declare module '@devzolo/node-native-browser' {
  namespace native {
    interface NativeBrowserCore {
      initialize(): void;
      init(): boolean;
      loadPlugin(path: string): void;
      NativeBrowser: new (path: string) => NativeBrowser;
      NativeBrowserType: typeof NativeBrowser;
    }

    class NativeBrowser {
      getUrl(): string;
      setUrl(url: string): void;
    }
  }
  const core: native.NativeBrowserCore;
  export = core;
}
