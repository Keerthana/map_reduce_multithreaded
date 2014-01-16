#include "q1sortreducer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

SortReducer::SortReducer(int id, int num_reducers, uSemaphore *signal,
                 const vector<Mapper *> &mappers)
  : Reducer(id, num_reducers, signal, mappers), id(id), num_reducers(num_reducers), signal(signal), mappers(mappers) {}

SortReducer::~SortReducer() {}

void SortReducer::main() {
  map<string, int> contents;

  for (unsigned int i = 0; i < mappers.size(); ++i) {
    mappers[i]->getSignal()->P();
    KVQueue *qq = mappers[i]->q;
    mappers[i]->getSignal()->V();
    while (1) {
      Mapper::KeyValue Val;
      if (qq->peekFront(&Val) != 0)
        break;
      if ((int)(hash(Val.key) % num_reducers) == id) {
        signal->P();
        Val = qq->popFront();
        ++contents[Val.key];
        signal->V();
      }
    }
  }
  for (map<string, int>::iterator i = contents.begin(); i != contents.end();
       ++i) {
    osacquire(cout) << (*i).first << ":" << (*i).second << endl;
  }
}


