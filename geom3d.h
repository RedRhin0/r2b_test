#ifndef GEOM3D
#define GEOM3D

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>

constexpr double eps = 1e-9;

struct Point3D
{
    double x, y, z;

    Point3D(double x = 0, double y = 0, double z = 0);
};

std::ostream &operator<<(std::ostream &os, const Point3D &point);
std::istream &operator>>(std::istream &is, Point3D &point);

struct Plane
{
    double A, B, C, D;

    Plane(const double &A = 0, const double &B = 0, const double &C = 0, const double &D = 0);
    Plane(const Point3D &p1, const Point3D &p2, const Point3D &p3);

    double pointPosition(const Point3D &p) const;
    bool isPointOnPlane(const Point3D &p) const;
};

std::ostream &operator<<(std::ostream &os, const Plane &plane);

bool isSameHalfSpace(const Plane &plane1, const Plane &plane2, const Point3D &target, const Point3D &origin);

std::vector<Point3D> readPointsFromFile(const std::string &filePath);

#endif // GEOM3D