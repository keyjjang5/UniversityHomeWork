////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
GraphicsClass::GraphicsClass()
{
	m_D3D = 0;

	m_Camera = 0;

	//m_Model[0] = 0;
	//m_Model[1] = 0;
	//m_Model[2] = 0;
	for (int i = 0; i < 19; i++) m_Model[i] = 0;

	//m_ColorShader = 0;
	m_TextureShader = 0;
	m_Bitmap = 0;

	m_LightShader = 0;
	m_Light = 0;

	//m_Input = 0;

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

	//m_Input = new InputClass;
	//if (!m_Input)
	//{
	//	return false;
	//}
	//m_Input->Initialize();

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
	//// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -30.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);


	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	for (int i = 0; i < 19; i++)
	{
		m_Model[i] = new ModelClass;
		if (!m_Model[i])
		{
			return false;
		}

	}


	// Initialize the model object.
	result = m_Model[0]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model0.txt", (WCHAR *)L"../Tutorial/texture/book.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[1]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model1.txt", (WCHAR *)L"../Tutorial/texture/carpet.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[2]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model2.txt", (WCHAR *)L"../Tutorial/texture/ceilinglight.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[3]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model3.txt", (WCHAR *)L"../Tutorial/texture/circletable.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[4]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model4.txt", (WCHAR *)L"../Tutorial/texture/cushion1.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[5]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model5.txt", (WCHAR *)L"../Tutorial/texture/cushion2.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[6]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model6.txt", (WCHAR *)L"../Tutorial/texture/cushion3.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[7]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model7.txt", (WCHAR *)L"../Tutorial/texture/ground.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[8]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model8.txt", (WCHAR *)L"../Tutorial/texture/picture.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[9]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model9.txt", (WCHAR *)L"../Tutorial/texture/picturecase.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[10]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model10.txt", (WCHAR *)L"../Tutorial/texture/sofa1.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[11]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model11.txt", (WCHAR *)L"../Tutorial/texture/sofa2.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[12]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model12.txt", (WCHAR *)L"../Tutorial/texture/table.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[13]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model13.txt", (WCHAR *)L"../Tutorial/texture/tv.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[14]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model14.txt", (WCHAR *)L"../Tutorial/texture/tvcase.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[15]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model15.txt", (WCHAR *)L"../Tutorial/texture/tvwall.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[16]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model16.txt", (WCHAR *)L"../Tutorial/texture/wall.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[17]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model17.txt", (WCHAR *)L"../Tutorial/texture/stair.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[18]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model18.txt", (WCHAR *)L"../Tutorial/texture/stairwall.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	/*result = m_Model[19]->Initialize(m_D3D->GetDevice(), (char*)"../Tutorial/Model4.txt", (WCHAR *)L"../Tutorial/data/ground.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}*/

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
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 0.5f);
	m_Light->SetDiffuseColor(0.3f, 0.3f, 0.3f, 0.1f);
	//m_Light->SetDirection(1.0f, 0.0f, 0.0f);

	m_Light->SetDirection(0.0f, -1.0f, 0.4f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 0.8f);
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
		(WCHAR*)L"../Tutorial/data/background.jpg", 256, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	return true;
}
void GraphicsClass::Shutdown()
{

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

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

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
		delete m_LightShader; 
		m_LightShader = 0; 
	}


	// Release the model object.
	for (int i = 0; i < 19; i++)
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

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	return;
}
bool GraphicsClass::Frame(int fps, int cpu, int obj, int poly, int screenX, int screenY, int mouseX, int mouseY, float frameTime)
{
	bool result;
	
	static float rotation = 0.0f;

	m_Camera->TickUpdate();

	// Update the rotation variable each frame. 
	rotation += (float)D3DX_PI * 0.005f;
	if(rotation > 360.0f) 
	{
		rotation -= 360.0f; 
	}

	// Set the location of the mouse.
	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetObject(obj, m_D3D->GetDeviceContext());
	if (!result) return false;

	result = m_Text->SetPolygon(poly, m_D3D->GetDeviceContext());
	if (!result) return false;

	result = m_Text->SetScreenSize(screenX, screenY, m_D3D->GetDeviceContext());
	if (!result) return false;

	result = m_Text->SetCameraPos(m_Camera->GetPosition(), m_D3D->GetDeviceContext());
	if (!result) return false;

	result = m_Text->SetCameraRot(m_Camera->GetRotation(), m_D3D->GetDeviceContext());
	if (!result) return false;

	result = m_Text->SetUpPos(m_Camera->GetLookAt(), m_D3D->GetDeviceContext());
	if (!result) return false;

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
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix, orthoMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.2f, 0.2f, 0.2f, 1.0f);
	// Generate the view matrix based on the camera's position.
	m_Camera->Render();
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	
	m_D3D->GetOrthoMatrix(orthoMatrix);
	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();


	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(),
		worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//D3DXMatrixRotationY(&worldMatrix, rotation);

	for (int i = 0; i < 19; i++)
	{
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		m_Model[i]->Render(m_D3D->GetDeviceContext());
		//// Render the model using the color shader.
		//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix,
		//	viewMatrix, projectionMatrix);

		// Render the model using the texture shader.
		//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(),
		//	worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());

		// Render the model using the light shader. 
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[i]->GetIndexCount(), worldMatrix,
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

//void GraphicsClass::MoveCamera(float x, float y, float z)
//{
//	m_Camera->SetPosition(x, y, z);
//}

void GraphicsClass::MoveCamera(int key)
{
	if (key == DIK_W) m_Camera->FrontWalk(1.0f);
	if (key == DIK_S) m_Camera->FrontWalk(-1.0f);

	if (key == DIK_A) m_Camera->SideWalk(1.0f);
	if (key == DIK_D) m_Camera->SideWalk(-1.0f);
}

void GraphicsClass::RotateCamera(float x, float y, float z)
{

	m_Camera->SetRotation(x, y, z);
	
}