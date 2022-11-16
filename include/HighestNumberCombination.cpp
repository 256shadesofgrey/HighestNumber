#include "HighestNumberCombination.hpp"

// #include <chrono>
// #include <iostream>
#include <algorithm>

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

bool HighestNumberCombination::cmp(const string &a, const string &b)
{
  // return true if a < b.
  string ab = a+b;
  string ba = b+a;

  bool result = false;

  if(ab.compare(ba) < 0){
    result = true;
  }

  return result;
}

vector<string> HighestNumberCombination::uintArrayToStrVector(const uint64_t uintArray[], uint64_t len)
{
  vector<string> result;

  for(uint64_t i = 0; i < len; ++i){
    result.push_back(to_string(uintArray[i]));
  }

  return result;
}

string HighestNumberCombination::combine(const uint64_t numbers[], uint64_t len)
{
  string result = "";
  vector<string> data = uintArrayToStrVector(numbers, len);

  // TODO: use radix sort or std::sort depending on the size of the array.
  sort(data.begin(), data.end(), cmp);

  for(int i = 0; i < data.size(); ++i){
    result = data[i]+result;
  }
  return result;
}
