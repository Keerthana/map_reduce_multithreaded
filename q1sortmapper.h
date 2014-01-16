#include <uC++.h>
#include <uSemaphore.h>
#include <string>
#include "q1mapper.h"
using namespace std;

_Task SortMapper : public Mapper {
  void main();

public:
  // Writes items to the queue in sorted order.
  SortMapper(const string &filename, int queue_len, int buffer_size,
             uSemaphore *signal);
  virtual ~SortMapper();
private:
  const string &filename;
  int queue_len;
  int buffer_size_;
  uSemaphore *signal;
}
;
