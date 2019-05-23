#pragma once
#include "CMyShape.h"
using namespace std;

class CMyRect :public CMyShape
{
public:
	CMyRect(CPoint pt1, CPoint pt2);
	CMyRect();
	~CMyRect();
	void draw(CDC *sdc);
	void ptEInput(CPoint pt);
};