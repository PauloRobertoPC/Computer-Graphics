#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "canvas.hpp"
#include "../utils/point_2D.hpp"
#include "../samplers/sampler.hpp"

class viewport{
    private:
        canvas &c;      //canvas used to calcula dx and dy
        double h, w, d; //heigth, width and point in z-axis
        double dx, dy;  // width and heigth of each pixel of canvas in real world
        sampler *sp;

        void change_dx_dy();

    public:
        viewport(double h, double w, double d, canvas &c, sampler* sp);

        int qnt_samples();
        point_2D sample_square();
    

        //Getters and Setters
        double get_h();
        void set_h(double h);
        double get_w();
        void set_w(double w);
        void set_wh(double w, double h);
        double get_d();
        void set_d(double d);
        double get_dx();
        double get_dy();
};

#endif
