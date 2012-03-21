
var lib = require('./lib');

function runit() {
  var result = lib.runFn(10);
  console.log(result);
}

runit();
//setInterval(runit, 1000);  // Do it over and over to watch for memory leaks
