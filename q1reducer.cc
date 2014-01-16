#include "q1reducer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
Reducer::Reducer(int id, int num_reducers, uSemaphore *signal,
                 const vector<Mapper *> &mappers)
    : id(id), num_reducers(num_reducers), signal(signal), mappers(mappers) {}

Reducer::~Reducer() {}

int Reducer::getID() { return id; }

int Reducer::getNumReducers() { return num_reducers; }

uSemaphore *Reducer::getSignal() { return signal; }

const vector<Mapper *> &Reducer::getMappers() { return mappers; }

void Reducer::main() {

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
    osacquire(cout) << (*i).first << " : " << (*i).second << endl;
  }
}
