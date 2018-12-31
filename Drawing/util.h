#pragma once
#include<afx.h>

double AngToRad(double angle);

double RadToAng(double radian);

POINT RotationPoint(POINT fixedPoint, POINT srcPoint, double angle);