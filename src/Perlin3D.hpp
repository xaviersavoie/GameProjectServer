#ifndef PERLIN_3D_HPP
#define PERLIN_3D_HPP

#include <Vec3d.hpp>

class Perlin3D {
   
    public:

        static int p[512];

        static double grad(int hash, double x, double y, double z);        

        static Vec3d getGradientVector(int v);

        static double generatePerlin(double x, double y, double z);

        static double fade(double t);

        static double lerp(double t, double a1, double a2);

        static void IMAGETEST();


};

#endif
