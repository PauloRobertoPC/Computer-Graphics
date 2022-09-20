#ifndef VP_HPP
#define VP_HPP
#define INF 1e18
// #define EPS 0.0000001

class vp{
    private:
        double x, y, z;   
    
    public:
        vp();
        vp(double x, double y, double z);

        vp operator+(vp v); //sum of vector/points
        vp operator-(vp v); //subtraction of vector/points       
        vp operator-(); //opposite vector 
        double operator*(vp v); //dot product
        vp operator*(double alp); //vector multiplicaton by a scalar
        vp operator/(double alp); //vector division by a scalar
        double operator~(); //vector module/size
        vp operator%(vp v); //cross product
        void print();
    
        //Getters and Setters
        double get_x();
        void set_x(double x);
        double get_y();
        void set_y(double y);
        double get_z();
        void set_z(double z);
};

#endif
