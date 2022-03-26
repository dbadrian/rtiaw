#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "constant.h"
#include "hittable.h"

#include <memory>
#include <optional>
#include <vector>

using std::shared_ptr;// TODO: Really shared_ptr? uff...costly...
using std::make_shared;

namespace rtiaw {
class HittableList : public Hittable
{
public:
  HittableList() = default;
  HittableList(shared_ptr<Hittable> object) { add(object); }

  void clear() { objects.clear(); }
  void add(shared_ptr<Hittable> object) { objects.push_back(object); }

  virtual std::optional<HitRecord> hit(const Ray &r, FPType t_min, FPType t_max) const override;

private:
  std::vector<shared_ptr<Hittable>> objects;
};

std::optional<HitRecord> HittableList::hit(const Ray &r, FPType t_min, FPType t_max) const
{
  auto closest_so_far = t_max;

  HitRecord rec{ std::nullopt };
  HitRecord temp_rec{ std::nullopt };

  for (const auto &object : objects) {
    temp_rec = object->hit(r, t_min, closest_so_far);
    if (temp_rec) {
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }

  return rec;
}

}// namespace rtiaw

#endif// HITTABLE_LIST_H