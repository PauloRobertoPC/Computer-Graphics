#ifndef PX_HPP
#define PX_HPP

typedef unsigned char int8;

class px{
    private: 
	    double r, g, b; //intensity of each color in interval [0, 1]
        static const unsigned int BITS_RED_CHANNEL = 8, BITS_GREEN_CHANNEL = 8, BITS_BLUE_CHANNEL = 8;

    public:
	    px();
	    px(double r, double g, double b);

        px operator*(double alp);
        
        unsigned int convert_red();
        unsigned int convert_green();
        unsigned int convert_blue();
        static px convert_rgb(int r, int g, int b){
            return px(1.0*r/((1<<BITS_RED_CHANNEL)-1), 1.0*g/((1<<BITS_GREEN_CHANNEL)-1), 1.0*b/((1<<BITS_BLUE_CHANNEL)-1));
        }
    
        //Getters and Setters
        double get_r();
        void set_r(double r);
        double get_g();
        void set_g(double g);
        double get_b();
        void set_b(double b);
};

#endif
