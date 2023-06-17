#include "../../header/samplers/multi_jittered.hpp"

multi_jittered::multi_jittered(const int num_samples, const int m)
	: sampler(num_samples, m) {
	generate_samples();
}

multi_jittered::multi_jittered(const multi_jittered& rhs)			
	: sampler(rhs) {
	generate_samples();
}

multi_jittered& multi_jittered::operator= (const multi_jittered& rhs) {
	if (this == &rhs) {		
		return (*this);
	}
	sampler::operator=(rhs);
	generate_samples();
	return (*this);
}

multi_jittered* multi_jittered::clone() const {
	return (new multi_jittered(*this));
}

multi_jittered::~multi_jittered() 
{}

void multi_jittered::generate_samples() {
	int n = (int)sqrt(num_samples);
	float subcell_width = 1.0 / ((float) num_samples);
	
	point_2D fill_point;
	for (int j = 0; j < num_samples * num_sets; j++)
		samples.push_back(fill_point);
			
	for (int p = 0; p < num_sets; p++) 
		for (int i = 0; i < n; i++)		
			for (int j = 0; j < n; j++) {
				samples[i * n + j + p * num_samples].x = (i * n + j) * subcell_width + rand_float()*subcell_width;
				samples[i * n + j + p * num_samples].y = (j * n + i) * subcell_width + rand_float()*subcell_width;
			}

	for (int p = 0; p < num_sets; p++) 
		for (int i = 0; i < n; i++)		
			for (int j = 0; j < n; j++) {
				int k = j + rand_int()%n;
				float t = samples[i * n + j + p * num_samples].x;
				samples[i * n + j + p * num_samples].x = samples[i * n + k + p * num_samples].x;
				samples[i * n + k + p * num_samples].x = t;
			}

	for (int p = 0; p < num_sets; p++)
		for (int i = 0; i < n; i++)		
			for (int j = 0; j < n; j++) {
				int k = j + rand_int()%n;
				float t = samples[j * n + i + p * num_samples].y;
				samples[j * n + i + p * num_samples].y = samples[k * n + i + p * num_samples].y;
				samples[k * n + i + p * num_samples].y = t;
		}
}
