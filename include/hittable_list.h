#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "constant.h"
#include "hittable.h"

#include <memory>
#include <optional>
#include <vector>

using std::unique_ptr; // TODO: Really unique_ptr? uff...costly...

namespace rtiaw {
class HittableList : public Hittable {
public:
  HittableList() = default;
  // explicit HittableList(unique_ptr<Hittable> object) { add(object); }
  explicit HittableList(unique_ptr<Hittable> object) { add(std::move(object)); }

  void clear() { objects.clear(); }
  // void add(unique_ptr<Hittable> object) { objects.push_back(object); }
  void add(unique_ptr<Hittable> object) {
    objects.emplace_back(std::move(object));
  }

  [[nodiscard]] virtual std::optional<HitRecord>
  hit(const Ray &r, FPType t_min, FPType t_max) const override; // NOLINT

private:
  std::vector<unique_ptr<Hittable>> objects;
};

std::optional<HitRecord> HittableList::hit(const Ray &r, FPType t_min,
                                           FPType t_max) const {

  auto closest_so_far = t_max;
  std::optional<HitRecord> closest_hit = std::nullopt;
  std::optional<HitRecord> temp_rec = std::nullopt;

  for (const auto &object : objects) {
    temp_rec = object->hit(r, t_min, closest_so_far);
    if (temp_rec) {
      closest_so_far = temp_rec->t;
      closest_hit = temp_rec;
    }
  }

  return closest_hit;
}

} // namespace rtiaw

#endif // HITTABLE_LIST_H