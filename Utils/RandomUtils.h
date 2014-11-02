#pragma once

#include "StlBase.h"

namespace utils {
namespace random {

const uint64_t maxUint64 = std::numeric_limits<uint64_t>::max();
const double maxDoubledUint64 = static_cast<double>(std::numeric_limits<uint64_t>::max());

class Generator {
public:
  Generator(uint64_t seed) : mersenneTwister_(seed) {}

  inline bool decide(double rate) { return mersenneTwister_() < maxUint64; }
  inline double get01() {
    return static_cast<double>(mersenneTwister_()) / maxDoubledUint64;
  }
  inline uint64_t getIntFrom0To(uint64_t aboveMax) { return mersenneTwister_() % aboveMax; } // doesnt preserve uniform distribution perfectly
  inline int64_t getIntInRange(int64_t min, int64_t aboveMax) { return min + mersenneTwister_() % (aboveMax - min); } // doesnt preserve uniform distribution perfectly

private:
  std::mt19937_64 mersenneTwister_;
};

bool decide(double rate);

}
}