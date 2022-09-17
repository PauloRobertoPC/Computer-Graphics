#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP

#include <iostream>

#define EPS 1e-8

//double comparator with latex-like syntax
class comparator{
    public:
        static bool eq(double a, double b){ // ==
            return (a+EPS > b) && (a-EPS < b);
        } 
    
        static bool g(double a, double b){ // >
            return a > b+EPS;
        }
    
        static bool l(double a, double b){ // <
            return a < b-EPS;
        }
    
        static bool geq(double a, double b){ // >=
            return !l(a, b);
        }
    
        static bool leq(double a, double b){ // <=
            return !g(a, b);
        }
    
        static bool neq(double a, double b){ // !=
            return !eq(a, b);
        }
};

#endif
