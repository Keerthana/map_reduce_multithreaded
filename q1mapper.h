#include <uC++.h>
#include <uSemaphore.h>
#include <string>

using namespace std;
class KVQueue;
_Task Mapper {
  void main();

public:
  struct KeyValue {
    string key;
    int value;

    KeyValue(const string &key, int value) : key(key), value(value) {}
    KeyValue() {}
  };
  Mapper(const string & filename, int queue_len, uSemaphore * signal);

  virtual ~Mapper();
  uSemaphore *getSignal();
  const string &getFilename();
  int queuesize();
  KVQueue *q;

private:
  const string &filename;
  int queue_len;
  uSemaphore *signal;
}
;
