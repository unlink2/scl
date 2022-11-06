#include "scl/sclrand.h"

static u32 seed_;

void scl_seed_rand(u32 seed) {
  if (seed != 0) {
    seed_ = seed;
  }
}

u32 scl_next_rand() {
  u32 seed = (seed_ << 13) ^ seed_; // NOLINT
  seed_++;
  return ((seed * (seed * seed * 15731 + 789221) + 1376312589) & // NOLINT
          0x7fffffff);                                           // NOLINT
}
