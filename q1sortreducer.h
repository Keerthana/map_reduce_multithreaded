#include <uC++.h>
#include <uSemaphore.h>
#include <string>
#include "q1reducer.h"
using namespace std;

_Task SortReducer : public Reducer {
  void main();

public:
  SortReducer(int id, int num_reducers, uSemaphore * signal,
              const vector<Mapper *> & mappers);
  virtual ~SortReducer();

private:
  int id, num_reducers;
  uSemaphore *signal;
  const vector<Mapper *> &mappers;
}
;
