#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

class viewport{
    private:
        double h, w, d; //heigth, point in z-axis
    
    public:
        viewport();
        viewport(double h, double w, double d);

        //Getters and Setters
        double get_h();
        void set_h(double h);
        double get_w();
        void set_w(double w);
        double get_d();
        void set_d(double d);
};

#endif
