#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

struct viewport{
    double h, w, d; //altura, largura e distância do observador O
    
    viewport(){ h = w = d = 0; }
    viewport(double h, double w, double d) : h(h), w(w), d(d){}
};

#endif
