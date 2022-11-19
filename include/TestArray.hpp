#ifndef TEST_ARRAY_HPP
#define TEST_ARRAY_HPP

#include <cstdint>
#include <random>

enum DebugLevel{
  silent = 0,
  verbose = 1,
  debug = 2
};

class TestArray{
private:
  DebugLevel debugLevel_ = silent;

  uint64_t *array_ = nullptr;
  uint64_t len_ = 100;

  std::random_device rd_;
  std::mt19937 rng_;

  void generateArray();
  void convertCharArrayToIntArray(uint64_t len, char *charArray[], uint64_t *intArray);

public:
  TestArray();
  TestArray(uint64_t len);
  TestArray(uint64_t len, char *array[]);
  TestArray(std::vector<std::uint64_t> values);

  ~TestArray();

  void setDebugLevel(DebugLevel debugLevel);

  uint64_t *getArray();
  uint64_t len() {return len_;};

  void printArray();
};

#endif // TEST_ARRAY_HPP
