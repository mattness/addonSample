//  This file (and its corresponding .cc file) wouldn't normally be part of
//  the addon.  Instead it would be part of some 3rd party library that gets
//  linked in at build time and has no idea that it's being leveraged from a
//  node/v8 addon at all.

#ifndef SRC_LIBRARY_H_
#define SRC_LIBRARY_H_

#include <vector>

class NativeObject {
 public:
  NativeObject(int id) : id_(id) {}
  ~NativeObject() {}
  int get_id() { return this->id_; }
  void set_id(int value) { this->id_ = value; }

 private:
  int id_;
};

std::vector<NativeObject*>* LibraryFn(int count);

#endif  // SRC_LIBRARY_H_
