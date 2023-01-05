#ifndef VECTOR_H
#define VECTOR_H

struct Vector2 {
  float x;
  float y;
};

struct Vector3 {
  float x;
  float y;
  float z;
};

float vecDistance(Vector2, Vector2);
float angleFrom(Vector2, Vector2);

#endif