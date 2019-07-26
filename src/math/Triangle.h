#pragma once

#include "Hit.h"
#include "Ray.h"
#include "Vec3.h"

#include <array>
#include <optional>

// TODO: consider moving this and sphere and ray into "oo" and then take their
// implementations out as static methods? Then can do proper functional stuff?
// Will make SoA/AoS easier as can separate vtx from normal

class Triangle {
public:
  using Vertices = std::array<Vec3, 3>;
  using Normals = std::array<Vec3, 3>;

private:
  Vertices vertices_;
  Normals normals_;

public:
  explicit Triangle(const Vertices &vertices);
  Triangle(const Vertices &vertices, const Normals &normals)
      : vertices_(vertices), normals_(normals) {}
  Triangle(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2)
      : Triangle(Vertices{v0, v1, v2}) {}

  [[nodiscard]] constexpr const Vec3 &vertex(int index) const {
    return vertices_[index];
  }

  [[nodiscard]] constexpr const Vec3 &normal(int index) const {
    return normals_[index];
  }

  [[nodiscard]] constexpr Vec3 uVector() const {
    return vertices_[1] - vertices_[0];
  }

  [[nodiscard]] constexpr Vec3 vVector() const {
    return vertices_[2] - vertices_[0];
  }

  [[nodiscard]] constexpr Vec3 faceNormal() const {
    return uVector().cross(vVector()).normalised();
  }
  [[nodiscard]] std::optional<Hit> intersect(const Ray &ray) const noexcept;
};