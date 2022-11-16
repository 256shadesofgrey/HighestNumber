#include "HighestNumberCombination.hpp"

// #include <string>
// #include <chrono>
// #include <iostream>

using namespace std;

uint8_t HighestNumberCombination::uintLen(uint64_t num){
  uint8_t len = 0;

  // auto start = chrono::high_resolution_clock::now();
  // len = to_string(num).length();

  do{
     ++len;
     num /= 10;
  }while(num);

  // auto runtime = chrono::high_resolution_clock::now() - start;
  // uint64_t runtime_us = chrono::duration_cast<std::chrono::microseconds>(runtime).count();
  // cout<<runtime_us<<endl;

  return len;
}
