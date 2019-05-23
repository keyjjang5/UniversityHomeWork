#pragma once

#include "CMyShape.h"
using namespace std;

class CMyCircle :public CMyShape
{
public:
	CMyCircle(CPoint pt1, CPoint pt2);
	CMyCircle();
	~CMyCircle();
	void ptEInput(CPoint pt);
	void draw(CDC *sdc);
};