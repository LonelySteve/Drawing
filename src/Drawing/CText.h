#pragma once
#include"CShape.h"

/*�ı�*/
SHAPE_CLASS_START(CText, CString text, int height, int angle)
protected:
	RECT rect;
	CString text;
	int height;
	int angle;
SHAPE_CLASS_END