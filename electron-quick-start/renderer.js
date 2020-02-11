// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.
const addon = require('node-addon-api') // develop

function callBack(msg) {
    console.log(msg);
    let s = sssss
    console.log(msg);
}
  
function wrap(fn) {
    return function wrapper(...args) {
      try {
        return fn.apply(this, args);
      } catch (e) {
        // do what you'd like to do with the error `e` here.
        throw e
      }
    };
  }

addon.asyncCallback(wrap(callBack));

//addon.asyncCallback(callBack);

//addon.syncCallback(callBack);

