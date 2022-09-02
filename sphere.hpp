#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <bits/stdc++.h>
#include "util.hpp"

using namespace std;

struct sphere{
    vp center; double radio, specular; px color;
     
    sphere(){}
    sphere(vp center, double r, double s, px color) : center(center), radio(r), specular(s), color(color){}
    sphere(double x, double y, double z, double r, double s, px color) : center(vp(x, y, z)), radio(r), specular(s), color(color){}

    //Calcula a interseção(se tiver) entre a esfera e o raio que sai de 'O' e tem direção 'D'
    tuple<double, double> intersection_with_ray(vp O, vp D){
        vp CO = O - this->center;
    
        double a = D*D;
        double b = 2*(CO*D);
        double c = CO*CO - this->radio*this->radio;
        double delta = b*b - 4*a*c;
        
        if(delta < 0) return {INF, INF};        //não há interseção entre a esfera e o raio
        double t1 = (-b + sqrt(delta))/(2*a);
        double t2 = (-b - sqrt(delta))/(2*a);

        return {t1, t2};
    }
};

#endif
