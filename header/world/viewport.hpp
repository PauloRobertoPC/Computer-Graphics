#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "../samplers/sampler.hpp"

class viewport{
    private:
        double dx, dy;
        double h, w, d; //heigth, point in z-axis
        sampler *sp;

    public:
        viewport();
        viewport(double h, double w, double d, sampler* sp);

        //Getters and Setters
        double get_h();
        void set_h(double h);
        double get_w();
        void set_w(double w);
        double get_d();
        void set_d(double d);
};

#endif
