#include "../../header/samplers/jittered.hpp"
#include <stdio.h>

jittered::jittered(int samples, int sets) :
    sampler(samples, sets) {
    generate_samples();
}

sampler* jittered::clone() const{
    return (new jittered(*this));
}

void jittered::generate_samples(){
    printf("Gerou jittered.\n");
    int n = (int) sqrt(num_samples);
    for(int p = 0; p < num_sets; p++){

        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                point_2D sp( (k + rand_float())/n,
                            (j + rand_float())/n );
                samples.push_back(sp);
            }
        }
    }
}
