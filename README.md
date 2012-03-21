addonSample
============
### Node.js sample native addon

The purpose of this repository is to demonstrate building a native addon for
node that is more involved than the usual "Hello World" sample.  The addon
itself doesn't really do anything, but it does strive to illustrate the
following:

* How to wrap a C++ function so it can be called from javascript
* How to accept arguments to a javascript function and pass them along to a
C++ function.
* How to expose an EXISTING C++ class to javascript.  One that the addon
developer does not control, and can't modify to extend node::ObjectWrap.

Building
--------
There is a build-time dependency on
[node-gyp](https://github.com/TooTallNate/node-gyp.git) 0.3.5+.  If node-gyp
is not on the path, make will install it (via npm) into the `node_modules`
directory.

To build just run `make` (GNU make).  It has been tested on Mac OS X Lion and
will likely work on other *nix flavors.  With any luck, you'll get output that
looks like the following:

```
$ make
info it worked if it ends with ok
spawn python [ '/Users/matt/.node-gyp/0.6.13/tools/gyp_addon',
  'binding.gyp',
  '-I/Users/matt/projects/addonSample/build/config.gypi',
  '-f',
  'make' ]
info done ok
/Users/matt/local/bin/node-gyp build
info it worked if it ends with ok
spawn make [ 'BUILDTYPE=Release', '-C', 'build' ]
  CXX(target) Release/obj.target/bindings/src/binding.o
  CXX(target) Release/obj.target/bindings/src/native_object_wrapper.o
  CXX(target) Release/obj.target/bindings/src/library.o
  SOLINK(target) Release/bindings.node
  SOLINK(target) Release/bindings.node: Finished
info done ok
[ { id: 1 },
  { id: 2 },
  { id: 3 },
  { id: 4 },
  { id: 5 },
  { id: 6 },
  { id: 7 },
  { id: 8 },
  { id: 9 },
  { id: 10 } ]
```

License
-------

(The MIT License)

Copyright (c) 2012 Matt Gollob

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
