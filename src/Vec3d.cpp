
#include <Vec3d.hpp>

        Vec3d::Vec3d(double inX, double inY, double inZ) : x(inX), y(inY), z(inZ) {}

        void Vec3d::setX(double inX) {
            x = inX;
        }

        void Vec3d::setY(double inY) {
            y = inY;
        }

        void Vec3d::setZ(double inZ) {
            z = inZ;
        }

        double Vec3d::dot(Vec3d inVec) {
            return (inVec.x * x) + (inVec.y * y) + ( inVec.z * z);
        }
