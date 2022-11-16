#ifndef HIGHEST_NUMBER_COMBINATION_HPP
#define HIGHEST_NUMBER_COMBINATION_HPP

#include <cstdint>
#include <string>
#include <vector>

class HighestNumberCombination{
private:
  static bool cmp(const std::string &a, const std::string &b);
  static std::vector<std::string> uintArrayToStrVector(const uint64_t uintArray[], uint64_t len);

public:
  static uint8_t uintLen(uint64_t num);

  static std::string combine(const uint64_t numbers[], uint64_t len);
};

#endif // HIGHEST_NUMBER_COMBINATION_HPP
