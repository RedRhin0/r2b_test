#include "geom3d.h"

Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {};

std::ostream &operator<<(std::ostream &os, const Point3D &point)
{
    // os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    os << point.x << " " << point.y << " " << point.z;
    return os;
}

std::istream &operator>>(std::istream &is, Point3D &point)
{
    double x, y, z;

    // can we read three double?
    if (is >> x >> y >> z)
    {
        point.x = x;
        point.y = y;
        point.z = z;
    }

    return is;
}

// Ax + By + Cz + D = 0
Plane::Plane(const double &A, const double &B, const double &C, const double &D) : A(A), B(B), C(C), D(D) {};
// but {0,0,0,x} is invalid plane...

// Point3D x3 constructor
Plane::Plane(const Point3D &p1, const Point3D &p2, const Point3D &p3)
{
    A = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y);
    B = (p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z);
    C = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    D = -(A * p1.x + B * p1.y + C * p1.z);
};

double Plane::pointPosition(const Point3D &p) const
{
    return A * p.x + B * p.y + C * p.z + D;
};

bool Plane::isPointOnPlane(const Point3D &p) const
{
    return std::abs(pointPosition(p)) < eps;
};

// are target and origin in same halfspaces relative to planes x2
bool isSameHalfSpace(const Plane &plane1, const Plane &plane2, const Point3D &target, const Point3D &origin)
{
    double pos1 = plane1.pointPosition(target);
    double pos2 = plane2.pointPosition(target);
    double originPos1 = plane1.pointPosition(origin);
    double originPos2 = plane2.pointPosition(origin);

    // target on plane counts as same half space
    return ((pos1 * originPos1 > 0) || plane1.isPointOnPlane(target)) &&
           ((pos2 * originPos2 > 0) || plane2.isPointOnPlane(target));
}

std::ostream &operator<<(std::ostream &os, const Plane &plane)
{
    os << "Plane(" << plane.A << "x + " << plane.B << "y + " << plane.C << "z + " << plane.D << " = 0)";
    return os;
}

std::vector<Point3D> readPointsFromFile(const std::string &filePath)
{
    std::ifstream file(filePath);
    std::vector<Point3D> points;

    if (!file.is_open())
    {
        std::cerr << "Error: can not open the file: " << filePath << '\n';
        exit(1);
    }

    double x, y, z;
    while (file >> x >> y >> z)
    {
        points.emplace_back(x, y, z);
    }

    if (!file.eof())
    {
        std::cerr << "Error: Invalid data found in the file " << filePath << " (expected three numbers for each point)." << '\n';
        exit(1);
    }

    return points;
}