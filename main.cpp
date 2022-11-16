#include <iostream>
#include <string>

#include <sys/select.h>

#include <TestArray.hpp>
#include <HighestNumberCombination.hpp>

using namespace std;

int main(int argc, char *argv[]){
  TestArray *ta;

  // TODO: implement getopt interface.
  // TODO: check if inputs are correct.
  if(argc > 1){
    bool firstParamInteger = true;

    try{
      stoi(argv[1]);
    }catch(invalid_argument){
      firstParamInteger = false;
    }

    if(firstParamInteger){
      cout<<"Testing with array passed as parameters."<<endl;
      ta = new TestArray(argc-1, &argv[1]);
    }else{
      cout<<"Testing with randomly generated array with given length."<<endl;
      ta = new TestArray(stoi(argv[2]));
    }
  }else{
    uint64_t n;
    vector<uint64_t> buffer;

    int fd_stdin = fileno(stdin);
    fd_set readfds;
    FD_SET(fd_stdin, &readfds);
    struct timeval tv = {0, 0};

    while(select(1, &readfds, NULL, NULL, &tv) && cin>>n){
      buffer.push_back(n);
    }

    if(buffer.size() > 0){
      cout<<"Testing with piped values."<<endl;
      ta = new TestArray(buffer);
    }else{
      cout<<"Testing with randomly generated array."<<endl;
      ta = new TestArray();
    }
  }

  ta->printArray();

  int32_t result = 0; //HighestNumberCombination::search(ta->getArray(), ta->len());

  cout<<"Highest possible number is: "<<result<<endl;

  return 0;
}
