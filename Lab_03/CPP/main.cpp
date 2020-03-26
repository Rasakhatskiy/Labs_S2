#include "../Include/Point.hpp"
#include <iostream>

int main()
{
	Point3D p1(1, 2, 3);
	Point3D p2(1, 2, 4);
	Point3D p3(1, 3, 4);
	Point3D p4(1, 3, 5);

	std::cout << (p1 < p2) << std::endl;
	std::cout << (p2 < p1) << std::endl;
	std::cout << (p2 <= p4) << std::endl;

	p1 = p2;
	p2 = p3;
}