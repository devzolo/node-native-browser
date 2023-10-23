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
    //width: number, height: number,  isLocal: boolean, transparent: boolean
  }

  export enum eKeyEventType {
    ///
    // Notification that a key transitioned from "up" to "down".
    ///
    KEYEVENT_RAWKEYDOWN = 0,

    ///
    // Notification that a key was pressed. This does not necessarily correspond
    // to a character depending on the key and language. Use KEYEVENT_CHAR for
    // character input.
    ///
    KEYEVENT_KEYDOWN,

    ///
    // Notification that a key was released.
    ///
    KEYEVENT_KEYUP,

    ///
    // Notification that a character was typed. Use this for text input. Key
    // down events may generate 0, 1, or more than one character event depending
    // on the key, locale, and operating system.
    ///
    KEYEVENT_CHAR
  }
  export class NativeBrowser {
    constructor(options: NativeBrowserOptions);
    getTextureId(): number;
    update(): void;
    destroy(): void;

    canNavigateBack(): boolean;
    canNavigateForward(): boolean;
    executeJavascript(jsCode: string): boolean;
    focus(): boolean;
    getProperty(key : string): boolean;
    getSettings(): Record<string, any>;
    getSource(callback:(code: string) => void): boolean;
    getTitle(): string;
    getURL(): string;
    injectMouseDown(mouseButton: string): boolean;
    injectMouseUp(mouseButton: string): boolean;
    injectMouseMove(posX: number,  posY: number): boolean;
    injectMouseWheel(verticalScroll: number, horizontalScroll: number): boolean;
    injectKeyboardEvent(windowKeyCode: number,  keyCode: number,  modifiers: number, isSystemKey: boolean, type: number): boolean;
    isFocused(): boolean;
    isLoading(): boolean;
    isRenderingPaused(): boolean;
    loadURL(url: string, postData?: string, urlEncoded?: boolean): boolean;
    navigateBack(): boolean;
    navigateForward(): boolean;
    reloadPage(ignoreCache: boolean): boolean;
    resize(width: number, height: number): boolean;
    setAjaxHandler( url: string, handler: (props: {get: any, post: any}) => void) : boolean;
    setProperty(key: string, value: string): boolean;
    setRenderingPaused(paused: boolean): boolean;
    setVolume(volume: number): boolean;
    toggleDevTools(visible: boolean): boolean;
  }

  export function NativeBrowserUpdate(): void;
}
