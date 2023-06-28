#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "brdf.hpp"

class lambertian : public brdf {
public:

    lambertian() = default;

    ~lambertian() = default;

    lambertian(const lambertian& l);

    lambertian(lambertian&& l) noexcept;

    lambertian& operator=(const lambertian& l);

    lambertian& operator=(lambertian&& l) noexcept;

    lambertian* clone() const override;

    px f(const hit_info& sr, const vp& wo, const vp& wi) const override;

    px sample_f(const hit_info& sr, const vp& wo, vp& wi, float& pdf) const override;

    px rho(const hit_info& sr, const vp& wo) const override;

    void set_ka(const float ka);

    void set_kd(const float kd);

    void set_cd(const px& c);

    void set_cd(const float r, const float g, const float b);

    void set_cd(const float c);

private:

    float kd = 0.0f;
    px cd = px(0, 0, 0);
};

inline void lambertian::set_ka(const float k) { kd = k; }

inline void lambertian::set_kd(const float k) { kd = k; }

inline void lambertian::set_cd(const px& c) { cd = c; }

inline void lambertian::set_cd(const float r, const float g, const float b) {
    cd.set_r(r);
    cd.set_g(g);
    cd.set_b(b);
}

inline void lambertian::set_cd(const float c) {
    cd.set_r(c);
    cd.set_g(c);
    cd.set_b(c);
}

#endif
