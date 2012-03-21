// Include this file's header first
#include "binding.h"

// System/library includes
#include <node.h>

// Additional application includes
#include "native_object_wrapper.h"
#include "library.h"

using v8::Arguments;
using v8::Array;
using v8::Exception;
using v8::Handle;
using v8::HandleScope;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Undefined;
using v8::Value;

Handle<Value> JS_RunFn(const Arguments& args) {
  HandleScope scope;

  if (args.Length() != 1) {
    ThrowException(Exception::TypeError(String::New(
      "Wrong number of arguments.  Expected 1")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsInt32()) {
    ThrowException(Exception::TypeError(String::New(
      "First argument must be a 32-bit signed integer")));
    return scope.Close(Undefined());
  }

  std::vector<NativeObject*>* libResult = LibraryFn(args[0]->Int32Value());

  // Allocate a javascript array to hold the wrapped NativeObjects
  Local<Array> arr = Array::New(libResult->size());

  // Iterate over the vector, wrapping each element and adding it to the array
  std::vector<NativeObject*>::iterator iterator = libResult->begin();
  int32_t index = 0;

  while(iterator < libResult->end()) {
    Handle<Object> wrapper = NativeObjectWrapper::wrap(*iterator);
    arr->Set(Number::New(index++), wrapper);
    iterator++;
  }

  // TODO:  I know I'm leaking the vector here, but can't delete it b/c it'll
  // destroy all the elements that we just wrapped.  The vector's lifetime
  // needs to be tied to something on the JS side so it can be deleted at the
  // correct time, but how?

  return scope.Close(arr);
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "runFn", JS_RunFn);
}
NODE_MODULE(bindings, init)
