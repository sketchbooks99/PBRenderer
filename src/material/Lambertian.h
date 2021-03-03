#pragma once

#include "../core/Material.h"
#include "../core/Texture.h"
#include "../texture/ConstantTexture.h"

namespace mypt {

struct HitRecord;

class Lambertian final : public Material {
public: 
    explicit Lambertian(vec3 albedo) : albedo(std::make_shared<ConstantTexture>(albedo)) {}
    explicit Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}
    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) const override;
    Float scattering_pdf(const Ray& r_in, const HitRecord& rec, const Ray& scattered) const override;
    
    std::string to_string() const override {
        std::ostringstream oss;
        oss << "Lambertian : {" << std::endl;
        oss << "\tTexture : " << albedo->to_string() << "," << std::endl;
        oss << "}";
        return oss.str();
    }

    MatType type() const override { return MatType::Lambertian; }
private:
    std::shared_ptr<Texture> albedo;
};

}
