#include "stdafx.h"
#include "util.h"

#define PI 3.1415926

POINT RotationPoint(POINT fixedPoint, POINT srcPoint, double angle)
{
 
	// 这里首先将直角坐标转换为极坐标
		// 获取相对x值与y值
	double relatively_x = double(srcPoint.x - fixedPoint.x);
	double relatively_y = double(srcPoint.y - fixedPoint.y);
	// 获取极坐标极半径
	double polar_radius = sqrt(pow(relatively_x, 2) + pow(relatively_y, 2));
	// 将原变化角度转换为改变的极角
	double change_polar_angle = angle * PI / 180;
	// 获取原极角
	double src_polar_angle;
	if (relatively_x == 0)
	{
		if (relatively_y > 0)
			src_polar_angle = PI / 2;
		else if (relatively_y < 0)
			src_polar_angle = 3 * PI / 4;
		else
			return srcPoint;
	}
	else
	{
		src_polar_angle = atan(relatively_y / relatively_x);
	}
	// 减去对应弧度后，转换回直角坐标
	double x = polar_radius * cos(src_polar_angle - change_polar_angle);
	double y = polar_radius * sin(src_polar_angle - change_polar_angle);
	// 加上左上坐标后得到实际坐标值后为POINT初始化后返回
	return POINT{ long(x + fixedPoint.x), long(y + fixedPoint.y) };
}
