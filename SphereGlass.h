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
    SphereGlass();
    SphereGlass(MyVector cent, double rad, Color col, float refractionIndex);
    void Rebound(Ray *ray, MyVector hitPosition);
};

SphereGlass::SphereGlass() : Sphere(), refractionIndex(1) {}
SphereGlass::SphereGlass(MyVector cent, double rad, Color color, float refractionIndex) : Sphere(cent, rad, color), refractionIndex(refractionIndex)
{
}
void SphereGlass::Rebound(Ray *ray, MyVector hitPosition)
{
    MyVector normalVector = this->NormalVector(hitPosition);
    float refractionRatio = 1.0 / refractionIndex;
    if (dotProduct(ray->direction, normalVector) > 0) // ray inside the sphere
    {
        normalVector = -1 * normalVector;
        refractionRatio = refractionIndex;
    }
    double cosTheta = dotProduct(/*-1 * */ ray->direction, normalVector);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
    MyVector outPut;
    if (refractionRatio * sinTheta > 1.0) // reflection
    {
        MyVector v = dotProduct(/*-1 * */ (ray->direction), normalVector) * normalVector;
        MyVector u = ray->direction + (-1.0 * v);
        outPut = (u - v);
    }
    else // refraction
    {
        MyVector v = (-1.0 / refractionRatio) * (ray->direction + cosTheta * normalVector);
        MyVector u = (-1 * sqrt(1 - v.moduleSq())) * normalVector;
        outPut = (u + v);
    }

    outPut.normalize();
    ray->direction = outPut;
    ray->position = hitPosition;
    ray->bounces++;
}

#endif