#include <uC++.h>
#include <uSemaphore.h>
#include <vector>
#include <string>

#include "q1kvqueue.h"

using namespace std;

_Task Reducer {
  void main();

public:
  Reducer(int id, int num_reducers, uSemaphore * signal,
          const vector<Mapper *> & mappers);
  virtual ~Reducer();
  // DJB2 hash. Include as part of the class interface.
  unsigned long hash(const string & str) {
    unsigned long hash = 5381;
    for (unsigned int i = 0; i < str.size(); ++i) {
      hash = ((hash << 5) + hash) + str[i];
    }
    return hash;
  }
  int getID();
  int getNumReducers();
  uSemaphore *getSignal();
  const vector<Mapper *> &getMappers();

private:
  int id, num_reducers;
  uSemaphore *signal;
  const vector<Mapper *> &mappers;
}
;
