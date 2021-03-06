#ifndef SRC_NATIVEOBJECTWRAPPER_H_
#define SRC_NATIVEOBJECTWRAPPER_H_

#include <v8.h>

class NativeObject;

class NativeObjectWrapper {
public:
  static void Initialize();
  static v8::Handle<v8::Object> wrap(NativeObject* obj);
  static NativeObject* unwrap(v8::Handle<v8::Object> wrapper);
  static v8::Handle<v8::Value> JS_GetId(v8::Local<v8::String> property,
    const v8::AccessorInfo& info);
  static void JS_SetId(v8::Local<v8::String> property,
    v8::Local<v8::Value> value, const v8::AccessorInfo& info);

private:
  static v8::Persistent<v8::ObjectTemplate> class_template_;
};

#endif  // SRC_NATIVEOBJECTWRAPPER_H_
