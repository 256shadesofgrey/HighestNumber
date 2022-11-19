#include "HighestNumberCombination.hpp"

#include <iostream>
#include <algorithm>
#include <cstring>

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

void HighestNumberCombination::countSort(vector<vector<uint64_t>> &data, vector<vector<uint64_t>> &sorted, const uint64_t baseBits)
{
  uint64_t base = (uint64_t)1 << baseBits;
  uint64_t count[base];
  memset(count, 0, base*sizeof(uint64_t));
  uint64_t mask = ~((uint64_t)0xFFFFFFFFFFFFFFFF << baseBits);

  // Counting the number of times we encounter each digit of the base.
  for(vector<uint64_t> num : data){
    count[num[0]&mask] += 1;
  }

  // Converting digit count to the position
  for(uint64_t i = 1; i < base; ++i){
    count[i] += count[i-1];
  }

  uint64_t val;
  // We have to insert the numbers backwards, so we start at index data.size()-1.
  // When i falls below 0 it will loop around to UINT64_MAX, which is always
  // not smaller than data.size(), so we will always exit the loop after
  // data.size() steps.
  for(uint64_t i = data.size()-1; i < data.size(); --i){
    val = data[i][0] & mask;
    sorted[count[val]] = data[i];

    // Shifting the bits here in preparation for the next digit to avoid
    // having to do another loop just for that.
    sorted[count[val]][0] >>= baseBits;

    // Decrement counter so that the next entry with the same value at
    // this digit is stored correctly.
    --count[val];
  }
}


vector<vector<uint64_t>>* HighestNumberCombination::radixSort(vector<vector<uint64_t>> *data, vector<vector<uint64_t>> *buffer)
{
  // TODO: implement calculation of optimal base.
  const uint16_t baseBits = 8;
  vector<vector<uint64_t>> *tmp;

  for(int16_t remainingBits = 64; remainingBits > 0; remainingBits-=baseBits){
    countSort(*data, *buffer, baseBits);

    // Swap pointers to avoid copying the entire vectors.
    tmp = data;
    data = buffer;
    buffer = tmp;
  }

  // The loop swapped buffer and data in the last run, so we return data, not buffer.
  return data;
}

string HighestNumberCombination::combine(const uint64_t numbers[], uint64_t len)
{
  string result = "";
  vector<vector<uint64_t>> data(len, vector<uint64_t>(2));
  vector<vector<uint64_t>> buf(len, vector<uint64_t>(2));
  vector<vector<uint64_t>> *sorted;

  prepareRadixSort(data, numbers, len);
  sorted = radixSort(&data, &buf);

  // TODO: use radix sort or std::sort depending on the size of the array.
  // sort(data.begin(), data.end(), cmp);
  // sorted = &data;

  for(uint64_t i = 0; i < (*sorted).size(); ++i){
    result += to_string((*sorted)[(*sorted).size()-i-1][1]);
  }
  return result;
}
