#include <cstdlib>
#include <string>
#include <iostream>
#include "TestArray.hpp"

#include "HighestNumberCombination.hpp"

using namespace std;

void TestArray::setDebugLevel(DebugLevel debugLevel)
{
  debugLevel_ = debugLevel;
}

TestArray::TestArray()
{
  array_ = new uint64_t[len_];
  rng_.seed(rd_());
  generateArray();
}

TestArray::TestArray(uint64_t len)
  :len_{len}
{
  array_ = new uint64_t[len_];
  rng_.seed(rd_());
  generateArray();
}

TestArray::TestArray(uint64_t len, char *array[])
  :len_{len}
{
  array_ = new uint64_t[len];
  rng_.seed(rd_());
  convertCharArrayToIntArray(len_, array, array_);
}

TestArray::TestArray(std::vector<uint64_t> values)
  :len_{(uint64_t)values.size()}
{
  array_ = new uint64_t[len_];
  rng_.seed(rd_());
  for(uint64_t i = 0; i < len_; i++){
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

  // Maximum length of a uint32_t number.
  uint8_t maxLen = 10;
  uniform_int_distribution<uint64_t> lenDist(1, maxLen);

  for(uint64_t i = 0; i < len_; i++){
    uniform_int_distribution<uint64_t> valDist(0, HighestNumberCombination::pow10_64[lenDist(rng_)]);
    array_[i] = valDist(rng_);
  }
}

void TestArray::convertCharArrayToIntArray(uint64_t len, char *charArray[],
                                           uint64_t *intArray)
{
  for(uint64_t i = 0; i < len; i++){
    intArray[i] = stoi(charArray[i]);
  }
}

const uint64_t *TestArray::getArray()
{
  return array_;
}

void TestArray::printArray()
{
  for(uint64_t i = 0; i < len_; i++){
    cout<<array_[i]<<" ";
  }
  cout<<endl;
}
