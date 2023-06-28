#include "../../header/brdfs/brdf.hpp"
#include "../../header/utils/px.hpp"
#include <utility>

brdf::~brdf() {
    if (sampler_ptr != nullptr) {
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }
}

brdf::brdf(const brdf& b) { sampler_ptr = b.sampler_ptr->clone(); }

brdf::brdf(brdf&& b) noexcept : sampler_ptr(std::exchange(b.sampler_ptr, nullptr)) {}

brdf& brdf::operator=(const brdf& b) {
    if (sampler_ptr) {
        delete sampler_ptr;
    }
    sampler_ptr = b.sampler_ptr->clone();

    return *this;
}

brdf& brdf::operator=(brdf&& b) noexcept {
    if (sampler_ptr) {
        delete sampler_ptr;
    }
    sampler_ptr = b.sampler_ptr;
    b.sampler_ptr = nullptr;

    return *this;
}

void brdf::set_sampler(sampler* sPtr) {
    sampler_ptr = sPtr;
    sampler_ptr->map_samples_to_hemisphere(1);  // for perfect diffuse
}

px brdf::f([[maybe_unused]] const hit_info& sr, [[maybe_unused]] const vp& wo, [[maybe_unused]] const vp& wi) const { return px(0, 0, 0); }

px brdf::sample_f([[maybe_unused]] const hit_info& sr, [[maybe_unused]] const vp& wo, [[maybe_unused]] vp& wi) const { return px(0, 0, 0); }

px brdf::sample_f([[maybe_unused]] const hit_info& sr, [[maybe_unused]] const vp& wo, [[maybe_unused]] vp& wi, [[maybe_unused]] float& pdf) const { return px(0, 0, 0); }

px brdf::rho([[maybe_unused]] const hit_info& sr, [[maybe_unused]] const vp& wo) const { return px(0, 0, 0); }
