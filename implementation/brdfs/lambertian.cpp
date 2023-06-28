#include "../../header/brdfs/lambertian.hpp"
#include "../../header//utils/constants.hpp"
#include <utility>

lambertian::lambertian(const lambertian& l) : brdf(l), kd(l.kd), cd(l.cd) {}

lambertian::lambertian(lambertian&& l) noexcept : brdf(std::move(l)), kd(std::exchange(l.kd, 0.0f)), cd(std::move(l.cd)) {}

lambertian& lambertian::operator=(const lambertian& l) {
    brdf::operator=(l);

    kd = l.kd;
    cd = l.cd;

    return *this;
}

lambertian& lambertian::operator=(lambertian&& l) noexcept {
    brdf::operator=(std::move(l));

    kd = std::exchange(l.kd, 0.0f);
    cd = std::move(l.cd);

    return *this;
}

lambertian* lambertian::clone() const { return new lambertian(*this); }

px lambertian::f([[maybe_unused]] const hit_info& sr, [[maybe_unused]] const vp& wo, [[maybe_unused]] const vp& wi) const { return px(cd) * (kd*invPI); }

// this generates a direction by sampling the hemisphere with a cosine distribution
// this is called in path_shade for any material with a diffuse shading component
// the samples have to be stored with a cosine distribution

px lambertian::sample_f(const hit_info& sr, const vp& wo, vp& wi, float& pdf) const {
    vp w(sr.normal);
    vp v = vp(0.0034f, 1.0f, 0.0071f) % w;
    v = !v;
    vp u = v % w;

    vp sp = sampler_ptr->sample_hemisphere();
    wi = u*sp.get_x() + v*sp.get_y() + w*sp.get_z();
    wi = !wi;

    pdf = invPI*(wi*sr.normal) ;

    return px(cd) * (invPI*kd);
}
 
px lambertian::rho([[maybe_unused]] const hit_info& sr, [[maybe_unused]] const vp& wo) const { return px(cd)*kd; }
