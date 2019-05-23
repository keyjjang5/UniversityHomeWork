#include "stdafx.h"
#include "CMyRect.h"
#include "MFCHw2.h"

using namespace std;

CMyRect::CMyRect(CPoint pt1, CPoint pt2):CMyShape(pt1, pt2)
{
	
}

CMyRect::CMyRect()
{

}

CMyRect::~CMyRect()
{

}

void CMyRect::draw(CDC *rdc)
{
	CBitmap rBitmap;
	rBitmap.LoadBitmap(IDB_BITMAP1);
	CBrush rBrush(&rBitmap);
	rdc->SelectObject(&rBrush);


	rdc->Rectangle(ptS.x, ptS.y, ptE.x, ptE.y);
}

void CMyRect::ptEInput(CPoint pt)
{
	ptE = pt;
}