#include "IsoConversion.h"

float calcXc(float Xi, float Yi, float Gx, float Xcmax)
{
    float Gy = Gx / 2.0;
    float Xc = 0.5 * ( (Xi/Gx) - (Yi/Gy) + 1.0 + Xcmax);
    return Xc;
}

float calcYc(float Xi, float Yi, float Gx, float Xcmax)
{
    float Gy = Gx / 2.0;
    float Yc = (Yi/2.0/Gy) - 0.5 + (Xi/2.0/Gx) - (Xcmax/2.0);
    return Yc;
}

float calcXi(float Xc, float Yc, float Gx, float Xcmax)
{
    float Xi = Gx * (Xc + Yc);
    return Xi;
}

float calcYi(float Xc, float Yc, float Gx, float Xcmax)
{
    float Gy = Gx / 2.0;
    float Yi = Gy * (Xcmax - Xc + Yc + 1.0);
    return Yi;
}
