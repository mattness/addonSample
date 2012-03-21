#include "native_object_wrapper.h"

#include "library.h"

using v8::AccessorInfo;
using v8::External;
using v8::Handle;
using v8::HandleScope;
using v8::Integer;
using v8::Local;
using v8::Object;
using v8::ObjectTemplate;
using v8::Persistent;
using v8::String;
using v8::Undefined;
using v8::Value;

Persistent<ObjectTemplate> NativeObjectWrapper::class_template_;
static void CleanupCallback(Persistent<Value> value, void *data);

void NativeObjectWrapper::Initialize() {
  HandleScope scope;

  Local<ObjectTemplate> raw_template = ObjectTemplate::New();
  raw_template->SetInternalFieldCount(1);
  raw_template->SetAccessor(String::New("id"), JS_GetId, JS_SetId);

  class_template_ = Persistent<ObjectTemplate>::New(raw_template);
}

Handle<Object> NativeObjectWrapper::wrap(NativeObject* obj) {
  HandleScope scope;

  // Create an instance of our class template and store it in a local handle...
  Local<Object> handle = NativeObjectWrapper::class_template_->NewInstance();
  // ... so we can wrap it in a Persistent handle ...
  Persistent<Object> wrapper = Persistent<Object>::New(handle);
  // ... and attach the native object and cleanup function.
  wrapper->SetPointerInInternalField(0, obj);
  wrapper.MakeWeak(obj, CleanupCallback);
  // MarkIndependent is an optimization that helps the GC speed up sweeps
  wrapper.MarkIndependent();

  return scope.Close(wrapper);
}

NativeObject* NativeObjectWrapper::unwrap(Handle<Object> wrapper) {
  NativeObject* obj = static_cast<NativeObject*>(
    wrapper->GetPointerFromInternalField(0));
  return obj;
}

void CleanupCallback(Persistent<Value> value, void *data) {
  NativeObject *obj = static_cast<NativeObject*>(data);
  delete obj;
}

Handle<Value> NativeObjectWrapper::JS_GetId(Local<String> property,
    const AccessorInfo& info) {
  HandleScope scope;

  NativeObject* obj = unwrap(info.Holder());

  return scope.Close(Integer::New(obj->get_id()));
}

void NativeObjectWrapper::JS_SetId(Local<String> property,
    Local<Value> value, const AccessorInfo& info) {
  HandleScope scope;

  NativeObject* obj = unwrap(info.Holder());
  obj->set_id(value->Int32Value());

  scope.Close(Undefined());
}
