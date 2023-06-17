#pragma once
#include "sampler.hpp"

class multi_jittered: public sampler {
public:
	multi_jittered(const int num_samples = 1, const int m = 50);
	multi_jittered(const multi_jittered& rhs);		
	multi_jittered& operator= (const multi_jittered& rhs);				
	virtual multi_jittered* clone() const;		
	virtual ~multi_jittered();								
		
private:
	virtual void generate_samples();		
};
