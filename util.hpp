#ifndef UTIL_HPP
#define UTIL_HPP
#define INF 1e18

typedef unsigned char int8;

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

struct px{
	double R, G, B; //intensity of each color in interval [0, 1]
    static const unsigned short int BITS_RED_CHANNEL = 8, BITS_GREEN_CHANNEL = 8, BITS_BLUE_CHANNEL = 8;

	px(){ R = G = B = 1; } //Cor Padrão(Branca)
	px(double r, double g, double b): R(r), G(g), B(b){}

    unsigned int convert_red(){ return R*((1<<BITS_RED_CHANNEL)-1); }
    unsigned int convert_green(){ return G*((1<<BITS_GREEN_CHANNEL)-1); }
    unsigned int convert_blue(){ return B*((1<<BITS_BLUE_CHANNEL)-1); }
    static px convert_rgb(int r, int g, int b){
        return px(1.0*r/((1<<BITS_RED_CHANNEL)-1), 1.0*g/((1<<BITS_GREEN_CHANNEL)-1), 1.0*b/((1<<BITS_BLUE_CHANNEL)-1));
    }
};
#endif
