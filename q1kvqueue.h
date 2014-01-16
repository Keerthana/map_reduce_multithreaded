#include <uC++.h>
#include <string>
#include <vector>
#include <queue>
#include "q1mapper.h"
using namespace std;

//extern _Task Mapper;
class KVQueue {
public:
  struct EmptyAndClosed {
    int num_thrown;
    EmptyAndClosed(int num_thrown) : num_thrown(num_thrown) {}
  };
  KVQueue(int size);
  void pushBack(const Mapper::KeyValue &item);

  Mapper::KeyValue popFront();
  // Copy the front value to "val" without removing it from the queue. Return 0
  // on success and -1
  // if the queue is empty. Throw an EmptyAndClosed exception if the queue is
  // closed and empty.
  int peekFront(Mapper::KeyValue *val) throw(EmptyAndClosed);
  void close();

private:
  int size;
  int closed;
  queue<Mapper::KeyValue> kvq;
};
