var addon = require('./build/Release/addon.node');

function callBack(msg) {
  console.log(msg);
  let s = sssss
  console.log(msg);
}


addon.asyncCallback(callBack);


//addon.syncCallback(callBack);

