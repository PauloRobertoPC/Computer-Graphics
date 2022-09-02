#ifndef UTIL_HPP
#define UTIL_HPP
#define INF 1e18

typedef unsigned char int8;

struct px{
	int8 R, G, B;

	px(){ R = G = B = 255; } //Cor Padrão

	px(int8 r, int8 g, int8 b){
		R = r; G = g; B = b;
	}
};

struct vp{
    double x, y, z;   
    
    vp(double x, double y, double z) : x(x), y(y), z(z){}

    vp operator+(vp v){ //soma entre vetores
        return vp(this->x+v.x, this->y+v.y, this->z+v.z);
    }

    vp operator-(vp v){ //subtração entre vetores
        return vp(this->x-v.x, this->y-v.y, this->z-v.z);
    }
    
    vp operator*(double alp){ //multiplicação de vetor por um escalar
        return vp(this->x*alp, this->y*alp, this->z*alp);
    }
    
    double operator*(vp v){ //produto interno
        return this->x*v.x + this->y*v.y + this->z*v.z;
    }
};

#endif
