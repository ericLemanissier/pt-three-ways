#pragma once

#include "math/Hit.h"
#include "math/Ray.h"
#include "util/Material.h"

namespace oo {

class Primitive {
public:
  virtual ~Primitive() = default;
  struct IntersectionRecord {
    Hit hit;
    Material material;
  };

  [[nodiscard]] virtual bool
  intersect(const Ray &ray, IntersectionRecord &intersection) const = 0;
};

}