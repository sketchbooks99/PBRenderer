#ifndef METAL_H
#define METAL_H

#include "../core/Material.h"

class Metal : public Material {
    public:
        Metal(const vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered
        ) const  {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    public: 
        vec3 albedo;
        double fuzz;
};

#endif