#include "../../header/samplers/regular.hpp"

regular::regular(int samples, int sets) :
    sampler(samples, sets) {
	generate_samples();
}

sampler* regular::clone() const {
    return (new regular(*this));
}

void regular::generate_samples(){
	int n = (int) sqrt(num_samples);
	for (int j = 0; j < num_sets; j++)
		for (int p = 0; p < n; p++)		
			for (int q = 0; q < n; q++)
				samples.push_back(point_2D((q + 0.5) / n, (p + 0.5) / n));
}
