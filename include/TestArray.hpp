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

  uint32_t *array_ = nullptr;
  uint32_t len_ = 100;

  std::random_device rd_;
  std::mt19937 rng_;

  void generateArray();
  void convertCharArrayToIntArray(uint32_t len, char *charArray[], uint32_t *intArray);

public:
  TestArray();
  TestArray(uint32_t len);
  TestArray(uint32_t len, char *array[]);
  TestArray(std::vector<std::uint32_t> values);

  ~TestArray();

  void setDebugLevel(DebugLevel debugLevel);

  const uint32_t *getArray();
  uint32_t len() {return len_;};

  void printArray();
};

#endif // TEST_ARRAY_HPP
