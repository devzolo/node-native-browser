const addon = require(`../bin/${process.platform}/${process.arch}/native-browser`);
export default addon;


//get yarn cache dir by node version
function getYarnCacheDir() {
    const nodeVersion = process.versions.node;
    const yarnCacheDir = path.join(process.env.HOME, '.cache', 'yarn', nodeVersion);
    return yarnCacheDir;

}

