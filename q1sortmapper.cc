#include "q1sortmapper.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

SortMapper::SortMapper(const string &filename, int queue_len, int buffer_size,
                       uSemaphore *signal)
    : Mapper(filename, queue_len, signal), filename(filename),
      queue_len(queue_len), buffer_size_(buffer_size), signal(signal) {
  //  q = new KVQueue(queue_len);
}
SortMapper::~SortMapper() {
  //  delete q;
}

void SortMapper::main() {
  ifstream datastream(getFilename().c_str(), std::ifstream::in);
  string word;

  while (1) {
    map<string, int> contents;
    for (int i = 0; i < buffer_size_; ++i) {
      datastream >> word;
      if (datastream.eof())
        break;
      ++contents[word];
    }
    for (map<string, int>::iterator i = contents.begin(); i != contents.end();
         ++i) {
      if ((*i).second > 1) {
        Mapper::KeyValue *k = new Mapper::KeyValue((*i).first, (*i).second);
        signal->P();
	//  q->pushBack(*k);
        signal->V();
        delete k;
      }
    }
  }

  //  q->close();
  signal->V();
}
