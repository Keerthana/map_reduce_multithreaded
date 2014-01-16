#include "q1kvqueue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
Mapper::Mapper(const string &filename, int queue_len, uSemaphore *signal)
    : filename(filename), queue_len(queue_len), signal(signal) {
  q = new KVQueue(queue_len);
}
Mapper::~Mapper() { delete q; }

uSemaphore *Mapper::getSignal() { return signal; }

const string &Mapper::getFilename() { return filename; }
int Mapper::queuesize() { return queue_len; }
void Mapper::main() {
  ifstream datastream(getFilename().c_str(), std::ifstream::in);
  string word;

  while (1) {
    datastream >> word;
    if (datastream.eof())
      break;

    KeyValue *k = new KeyValue(word, 1);
    signal->P();
    q->pushBack(*k);
    signal->V();
    delete k;
  }
  q->close();
  signal->V();
}
