#include "stdafx.h"
#include "util.h"

#define PI 3.1415926

POINT RotationPoint(POINT fixedPoint, POINT srcPoint, double angle)
{
 
	// �������Ƚ�ֱ������ת��Ϊ������
		// ��ȡ���xֵ��yֵ
	double relatively_x = double(srcPoint.x - fixedPoint.x);
	double relatively_y = double(srcPoint.y - fixedPoint.y);
	// ��ȡ�����꼫�뾶
	double polar_radius = sqrt(pow(relatively_x, 2) + pow(relatively_y, 2));
	// ��ԭ�仯�Ƕ�ת��Ϊ�ı�ļ���
	double change_polar_angle = angle * PI / 180;
	// ��ȡԭ����
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
	// ��ȥ��Ӧ���Ⱥ�ת����ֱ������
	double x = polar_radius * cos(src_polar_angle - change_polar_angle);
	double y = polar_radius * sin(src_polar_angle - change_polar_angle);
	// �������������õ�ʵ������ֵ��ΪPOINT��ʼ���󷵻�
	return POINT{ long(x + fixedPoint.x), long(y + fixedPoint.y) };
}
