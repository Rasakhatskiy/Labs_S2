#ifndef POINT_HPP
#define POINT_HPP

class Point3D
{
public:
	double X, Y, Z;

	Point3D(double x, double y, double z) : X{ x }, Y{ y }, Z{ z }{};
	Point3D() = default;
};
#endif //POINT_HPP
