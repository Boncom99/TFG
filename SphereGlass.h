#ifndef SPHEREGLASS_H
#define SPHEREGLASS_H
#include <vector>
#include "Object.h"
#include "Ray.h"
#include "MyVector.h"
#include "Sphere.h"
#include "Color.h"
#include <iostream>
class SphereGlass : public Sphere
{
public:
    float refractionIndex;
    SphereGlass(MyVector cent, double rad, Color col, float refractionIndex);
    void Rebound(Ray *ray, MyVector hitPosition);
    double distance(MyVector position);
};

SphereGlass::SphereGlass(MyVector cent, double rad, Color color, float refractionIndex) : Sphere(cent, rad, color, 0), refractionIndex(refractionIndex)
{
}
bool randomBool()
{
    return (rand() % (2)) == 1;
}
void SphereGlass::Rebound(Ray *ray, MyVector hitPosition)
{
    MyVector normalVector = this->NormalVector(hitPosition);
    float refractionRatio = refractionIndex;
    if (dotProduct(ray->direction, normalVector) > 0) // ray inside the sphere
    {
        normalVector = -1 * normalVector;
        refractionRatio = 1.0 / refractionIndex;
    }
    double cosTheta = dotProduct(-1 * ray->direction, normalVector);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
    MyVector outPut;
    if (refractionRatio * sinTheta > 1.0 && randomBool()) // reflection
    {
        MyVector v = dotProduct(-1 * (ray->direction), normalVector) * normalVector;
        outPut = ray->direction - 2 * v;
    }
    else // refraction

    {
        MyVector v = (-1.0 / refractionRatio) * (ray->direction + cosTheta * normalVector);
        MyVector u = -1 * (sqrt(1 - v.moduleSq())) * normalVector;
        outPut = (u + v);
    }

    outPut.normalize();
    ray->direction = outPut;
    ray->position = hitPosition;
}
double SphereGlass::distance(MyVector position)
{
    return 0;
}

#endif