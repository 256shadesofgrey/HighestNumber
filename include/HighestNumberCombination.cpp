#include "HighestNumberCombination.hpp"

#include <iostream>
#include <algorithm>

using namespace std;

// We expect numbers with length of up to 9. Experiments have shown that we can
// get away with length*2-2 for the radix sort.
#define MAX_LEN 16

uint8_t HighestNumberCombination::uintLen(uint64_t num){
  uint8_t len = 0;

  do{
     ++len;
     num /= 10;
  }while(num);

  return len;
}

bool HighestNumberCombination::cmp(const uint64_t &a, const uint64_t &b)
{
  // return true if a < b.
  volatile uint64_t lena = uintLen(a);
  volatile uint64_t lenb = uintLen(b);
  uint64_t ab = a*pow10_64[uintLen(b)]+b;
  uint64_t ba = b*pow10_64[uintLen(a)]+a;

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
  uint64_t *count = (uint64_t*)calloc(base, sizeof(uint64_t));
  uint64_t mask = ~((uint64_t)0xFFFFFFFFFFFFFFFF << baseBits);

  // Counting the number of times we encounter each digit of the base.
  for(const vector<uint64_t> &num : data){
    count[num[0]&mask] += 1;
  }

  // Converting digit count to the position
  for(uint64_t i = 1; i < base; ++i){
    count[i] += count[i-1];
  }

  uint64_t val;
  uint64_t pos;
  // We have to insert the numbers backwards, so we start at index data.size()-1.
  // When i falls below 0 it will loop around to UINT64_MAX, which is always
  // not smaller than data.size(), so we will always exit the loop after
  // data.size() steps.
  for(uint64_t i = data.size()-1; i < data.size(); --i){
    val = data[i][0] & mask;
    pos = count[val]-1;
    sorted[pos] = data[i];

    // Shifting the bits here in preparation for the next digit to avoid
    // having to do another loop just for that.
    sorted[pos][0] >>= baseBits;

    // Decrement counter so that the next entry with the same value at
    // this digit is stored correctly.
    --count[val];
  }

  free(count);
}


vector<vector<uint64_t>>* HighestNumberCombination::radixSort(vector<vector<uint64_t>> *data, vector<vector<uint64_t>> *buffer)
{
  // TODO: implement calculation of optimal base.
  const uint16_t baseBits = 22;
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

  if(len > 10000000){
    vector<vector<uint64_t>> *sorted;
    vector<vector<uint64_t>> data(len, vector<uint64_t>(2));
    vector<vector<uint64_t>> buf(len, vector<uint64_t>(2));
    prepareRadixSort(data, numbers, len);
    sorted = radixSort(&data, &buf);

    for(uint64_t i = 0; i < (*sorted).size(); ++i){
      result += to_string((*sorted)[(*sorted).size()-i-1][1]);
    }
  }else{
    vector<uint64_t> data(numbers, numbers+len);
    sort(data.begin(), data.end(), cmp);

    for(uint64_t i = 0; i < data.size(); ++i){
      result += to_string(data[data.size()-i-1]);
    }
  }

  return result;
}
