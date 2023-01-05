#include <algorithm>
#include <cmath>
#include "./Vector.h"

float vecDistance(Vector2 to, Vector2 from) {
  return sqrtf(
    powf(from.x - to.x, 2) +
    powf(from.y - to.y, 2)
  );
}

float angleFrom(Vector2 to, Vector2 from) {
  return std::atan2(to.x - from.x, to.y - from.y);
}