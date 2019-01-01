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

	// �������Ƚ�ֱ������ת��Ϊ������
	// ��ȡxֵ��yֵ��ƫ����
	double offset_x = double(srcPoint.x - fixedPoint.x);
	double offset_y = double(srcPoint.y - fixedPoint.y);
	// ��ȡ�����꼫�뾶
	double polar_radius = sqrt(pow(offset_x, 2) + pow(offset_y, 2));
	// ��ԭ�仯�Ƕ�ת��Ϊ�ı�ļ���
	double change_polar_angle = AngToRad(angle);
	// ��ȡԭ����
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
	// ��ȥ��Ӧ���Ⱥ�ת����ֱ������
	double x = polar_radius * cos(src_polar_angle - change_polar_angle);
	double y = polar_radius * sin(src_polar_angle - change_polar_angle);
	// �������������õ�ʵ������ֵ��ΪPOINT��ʼ���󷵻�
	return POINT{ long(x + fixedPoint.x), long(y + fixedPoint.y) };
}
