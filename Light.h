#ifndef LIGHT_H
#define LIGHT_H
#include <vector>
#include "Ray.h"
#include "MyVector.h"
#include "Color.h"
#include <iostream>
class Light
{
public:
    MyVector center;
    double radius;
    Color color;
    Light();
    Light(MyVector center, double radius, Color color);
    double hit(Ray ray);
};

Light::Light() : center(MyVector(0, 0, 0)), radius(0), color(Color(0, 0, 0))
{
}
Light::Light(MyVector center, double radius, Color color) : center(center), radius(radius), color(color)
{
}
double Light::hit(Ray ray)
{
    // double a = 1; //direction.moduleSq() //sempre valdrà 1
    double b = 2 * (dotProduct((ray.position - center), ray.direction));
    double c = (ray.position - center).moduleSq() - radius * radius;
    // Discriminant
    double discriminant = b * b - 4 * c;
    if (discriminant >= 0)
    {
        double t2 = (-1 * b - sqrt(discriminant)) / 2.0;
        if (t2 > 0.00001)
        {
            return t2;
        }
        else
        {
            double t1 = (-1 * b + sqrt(discriminant)) / (2.0);
            if (t1 > 0.00001)
            {
                return t1;
            }
        }
    }

    return -1;
}

#endif
