#pragma once

#include "sampler.hpp"

class regular : public sampler{
public:
    regular(int samples = 1, int sets = 50);
    virtual sampler* clone() const;
    virtual void generate_samples();
};
