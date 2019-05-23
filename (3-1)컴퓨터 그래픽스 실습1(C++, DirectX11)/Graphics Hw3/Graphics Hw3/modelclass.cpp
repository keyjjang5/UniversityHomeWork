////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////

#include "modelclass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;	m_model = 0;
}

ModelClass::ModelClass(const ModelClass& other)
{
}

ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename)
{
	bool result;

	// Load in the model data,
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}

	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	

	return true;
}

void ModelClass::Shutdown()
{
	// Release the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);
	return;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;	int beforeVCount, beforeICount;	// Set the number of vertices in the vertex array.
	// Hw3 변경 3->15
	m_vertexCount = 72;

	// Set the number of indices in the index array.
	// Hw3 변경 3->15
	m_indexCount = 72;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array with data.

	// Load the vertex array and index array with data.
	for (int i = 0; i < 36; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
		indices[i] = i;
	}

	// hw5 추가
	LoadModel((char*)"../Graphics Hw3/data/tetrahedron.txt", 36, 48);
	/*beforeVCount = m_vertexCount;
	beforeICount = m_indexCount;

	m_vertexCount += 12;
	m_indexCount += 12;*/

	
	for (int i = 36; i <48; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
		indices[i] = i;
	}

	LoadModel((char*)"../Graphics Hw3/data/triangularpole.txt", 48, 72);

	for (int i = 48; i < 72; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
		indices[i] = i;
	}

	// Vertex 정보 : pixel shader로 들어갈 정보
	// x, y, z 순
	//vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f); // Bottom left.
	//vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);
	//vertices[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f); // Top middle.
	//vertices[1].texture = D3DXVECTOR2(0.5f, 0.0f);
	//vertices[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f); // Bottom right.
	//vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);
	//vertices[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 가까이있는 사각형
	//vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);	// Bottom left.
	//vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);
	//vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);	// Top left.
	//vertices[1].texture = D3DXVECTOR2(0.0f, 0.0f);
	//vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);	// Bottom right.
	//vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);
	//vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);	// Top right
	//vertices[3].texture = D3DXVECTOR2(1.0f, 0.0f);

	//// 멀리있는 사각형
	//vertices[4].position = D3DXVECTOR3(2.0f, 2.0f, 3.0f);	// Bottom left.
	//vertices[4].texture = D3DXVECTOR2(0.0f, 1.0f);
	//vertices[5].position = D3DXVECTOR3(2.0f, 4.0f, 3.0f);	// Top left.
	//vertices[5].texture = D3DXVECTOR2(0.0f, 0.0f);
	//vertices[6].position = D3DXVECTOR3(4.0f, 2.0f, 3.0f);	// Bottom right.
	//vertices[6].texture = D3DXVECTOR2(1.0f, 1.0f);
	//vertices[7].position = D3DXVECTOR3(4.0f, 4.0f, 3.0f);	// Top right
	//vertices[7].texture = D3DXVECTOR2(1.0f, 0.0f);

	//// Hw3 추가
	//// 사각형
	//vertices[3].position = D3DXVECTOR3(-4.0f, -1.0f, 0.0f); // 왼쪽아래
	//vertices[3].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	//vertices[4].position = D3DXVECTOR3(-4.0f, 1.0f, 0.0f); // 왼쪽위
	//vertices[4].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	//vertices[5].position = D3DXVECTOR3(-2.0f, -1.0f, 0.0f); // 오른쪽아래
	//vertices[5].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	//vertices[6].position = D3DXVECTOR3(-2.0f, -1.0f, 0.0f); // 오른쪽아래
	//vertices[6].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	//vertices[7].position = D3DXVECTOR3(-4.0f, 1.0f, 0.0f); // 왼쪽위
	//vertices[7].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	//vertices[8].position = D3DXVECTOR3(-2.0f, 1.0f, 0.0f); // 오른쪽위
	//vertices[8].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	//
	//// 별모양
	//vertices[9].position = D3DXVECTOR3(3.0f, 0.75f, 0.0f); // 왼쪽 위
	//vertices[9].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	//vertices[10].position = D3DXVECTOR3(5.0f, 0.75f, 0.0f); // 오른쪽 위
	//vertices[10].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	//vertices[11].position = D3DXVECTOR3(4.0f, -1.25f, 0.0f); // 가운데 아래
	//vertices[11].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[12].position = D3DXVECTOR3(3.0f, -0.75f, 0.0f); // 왼쪽 아래
	//vertices[12].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	//vertices[13].position = D3DXVECTOR3(4.0f, 1.25f, 0.0f); // 가운데 위
	//vertices[13].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	//vertices[14].position = D3DXVECTOR3(5.0f, -0.75f, 0.0f); // 오른쪽아래
	//vertices[14].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	//


	// Load the index array with data.
	//indices[0] = 0; // Bottom left.
	//indices[1] = 1; // Top left.
	//indices[2] = 2; // Bottom right.
	
	//indices[3] = 2; 
	//indices[4] = 1;
	//indices[5] = 3;	// Top right

	//indices[6] = 4;
	//indices[7] = 5;
	//indices[8] = 6;

	//indices[9] = 6;
	//indices[10] = 5;
	//indices[11] = 7;

	/*indices[3] = 3;
	indices[4] = 4;
	indices[5] = 5;

	indices[6] = 6;
	indices[7] = 7;
	indices[8] = 8;

	indices[9] = 9;
	indices[10] = 10;
	indices[11] = 11;

	indices[12] = 12;
	indices[13] = 13;
	indices[14] = 14;*/

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	// device : 그래픽카드
	// 이 위까지는 메인메모리에만 잡혀있고 이 아래는 그래픽카드에 잡음
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	// device : 그래픽카드
	// 이 위까지는 메인메모리에만 잡혀있고 이 아래는 그래픽카드에 잡음
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;

	return true;
}

