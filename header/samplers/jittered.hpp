#pragma once

#include "sampler.hpp"

class jittered : public sampler{
public:
    jittered(int samples = 1, int sets = 50);
    virtual sampler* clone() const;
    virtual void generate_samples();
};
