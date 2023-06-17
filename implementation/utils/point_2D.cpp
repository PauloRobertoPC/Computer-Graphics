#include "../../header/utils/point_2D.hpp"

point_2D::point_2D()
	:x(0), y(0)
{}

point_2D::point_2D(const double a)
	:x(a), y(a)
{}

point_2D::point_2D(const double a, const double b)
	:x(a), y(b)
{}

point_2D::point_2D(const point_2D& p)
	:x(p.x), y(p.y)
{}

point_2D::~point_2D() 
{}

point_2D& point_2D::operator= (const point_2D& rhs) {
	
	if (this == &rhs)
		return (*this);

	x = rhs.x; y = rhs.y; 

	return (*this);
}

// distance between two points
double point_2D::distance(const point_2D& p) const {
	return (sqrt(		(x - p.x) * (x - p.x) 
					+ 	(y - p.y) * (y - p.y)));
}

// unary minus
point_2D point_2D::operator- (void) const {
	return (point_2D(-x, -y));
}

// mutliplication by a double on the right
point_2D point_2D::operator* (const double a) const {
	return (point_2D(x * a,y * a));
}

// the square of the distance between the two points as a member function
double point_2D::d_squared(const point_2D& p) const {
	return (	(x - p.x) * (x - p.x) 
			+ 	(y - p.y) * (y - p.y) );
}

// multiplication by a double on the left
point_2D operator* (double a, const point_2D& p) {
	return (point_2D(a * p.x, a * p.y));
}