void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}
	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
	return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	// 데이터들이 얼마나 떨어져있는지에 대한 변수
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	// Topology
	// 인수는 어떻게 표현할 것인지에 대한 것
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;
	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}
	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}
	return true;
}

void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
	return;
}

bool ModelClass::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;
	// Open the model file.
	fin.open(filename);
	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}
	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	// Read in the vertex count.
	fin >> m_vertexCount;
	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;
	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}
	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);
	// Read in the vertex data.
	for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}
	// Close the model file.
	fin.close();
	return true;
}

void ModelClass::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}
	return;
}

bool ModelClass::LoadModel(char* filename, int start, int last)
{
	ifstream fin;
	char input;
	int i;
	// Open the model file.
	fin.open(filename);
	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}
	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	// Read in the vertex count.
	fin >> m_vertexCount;
	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;
	// Create the model using the vertex count that was read in.
	// m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}
	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);
	// Read in the vertex data.
	for (i = start; i < last; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}
	// Close the model file.
	fin.close();
	return true;
}

//bool ModelClass::RotateModel(char* filename, int start, int last)
//{
//	ifstream fin;
//	char input;
//	int i;
//	// Open the model file.
//	fin.open(filename);
//	// If it could not open the file then exit.
//	if (fin.fail())
//	{
//		return false;
//	}
//	// Read up to the value of vertex count.
//	fin.get(input);
//	while (input != ':')
//	{
//		fin.get(input);
//	}
//	// Read in the vertex count.
//	fin >> m_vertexCount;
//	// Set the number of indices to be the same as the vertex count.
//	m_indexCount = m_vertexCount;
//	// Create the model using the vertex count that was read in.
//	m_model = new ModelType[m_vertexCount];
//	if (!m_model)
//	{
//		return false;
//	}
//	// Read up to the beginning of the data.
//	fin.get(input);
//	while (input != ':')
//	{
//		fin.get(input);
//	}
//	fin.get(input);
//	fin.get(input);
//	// Read in the vertex data.
//	for (i = start; i < last; i++)
//	{
//		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
//		fin >> m_model[i].tu >> m_model[i].tv;
//		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
//	}
//	// Close the model file.
//	fin.close();
//	return true;
//}