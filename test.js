
var lib = require('./lib');

function runit() {
  var result = lib.runFn(10);
  console.log(result);
}

//runit();
var id = setInterval(runit, 100);  // Do it over and over to watch for memory leaks

// Stop it after one minute
setTimeout(function() {
  clearInterval(id);
}, 60000);
