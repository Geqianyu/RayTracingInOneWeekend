
#include "HittableList.h"

HittableList::HittableList()
{

}

HittableList::HittableList(std::shared_ptr<Hittable> objectValue)
{
    add(objectValue);
}

HittableList::~HittableList()
{

}

void HittableList::clear()
{
    objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> objectValue)
{
    objects.push_back(objectValue);
}

bool HittableList::hit(const ray& r, double t_min, double t_max, Hit_record& rec) const
{
    Hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}