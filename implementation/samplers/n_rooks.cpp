#include "../../header/samplers/n_rooks.hpp"

n_rooks::n_rooks(const int num_samples, const int m)
	: sampler(num_samples, m) {
	generate_samples();
}

n_rooks::n_rooks(const n_rooks& nr)			
	: sampler(nr) {
	generate_samples();
}

n_rooks& 
n_rooks::operator= (const n_rooks& rhs) {
	if (this == &rhs)
		return (*this);
		
	sampler::operator=(rhs);
	return (*this);
}

n_rooks*	n_rooks::clone() const {
	return (new n_rooks(*this));
}

n_rooks::~n_rooks() 
{}

void n_rooks::generate_samples() {	
	for (int p = 0; p < num_sets; p++)          			
		for (int j = 0; j < num_samples; j++) {
			point_2D sp((j + rand_float()) / num_samples, (j + rand_float()) / num_samples);
			samples.push_back(sp);
		}		

	shuffle_x_coordinates();
	shuffle_y_coordinates();
}
