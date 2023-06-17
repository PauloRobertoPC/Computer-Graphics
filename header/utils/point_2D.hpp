#pragma once

#include "matrix.hpp"
#include <math.h>

class point_2D {
public:
    double x, y;

    point_2D();
    point_2D(const double a);
    point_2D(const double a, const double b);
    point_2D(const point_2D &p);
    ~point_2D();

	point_2D& operator= (const point_2D& p);						// assignment operator	
	point_2D operator- (void) const;								// unary minus
	point_2D operator* (const double a) const;					// multiplication by a double on the right

	double d_squared(const point_2D& p) const;					// square of distance bertween two points
	double distance(const point_2D& p) const;					// distance bewteen two points
};

point_2D operator* (double a, const point_2D& p);
