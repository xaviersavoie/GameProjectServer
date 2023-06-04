#ifndef VEC_3D_HPP
#define VEC_3D_HPP

    class Vec3d {


        public :
            double x, y, z;

            Vec3d(double inX, double inY, double inZ);

            double getX();

            double getY();

            double getZ();

            void setX(double x);

            void setY(double y);

            void setZ(double z);

            double dot(Vec3d inVec);

    };

#endif
