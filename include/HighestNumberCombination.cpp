#include "HighestNumberCombination.hpp"

#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_LEN 19

uint8_t HighestNumberCombination::uintLen(uint64_t num){
  uint8_t len = 0;

  do{
     ++len;
     num /= 10;
  }while(num);

  return len;
}

bool HighestNumberCombination::cmp(const vector<uint64_t> &a, const vector<uint64_t> &b)
{
  // return true if a < b.
  uint64_t ab = pow10_64[uintLen(a[0])]+b[0];
  uint64_t ba = pow10_64[uintLen(b[0])]+a[0];

  return ab<ba;
}

void HighestNumberCombination::prepareRadixSort(vector<vector<uint64_t>> &data, const uint64_t numbers[], uint64_t len)
{
  uint64_t numLen;
  for(uint64_t i = 0; i < len; ++i){
    data[i][1] = numbers[i];
    numLen = uintLen(numbers[i]);
    int8_t remLen = MAX_LEN;
    while(remLen > 0){
      remLen -= numLen;
      if(remLen >= 0){
        data[i][0] += numbers[i] * pow10_64[remLen];
      }else{
        data[i][0] += numbers[i] / pow10_64[-remLen];
      }
    }
  }
}

string HighestNumberCombination::combine(const uint64_t numbers[], uint64_t len)
{
  string result = "";
  vector<vector<uint64_t>> data(len, vector<uint64_t>(2));

  prepareRadixSort(data, numbers, len);

  // TODO: use radix sort or std::sort depending on the size of the array.
  // sort(data.begin(), data.end(), cmp);

  for(uint64_t i = 0; i < data.size(); ++i){
    result += to_string(data[data.size()-i-1][1]);
  }
  return result;
}
