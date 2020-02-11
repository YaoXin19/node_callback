var addon = require('./index.js');

function wrap(fn) {
  return function wrapper(...args) {
    try {
      return fn.apply(this, args);
    } catch (e) {
      // do what you'd like to do with the error `e` here.
    }
  };
}

function callBack(msg) {
  console.log(msg);
  let s = sssss
  console.log(msg);
}


//addon.asyncCallback(wrap(callBack));

addon.asyncCallback(callBack);

//syncCallback(callBack);

