#include "HighestNumberCombination.hpp"

// #include <chrono>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_LEN 19

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

bool HighestNumberCombination::cmp(const uint64_t &a, const uint64_t &b)
{
  // return true if a < b.
  uint64_t ab = pow10_64[uintLen(a)]+b;
  uint64_t ba = pow10_64[uintLen(b)]+a;

  return ab<ba;
}

void HighestNumberCombination::prepareRadixSort(vector<uint64_t> &data)
{
  // cout<<data[0]<<" ";

  uint64_t num;
  uint64_t numLen;
  for(uint64_t &n : data){
    num = n;
    numLen = uintLen(n);
    n = 0;
    int8_t remLen = MAX_LEN;
    while(remLen > 0){
      remLen -= numLen;
      if(remLen >= 0){
        n += num * pow10_64[remLen];
      }else{
        n += num / pow10_64[-remLen];
      }
    }
  }

  // cout<<data[0]<<endl;
}

string HighestNumberCombination::combine(const uint64_t numbers[], uint64_t len)
{
  string result = "";
  vector<uint64_t> data(numbers, numbers+len);

  prepareRadixSort(data);

  // TODO: use radix sort or std::sort depending on the size of the array.
  // sort(data.begin(), data.end(), cmp);

  for(uint64_t i = 0; i < data.size(); ++i){
    result += to_string(data[data.size()-i-1]);
  }
  return result;
}
