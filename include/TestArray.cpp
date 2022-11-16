#include <cstdlib>
#include <string>
#include <iostream>
#include "TestArray.hpp"

#include "HighestNumberCombination.hpp"

using namespace std;

const uint64_t pow10[20] = {
  1,
  10,
  100,
  1000,
  10000,
  100000,
  1000000,
  10000000,
  100000000,
  1000000000,
  10000000000,
  100000000000,
  1000000000000,
  10000000000000,
  100000000000000,
  1000000000000000,
  10000000000000000,
  100000000000000000,
  1000000000000000000,
  UINT64_MAX
};

void TestArray::setDebugLevel(DebugLevel debugLevel)
{
  debugLevel_ = debugLevel;
}

TestArray::TestArray()
{
  array_ = new uint32_t[len_];
  rng_.seed(rd_());
  generateArray();
}

TestArray::TestArray(uint32_t len)
  :len_{len}
{
  array_ = new uint32_t[len_];
  rng_.seed(rd_());
  generateArray();
}

TestArray::TestArray(uint32_t len, char *array[])
  :len_{len}
{
  array_ = new uint32_t[len];
  rng_.seed(rd_());
  convertCharArrayToIntArray(len_, array, array_);
}

TestArray::TestArray(std::vector<uint32_t> values)
  :len_{(uint32_t)values.size()}
{
  array_ = new uint32_t[len_];
  rng_.seed(rd_());
  for(uint32_t i = 0; i < len_; i++){
    array_[i] = values[i];
  }
}


TestArray::~TestArray()
{
  if(array_){
    free(array_);
  }
}

void TestArray::generateArray()
{
  // Add variety to the number length, since that's the tricky part.
  uint8_t maxLen = 19;
  uniform_int_distribution<uint32_t> lenDist(1, maxLen);

  for(uint32_t i = 0; i < len_; i++){
    uniform_int_distribution<uint32_t> valDist(0, pow10[lenDist(rng_)]);
    array_[i] = valDist(rng_);
  }
}

void TestArray::convertCharArrayToIntArray(uint32_t len, char *charArray[],
                                           uint32_t *intArray)
{
  for(uint32_t i = 0; i < len; i++){
    intArray[i] = stoi(charArray[i]);
  }
}

const uint32_t *TestArray::getArray()
{
  return array_;
}

void TestArray::printArray()
{
  for(uint32_t i = 0; i < len_; i++){
    cout<<array_[i]<<" ";
  }
  cout<<endl;
}
