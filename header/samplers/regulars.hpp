#pragma once

#include "sampler.hpp"

class regulars : public sampler{
public:
    regulars(int samples = 1, int sets = 50);
    virtual sampler* clone() const;
    virtual void generate_samples();
};
