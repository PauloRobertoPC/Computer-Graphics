#ifndef BRDF_HPP
#define BRDF_HPP

#include <math.h>

#include "../samplers/sampler.hpp"
#include "../utils/px.hpp"
#include "../utils/hit_info.hpp"
#include "../utils/vp.hpp"

class brdf {
public:

    brdf() = default;

    virtual ~brdf();

    brdf(const brdf& b);

    brdf(brdf&& b) noexcept;

    brdf& operator=(const brdf& b);

    brdf& operator=(brdf&& b) noexcept;

    virtual brdf* clone() const = 0;

    void set_sampler(sampler* sPtr);

    virtual px f(const hit_info& sr, const vp& wo, const vp& wi) const;

    virtual px sample_f(const hit_info& sr, const vp& wo, vp& wi) const;

    virtual px sample_f(const hit_info& sr, const vp& wo, vp& wi, float& pdf) const;

    virtual px rho(const hit_info& sr, const vp& wo) const;

protected:

    sampler* sampler_ptr = nullptr;  // for indirect illumination
};

#endif
