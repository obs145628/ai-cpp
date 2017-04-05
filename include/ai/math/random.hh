#pragma once

#include <array>
#include <cstddef>
#include <vector>

class Random
{
public:
  Random();
  Random(unsigned long s);

  ///Returns n \in [0, 4,294,967,295]
  unsigned long
  int32_get();

  ///Returns n \in [0, 2,147,483,648]
  long
  int31_get();

  ///Returns n \in [0, 2^64 - 1]
  uint64_t
  u64_get();


  bool
  bool_get();

  ///Returns n \in [0, 1[
  float
  float_get();

  ///Returns n \in [0, 1[
  double
  double_get();

  float
  float_get(float max);

  double
  double_get(double max);

  float
  float_get(float min, float max);

  double
  double_get(double min, double max);

private:
  static const int N = 624;
  static const int M = 397;
  static const unsigned long MATRIX_A = 0x9908b0dfUL;
  static const unsigned long UPPER_MASK = 0x80000000UL;
  static const unsigned long LOWER_MASK = 0x7fffffffUL;
  
  std::array<unsigned long, N> mt_;
  int mti_;
  std::array<unsigned long, 2> mag01_;
};
