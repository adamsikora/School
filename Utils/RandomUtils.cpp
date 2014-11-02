#include "RandomUtils.h"

namespace utils {
namespace random {

std::mt19937_64 mersenneTwister;

bool decide(double rate) {
  return mersenneTwister() < rate*std::numeric_limits<uint64_t>::max();
}

}
}