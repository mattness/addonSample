#include "library.h"

using std::vector;

vector<NativeObject*>* LibraryFn(int count) {
  vector<NativeObject*>* result = new vector<NativeObject*>();

  for (int i = 0; i < count; i++) {
    result->push_back(new NativeObject(i + 1));
  }

  return result;
}
