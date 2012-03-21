#ifndef SRC_BINDING_H_
#define SRC_BINDING_H_

// Forward-declare the v8 types
namespace v8 {
  template <class T> class Handle;
  class Object;
}

void init(v8::Handle<v8::Object> target);

#endif  // SRC_BINDING_H_
