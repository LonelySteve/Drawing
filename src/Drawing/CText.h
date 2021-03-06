#pragma once
#include"CShape.h"

/*文本*/
SHAPE_CLASS_START(CText, SHAPE_PROPERTY_TEXT, SHAPE_PROPERTY_HEIGHT, SHAPE_PROPERTY_ANGLE)
protected:
	// 记录文本无旋转度数时的矩形数据
	RECT rect;
	SHAPE_PROPERTY_TEXT;
	SHAPE_PROPERTY_HEIGHT;
	SHAPE_PROPERTY_ANGLE;
SHAPE_CLASS_END