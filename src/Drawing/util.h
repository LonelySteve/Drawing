#pragma once
#include<afx.h>

#define PI 3.1415926

#define IF_ASSIGN(boolVal,lVal,rVAl) if(boolVal) lVal=rVAl

#define PTR_NULL_RETURN(ptr,retVal) if(ptr == NULL) return retVal

#define PTR_CALL_METHOD(ptr,func_call) if (ptr != NULL) ptr->func_call         

#define PTR_ASSIGN(ptr,val) IF_ASSIGN(ptr != NULL,*ptr,val)

#define PTR_VAL_ASSIGN(ptr,val) IF_ASSIGN(ptr == NULL,ptr,val)

#define ANG_TO_RAD(angle) angle * PI / 180

#define RAD_TO_ANG(radian) radian * 180 / PI

POINT RotationPoint(POINT fixedPoint, POINT srcPoint, double angle);
