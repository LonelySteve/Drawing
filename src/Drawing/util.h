#pragma once
#include<afx.h>

#define PI 3.1415926

#define IF_ASSIGN(boolVal,lVal,rVAl) if(boolVal) lVal=rVAl

#define PTR_NULL_RETURN(ptr,retVal) if(ptr == NULL) return retVal

#define PTR_CALL_METHOD(ptr,func_call) if (ptr != NULL) ptr->func_call         

#define PTR_ASSIGN(ptr,val) IF_ASSIGN(ptr != NULL,*ptr,val)

#define PTR_VAL_ASSIGN(ptr,val) IF_ASSIGN(ptr == NULL,ptr,val)

double AngToRad(double angle);

double RadToAng(double radian);

POINT RotationPoint(POINT fixedPoint, POINT srcPoint, double angle);
