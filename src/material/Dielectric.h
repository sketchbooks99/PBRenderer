#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "../core/Material.h"

class Dielectric : public Material {
    public:
        Dielectric(double ri) : ref_idx(ri) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered
        ) const {
            attenuation = vec3(1.0, 1.0, 1.0);
            double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

            vec3 unit_direction = unit_vector(r_in.direction());
            double cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
            if(etai_over_etat * sin_theta > 1.0) {
                vec3 reflected = reflect(unit_direction, rec.normal);
                scattered = Ray(rec.p, reflected);
                return true;
            }
            double reflect_prob = schlick(cos_theta, etai_over_etat);
            if(random_double() < reflect_prob) {
                vec3 reflected = reflect(unit_direction, rec.normal);
                scattered = Ray(rec.p, reflected);
                return true;
            }
            vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
            scattered = Ray(rec.p, refracted);
            return true;
        }

    public:
        double ref_idx;
};

#endif