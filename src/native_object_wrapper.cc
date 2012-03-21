#include "native_object_wrapper.h"

#include <v8.h>

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

Handle<Object> NativeObjectWrapper::wrap(NativeObject* obj) {
  HandleScope scope;

  //  TODO:  Creating a new template for every instance that gets wrapped
  //  seems redundant.  However, attempts to make it static and only set it up
  //  once were met with a segfault when NewInstance() was called.  Is such a
  //  thing possible?

  // This code based on http://blog.owned.co.za/?p=205
  Handle<ObjectTemplate> raw_template = ObjectTemplate::New();
  raw_template->SetInternalFieldCount(1);
  raw_template->SetAccessor(String::New("id"), JS_GetId, JS_SetId);

  Persistent<ObjectTemplate> class_template =
    Persistent<ObjectTemplate>::New(raw_template);
  Handle<Object> wrapper = class_template->NewInstance();
  wrapper->SetInternalField(0, External::New(obj));

  // TODO:  More leakage here too.  Dispose() and Clear() are never getting
  // called on class_template (should it even be Persistent?), but when and
  // how should that be handled?

  return scope.Close(wrapper);
}

NativeObject* NativeObjectWrapper::unwrap(Handle<Object> wrapper) {
  Handle<External> field = Handle<External>::Cast(wrapper->GetInternalField(0));
  return static_cast<NativeObject*>(field->Value());
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
