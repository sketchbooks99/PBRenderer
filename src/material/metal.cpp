#include "metal.h"
#include "../core/bsdf.h"

namespace mypt {

bool Metal::scatter(
    const Ray& r_in, SurfaceInteraction& si
) const {
    vec3 reflected = reflect(normalize(r_in.direction()), si.n);
    si.scattered = Ray(si.p, reflected+fuzz*random_in_unit_sphere(), r_in.time());
    si.attenuation = albedo;
    si.is_specular = true;
    si.pdf_ptr = 0;

    return true;
}

}