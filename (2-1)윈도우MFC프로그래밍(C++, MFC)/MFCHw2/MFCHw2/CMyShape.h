#pragma once

using namespace std;

class CMyShape
{
public :
	CMyShape(CPoint pt1, CPoint pt2);
	CMyShape();
	~CMyShape();
	CPoint ptS;
	CPoint ptE;

	virtual void draw(CDC *sdc);
	virtual void ptEInput(CPoint pt);
};