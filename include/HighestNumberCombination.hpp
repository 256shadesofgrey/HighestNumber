#ifndef HIGHEST_NUMBER_COMBINATION_HPP
#define HIGHEST_NUMBER_COMBINATION_HPP

#include <cstdint>
#include <string>
#include <vector>

class HighestNumberCombination{
private:
  static int8_t log2_64(uint64_t n);
  static bool cmp(const uint64_t &a, const uint64_t &b);
  static void prepareRadixSort(uint64_t **data, const uint64_t numbers[], uint64_t len, uint8_t maxValLen);
  static void countSort(uint64_t **data, uint64_t **sorted, uint64_t len, uint64_t *count, const uint64_t baseBits, const uint64_t base);
  static uint64_t** radixSort(uint64_t **data, uint64_t **buffer, uint64_t len, const uint16_t baseBits, const uint16_t maxValBits);

public:
  constexpr static const uint64_t pow10_64[20] = {
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

  constexpr static const uint32_t pow10_32[11] = {
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
    UINT32_MAX
  };

  static uint8_t uintLen(uint64_t num);

  static std::string combine(uint64_t numbers[], uint64_t len);
};

#endif // HIGHEST_NUMBER_COMBINATION_HPP
