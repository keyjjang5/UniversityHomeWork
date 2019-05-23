////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
GraphicsClass::GraphicsClass()
{
	m_D3D = 0;

	m_Camera = 0;
	for (int i = 0; i < 5; i++)
	{
		m_Model[i] = 0;
	}
	m_LightShader = 0;
	m_Light = 0;

	m_Input = 0;

	m_TextureShader = 0;

	m_Bitmap = 0;
	m_Text = 0;
}
GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}
GraphicsClass::~GraphicsClass()
{
}
bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	D3DXMATRIX baseViewMatrix;

	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}
	m_Input->Initialize();

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN,
		SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}
	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -100.0f);
	// Create the model object.
	for (int i = 0; i < 5; i++)
	{
		m_Model[i] = new ModelClass;
		if (!m_Model[i])
		{
			return false;
		}	
	}
	// Initialize the model object.
	result = m_Model[0]->Initialize(m_D3D->GetDevice(),
		(char*)"../DirectX_tutorial/model0.txt",
		(WCHAR*)L"../DirectX_tutorial/Data/Texture/Barrel.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[1]->Initialize(m_D3D->GetDevice(),
		(char*)"../DirectX_tutorial/model1.txt",
		(WCHAR*)L"../DirectX_tutorial/Data/Texture/DeadTree.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[2]->Initialize(m_D3D->GetDevice(),
		(char*)"../DirectX_tutorial/model2.txt",
		(WCHAR*)L"../DirectX_tutorial/Data//Texture/samuraisword2.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[3]->Initialize(m_D3D->GetDevice(),
		(char*)"../DirectX_tutorial/model3.txt",
		(WCHAR*)L"../DirectX_tutorial/Data//Texture/samuraisword2.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[4]->Initialize(m_D3D->GetDevice(),
		(char*)"../DirectX_tutorial/model4.txt",
		(WCHAR*)L"../DirectX_tutorial/Data//Texture/samuraisword2.jpg");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	} 
	
	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{ 
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false; 
	}

	// Create the light object. 
	m_Light = new LightClass; 
	if(!m_Light) 
	{ 
		return false; 
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.3f, 0.4f, 0.5f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 1.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}
	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd, -1);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}
	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight,
		(WCHAR*)L"../DirectX_tutorial/data/sky.jpg", 512, 512); // 원래는 256, 256
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}
	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth,
		screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}



	return true;
}

void GraphicsClass::Shutdown()
{

	// Release the light object. 
	if(m_Light) 
	{
		delete m_Light; 
		m_Light = 0;
	}
	
	// Release the light shader object. 
	if(m_LightShader) 
	{ 
		m_LightShader->Shutdown(); 
		delete m_LightShader; m_LightShader = 0; 
	}


	// Release the model object.
	for (int i = 0; i < 5; i++)
	{
		if (m_Model[i])
		{
			m_Model[i]->Shutdown();
			delete m_Model[i];
			m_Model[i] = 0;
		}
	}
	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}
	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}



	return;
}

bool GraphicsClass::Frame()
{
	bool result;
	
	static float rotation = 0.0f;

	// Update the rotation variable each frame. 
	rotation += (float)D3DX_PI * 0.005f;
	if(rotation > 360.0f) 
	{
		rotation -= 360.0f; 
	}


	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render(float rotation)
{
#define MMATRIXSIZE 6
	D3DXMATRIX viewMatrix, projectionMatrix, orthoMatrix;
	D3DXMATRIX worldMatrix[MMATRIXSIZE];
	bool result;

	

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.2f, 0.2f, 0.2f, 1.0f);
	// Generate the view matrix based on the camera's position.
	m_Camera->Render();
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	for (int i = 0; i < MMATRIXSIZE; i++)
		m_D3D->GetWorldMatrix(worldMatrix[i]);

	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);

	// 이미지 랜더 시작
	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	// 이미지 랜더
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 1000, 800);
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	for (int i = 0; i < MMATRIXSIZE; i++)
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(),
			worldMatrix[i], viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();
	// 이미지 랜더 끝

	// 텍스트 랜더 시작
	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	// 텍스트 랜더
	for (int i = 0; i < MMATRIXSIZE; i++)
		result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix[i], orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();
	// 텍스트 랜더 끝

	
	// Rotate the world matrix by the rotation value so that the triangle will spin.
	D3DXMatrixRotationX(&worldMatrix[0], rotation);
	D3DXMatrixRotationX(&worldMatrix[1], rotation);
	D3DXMatrixRotationX(&worldMatrix[2], rotation);
	D3DXMatrixRotationX(&worldMatrix[3], rotation);
	D3DXMatrixRotationX(&worldMatrix[4], rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	// 모델 랜더링
	for (int i = 0; i < MMATRIXSIZE - 1; i++)
	{
		m_Model[i]->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader. 
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[i]->GetIndexCount(), worldMatrix[i],
			viewMatrix, projectionMatrix, m_Model[i]->GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result)
		{
			return false;
		}
	}


	



	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void GraphicsClass::SetSampling(int menu, HWND hwnd)
{
	//m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd, menu);
}