import path from 'path';
const nativeDir = path.join(__dirname, '..', 'bin', process.platform, '/', process.arch);
const browser = require(path.join(nativeDir, 'native-browser'));

browser.initialize = (): unknown => {
  browser.init(nativeDir)
  return browser;
};

const browserEx = browser.initialize()

export default browserEx;

export enum eKeyEventType {
  KEYEVENT_RAWKEYDOWN = 0,
  KEYEVENT_KEYDOWN,
  KEYEVENT_KEYUP,
  KEYEVENT_CHAR
}

export const { NativeBrowser, NativeBrowserUpdate } = browserEx;
