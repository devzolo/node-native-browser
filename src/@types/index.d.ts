declare module '@devzolo/node-native-browser' {

  interface NativeBrowserOptions {
    hwnd?: number;
    url?: string;
    width?: number;
    height?: number;
    title?: string;
    toolbar?: boolean;
    resizable?: boolean;
    fullscreen?: boolean;
    minWidth?: number;
    minHeight?: number;
    maxWidth?: number;
    maxHeight?: number;
    transparent?: boolean;
    frame?: boolean;
    show?: boolean;
    backgroundColor?: string;
    onCreated?: (browser: NativeBrowser) => void;
    onClose?: (browser: NativeBrowser) => void;
    onError?: (browser: NativeBrowser, error: Error) => void;
  }

  export class NativeBrowser {
    constructor(options: NativeBrowserOptions);
    getTextureId(): number;
    getUrl(): string;
    loadUrl(url: string): void;
    bindTexture(): void;
    update(): void;
    destroy(): void;
    resize(width: number, height: number): void;
  }

  export function NativeBrowserUpdate(): void;
}
