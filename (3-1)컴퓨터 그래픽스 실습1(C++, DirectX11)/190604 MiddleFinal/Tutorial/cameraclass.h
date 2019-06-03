#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_
//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	void Render();
	void GetViewMatrix(D3DXMATRIX&);

	void FrontWalk(long);
	void SideWalk(long);

	void TickUpdate();
	void CheckRange();

	// 수정
	D3DXVECTOR3 GetUp();
	D3DXVECTOR3 GetLookAt();

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_viewMatrix;

	D3DXVECTOR3 m_pos, m_lookAt, m_up;
	
	DWORD m_dwElapsedTime;

	// 추가
};
#endif