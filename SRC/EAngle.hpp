#pragma once
#include "Vector.hpp"
#include <cmath>


class EAngle
{
    public:
    EAngle()
    {
        p = y = r = 0;
    }
    EAngle(float pitch, float yaw, float roll)
    {
        p = pitch;
        y = yaw;
        r = roll;
    }

    Vector3 ToVector3() const
    {
        return Vector3(std::cos(y) * std::cos(p),
            std::sin(p),
            std::sin(y) * std::cos(p));
    }

    void Normalize()
    {
        if(p > 89)
            p = 89;
        if(p < -89)
            p = -89;
        
        while(y < -180)
            y += 360;
        while(y > 180)
            y -= 360;
    }

    float p, y, r;
};
