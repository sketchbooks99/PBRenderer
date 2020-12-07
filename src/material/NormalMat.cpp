#include "NormalMat.h"

bool NormalMat::scatter(
    const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered
) const {
    vec3 scatter_direction = rec.normal + random_unit_vector();
    scattered = Ray(rec.p, scatter_direction, r_in.time());
    attenuation = normalize(rec.normal);
    return true;
}