#ifndef _GQY_HITTABLE_LIST_H_
#define _GQY_HITTABLE_LIST_H_

#include "Hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable
{
public:
    // ���к���
    HittableList();
    HittableList(std::shared_ptr<Hittable> objectValue);
    ~HittableList();

    void clear();
    void add(std::shared_ptr<Hittable> objectValue);

    virtual bool hit(const ray& r, double t_min, double t_max, Hit_record& rec) const override;

public:
    // ���б���
    std::vector<std::shared_ptr<Hittable>> objects;
};

#endif // !_GQY_HITTABLE_LIST_H_
