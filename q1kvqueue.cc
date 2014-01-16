#include "q1kvqueue.h"

using namespace std;

KVQueue::KVQueue(int size) : size(size) {
  closed = 0;
  kvq = queue<Mapper::KeyValue>();
}

void KVQueue::pushBack(const Mapper::KeyValue &item) { kvq.push(item); }

Mapper::KeyValue KVQueue::popFront() {
  Mapper::KeyValue temp = kvq.front();
  kvq.pop();
  return temp;
}

int KVQueue::peekFront(Mapper::KeyValue *val) throw(EmptyAndClosed) {
  if (kvq.empty()) {
    return -1;
  } else
    *val = kvq.front();
  return 0;
}
void KVQueue::close() { closed = 1; }
