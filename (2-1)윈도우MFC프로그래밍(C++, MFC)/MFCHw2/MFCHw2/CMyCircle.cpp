#include "stdafx.h"
#include "CMyCircle.h"

using namespace std;

CMyCircle::CMyCircle(CPoint pt1, CPoint pt2):CMyShape(pt1, pt2)
{
	
}

CMyCircle::CMyCircle()
{

}

CMyCircle::~CMyCircle()
{

}

void CMyCircle::draw(CDC *edc)
{
	/*CDC edc;
	CBrush eBrush(RGB(0, 255, 0));
	edc.SelectObject(&eBrush);
	edc.Ellipse(ptS.x, ptS.y, ptE.x, ptE.y);*/

	CBrush eBrush(RGB(0,255,0));
	edc->SelectObject(&eBrush);
	edc->Ellipse(ptS.x, ptS.y, ptE.x, ptE.y);
}

void CMyCircle::ptEInput(CPoint pt)
{
	ptE = pt;
}
