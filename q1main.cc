#include <uC++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <errno.h>
#include "q1reducer.h"
using namespace std;

void uMain::main() {
  int numReducers = 4, queueLength = 16, bufferSize = 0;
  std::string inputDir;

  switch (argc) {
  case 5:
    bufferSize = atoi(argv[4]);
  case 4:
    queueLength = atoi(argv[3]);
  case 3:
    numReducers = atoi(argv[2]);
  case 2:
    inputDir = argv[1];
    break;
  case 1:
    cerr << "Usage: " << argv[0]
         << " input-directory [num-reducers [ queue-length [sort-buffer-size]]]"
         << endl;
    exit(-1);
  }
  DIR *d;
  struct dirent *dirp;
  struct stat buffer;

  if ((d = opendir(inputDir.c_str())) == NULL) {
    cout << "Error(" << errno << ") opening " << inputDir << endl;
  }
  vector<string> files = vector<string>();
  while ((dirp = readdir(d)) != NULL) {
    lstat((inputDir + "/" + dirp->d_name).c_str(), &buffer);
    if (S_ISREG(buffer.st_mode))
      files.push_back(inputDir + "/" + dirp->d_name);
  }
  closedir(d);
  vector<Mapper *> mappers = vector<Mapper *>();
  uSemaphore signal(1);
  for (unsigned int i = 0; i < files.size(); i++) {
    mappers.push_back(new Mapper(files[i], queueLength, &signal));
  }

  vector<Reducer *> reducers = vector<Reducer *>();
  for (int i = 0; i < numReducers; ++i) {
    reducers.push_back(new Reducer(i, numReducers, &signal, mappers));
  }

  for (unsigned int i = 0; i < reducers.size(); i++) {
    delete reducers[i];
  }

  for (unsigned int i = 0; i < mappers.size(); i++) {
    delete mappers[i];
  }

  cout << "Finished! Semaphore counter: " << signal.counter() << endl;
}
