import path from 'path';
const nativeDir = path.join(__dirname, '..', 'bin', process.platform, '/', process.arch);
const browser = require(path.join(nativeDir, 'native-browser'));

browser.initialize = (): unknown => {
  browser.init(nativeDir)
  return browser;
};

const browserEx = browser.initialize()

export default browserEx;

export const { NativeBrowser, NativeBrowserUpdate } = browserEx;
