#include "HighestNumberCombination.hpp"

#include <iostream>
#include <algorithm>
#include <cstring>
#include <bit>

using namespace std;

// We expect numbers with length of up to 9. Experiments have shown that we can
// get away with length*2-2 for the radix sort.
#define MAX_LEN (16)

// Corresponds to a 32kb counting array.
#define MAX_BASE_BITS (22)

// The number of elements at which radix sort becomes more effective than std::sort.
// The value was determined experimentally.
#define N_AT_EQUAL_RUNTIME (18)

int8_t HighestNumberCombination::log2_64(uint64_t n)
{
  // For values >=1 this gives the same result as ceil(log2(n)), but depending
  // on compiler optimization may result in greater performance because
  // counting leading zeroes is part of many CPU's instruction sets.
  // This is also why we need C++20. Prior to that there was no standard way
  // to implement this in C++.
  return 64-countl_zero(n);
}

uint8_t HighestNumberCombination::uintLen(uint64_t num){
  uint8_t len = 0;

  // Divide by 10 until we reach 0.
  do{
     ++len;
     num /= 10;
  }while(num);

  return len;
}

bool HighestNumberCombination::cmp(const uint64_t &a, const uint64_t &b)
{
  // If ordering ab is smaller than ba, a is sorted before b.
  uint64_t ab = a*pow10_64[uintLen(b)]+b;
  uint64_t ba = b*pow10_64[uintLen(a)]+a;

  return ab<ba;
}

void HighestNumberCombination::prepareRadixSort(uint64_t **data, const uint64_t numbers[], uint64_t len, uint8_t maxValLen)
{
  uint64_t numLen;

  // Create for each number to be sorted a key/value pair, where key contains
  // the value repeating itself until maxValLen digits are filled.
  // And the value is the unmodified number.
  for(uint64_t i = 0; i < len; ++i){
    data[i][1] = numbers[i];
    numLen = uintLen(numbers[i]);
    int8_t remLen = maxValLen;
    // Filling up the key left to right.
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

void HighestNumberCombination::countSort(uint64_t **data, uint64_t **sorted, uint64_t len, uint64_t *count, const uint64_t baseBits, const uint64_t base)
{
  // When applying this mask to a number, we get the value of the least
  // significant digit in the base we're using for sorting.
  uint64_t mask = ~((uint64_t)0xFFFFFFFFFFFFFFFF << baseBits);

  // Counting the number of times we encounter each digit of the base.
  for(uint64_t i = 0; i < len; ++i){
    count[data[i][0]&mask] += 1;
  }

  // Converting digit count to the position
  for(uint64_t i = 1; i < base; ++i){
    count[i] += count[i-1];
  }

  uint64_t val;
  uint64_t pos;
  // We have to insert the numbers backwards, so we start at index len-1.
  // When i falls below 0 it will loop around to UINT64_MAX, which is always
  // not smaller than len, so we will always exit the loop after
  // len steps.
  for(uint64_t i = len-1; i < len; --i){
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
}


uint64_t** HighestNumberCombination::radixSort(uint64_t **data, uint64_t **buffer, uint64_t len, const uint16_t baseBits, const uint16_t maxValBits)
{
  // Need the actual base to determine the length of the counting array.
  uint64_t base = (uint64_t)1 << baseBits;
  // Need the counting array to be initialized with 0's. But since we can't
  // initialize a variable length array, using calloc instead.
  uint64_t *count = (uint64_t*)calloc(base, sizeof(uint64_t));
  // Pointer to help swap data and buffer pointers.
  uint64_t **tmp;

  for(int16_t remainingBits = maxValBits; remainingBits > 0; remainingBits-=baseBits){
    countSort(data, buffer, len, count, baseBits, base);

    memset(count, 0, base*sizeof(uint64_t));

    // Swap pointers to avoid copying the entire vectors.
    tmp = data;
    data = buffer;
    buffer = tmp;
  }

  // Free the allocated memory.
  free(count);

  // The loop swapped buffer and data in the last run, so we return data, not buffer.
  return data;
}

string HighestNumberCombination::combine(uint64_t numbers[], uint64_t len)
{
  string result = "";

  // Radix sort outperforms comparison based algorithms at larger input sizes.
  // Hence we will use both, and switch over between them at a point where the
  // runtime would have been equal.
  if(len > N_AT_EQUAL_RUNTIME){
    // Can't use radix sort directly on the numbers array because we need
    // to modify the numbers, but need to keep the original ones for the result.
    // Use calloc instead of [] to prevent a segfault from stack overflow on
    // large input arrays.
    uint64_t **data = (uint64_t**)calloc(len, sizeof(uint64_t*));
    // Additional array to store partially sorted data after count sort.
    uint64_t **buf = (uint64_t**)calloc(len, sizeof(uint64_t*));
    // Allocating memory for the actual data. Only need to do it once for the
    // data array, and the rest of the operation will work by swapping pointers
    // with buf.
    for(uint64_t i = 0; i < len; ++i){
      data[i] = (uint64_t*)calloc(2, sizeof(uint64_t));
    }

    // Determine the best parameters for radix sort.

    // Find the highest number in the array.
    uint64_t maxVal = *max_element(numbers, numbers+len);
    // Calculate the length to which to extend the numbers for radix sort to
    // work for this problem.
    uint8_t maxValLen = (uintLen(maxVal) << 1) - 2;
    // Previous formula will produce 0 when maxVal is single digit.
    // But length must be at least 1 for the sort to work on array of single
    // digit numbers.
    maxValLen = maxValLen > 0 ? maxValLen : 1;
    // Calculate the number of bits required to hold the value.
    uint16_t maxValBits = (uint16_t)log2_64(pow10_64[maxValLen]);

    // The higher the base, the fewer passes the algorithm will need to sort
    // the data. But the memory usage grows exponentially with each additional
    // bit, so we'll keep it as high as possible without making it much
    // bigger than the input array, and giving it a sensible upper limit.
    uint16_t lenBits = (uint16_t)log2_64(len);
    uint16_t baseBits = lenBits < MAX_BASE_BITS ? lenBits : MAX_BASE_BITS;

    // Populate the data array with the numbers that have to be sorted.
    prepareRadixSort(data, numbers, len, maxValLen);
    // Perform radix sort on the data array.
    data = radixSort(data, buf, len, baseBits, maxValBits);

    // Put the sorted data into a string that represents the number we're
    // looking for.
    for(uint64_t i = 0; i < len; ++i){
      result += to_string(data[len-i-1][1]);
    }

    // Free the previously allocated memory.
    for(uint64_t i = 0; i < len; ++i){
      free(data[i]);
    }
    free(data);
    free(buf);
  }else{
    // std::sort uses a comparison based algorithm that guarantees n log n
    // runtime since C++11. Hence there will be very little performance to gain
    // over the standard implementation, so we'll just use that.
    // Because we're not comparing the numbers directly, but rather which is
    // higher depending on how they are arranged, we need a custom compare
    // function cmp.
    sort(numbers, numbers+len, cmp);

    // Put the sorted data into a string that represents the number we're
    // looking for.
    // Because the representation of the result returned by radix sort is
    // different, this isn't actually duplicated code.
    for(uint64_t i = 0; i < len; ++i){
      result += to_string(numbers[len-i-1]);
    }
  }

  return result;
}
