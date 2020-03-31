#ifndef POINT_HPP
#define POINT_HPP

class Point3D
{
public:
	double X, Y, Z;

	Point3D(double x, double y, double z) : X{ x }, Y{ y }, Z{ z }{};
	Point3D() = default;

	bool operator==(const Point3D& cmp) const
	{
		return 
			this->X == cmp.X &&
			this->Y == cmp.Y &&
			this->Z == cmp.Z;
	}

	bool operator!=(const Point3D& cmp) const
	{
		return !(*this == cmp);
	}

	bool operator< (const Point3D& cmp) const
	{
		if (this->X < cmp.X) 
			return true;
		else 
			if (this->X == cmp.X)
				if (this->Y < cmp.Y) 
					return true;
				else 
					if (this->Y == cmp.Y)
						if (this->Z < cmp.Z) 
							return true;
						else 
							return false;
					else 
					return false;
			else 
			return false;
	}

	bool operator> (const Point3D& cmp) const
	{
		if (this->X > cmp.X)
			return true;
		else
			if (this->X == cmp.X)
				if (this->Y > cmp.Y)
					return true;
				else
					if (this->Y == cmp.Y)
						if (this->Z > cmp.Z)
							return true;
						else
							return false;
					else
						return false;
			else
				return false;
	}

	bool operator<=(const Point3D& cmp) const
	{
		return (*this < cmp) || (*this == cmp);
	}

	bool operator>=(const Point3D& cmp) const
	{
		return (*this > cmp) || (*this == cmp);
	}

	Point3D& operator=(const Point3D& cmp)
	{
		this->X = cmp.X;
		this->Y = cmp.Y;
		this->Z = cmp.Z;
		return *this;
	}
};
#endif //POINT_HPP
