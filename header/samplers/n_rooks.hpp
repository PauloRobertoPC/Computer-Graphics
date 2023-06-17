#pragma once

#include "sampler.hpp"

class n_rooks: public sampler {
public:
	n_rooks(const int num_samples = 1, const int m = 50);	
	n_rooks(const n_rooks& nr);					
	n_rooks& operator= (const n_rooks& rhs);				
	virtual n_rooks*	clone() const;			
	virtual ~n_rooks();
		
private:		
	virtual void generate_samples(void);						
};
