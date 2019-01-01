#include "stdafx.h"
#include "util.h"


double AngToRad(double angle)
{
	return angle * PI / 180;
}

double RadToAng(double radian)
{
	return radian * 180 / PI;
}

POINT RotationPoint(POINT fixedPoint, POINT srcPoint, double angle)
{

	// 这里首先将直角坐标转换为极坐标
	// 获取x值与y值的偏移量
	double offset_x = double(srcPoint.x - fixedPoint.x);
	double offset_y = double(srcPoint.y - fixedPoint.y);
	// 获取极坐标极半径
	double polar_radius = sqrt(pow(offset_x, 2) + pow(offset_y, 2));
	// 将原变化角度转换为改变的极角
	double change_polar_angle = AngToRad(angle);
	// 获取原极角
	double src_polar_angle;
	if (offset_x == 0)
	{
		if (offset_y > 0)
			src_polar_angle = PI / 2;
		else if (offset_y < 0)
			src_polar_angle = 3 * PI / 4;
		else
			return srcPoint;
	}
	else
	{
		src_polar_angle = atan(offset_y / offset_x);
	}
	// 减去对应弧度后，转换回直角坐标
	double x = polar_radius * cos(src_polar_angle - change_polar_angle);
	double y = polar_radius * sin(src_polar_angle - change_polar_angle);
	// 加上左上坐标后得到实际坐标值后为POINT初始化后返回
	return POINT{ long(x + fixedPoint.x), long(y + fixedPoint.y) };
}
