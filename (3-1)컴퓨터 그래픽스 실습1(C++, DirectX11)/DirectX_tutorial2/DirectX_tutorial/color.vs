////////////////////////////////////////////////////////////////////////////////
// Filename: color.vs
////////////////////////////////////////////////////////////////////////////////

// cpp�� �����

/////////////
// GLOBALS //
/////////////

// Struct ���� ����
// ���� ���۸� �������� ����ϴ� �ڷ��� cbuffer
cbuffer MatrixBuffer
{
 // �� matrix�� ũ��� 4 * 4 ���
 // ó�� ������ ����(vertex)�� Local��ǥ��
 // > Local ��ǥ�� : �� �ϳ��� �����ϱ� ���� ��ǥ��

 // Local��ǥ�踦 World��ǥ��� �ٲٱ� ���� ���
 // > World��ǥ�� : DirextX���� ����ϴ� ��ǥ��
 matrix worldMatrix;
 // World��ǥ�踦 �츮�� ī�޶�� ���� ���̴� ��ǥ��� �ٲٱ� ���� ���
 // > Camera��ǥ Ȥ�� View��ǥ : �츮�� ī�޶�� �� �� ���̴� ��ǥ
 // > 3���� ��ǥ��
 matrix viewMatrix;
 // ���� �츮���� ���̴� ȭ������ �ٲٴ� ���(���ٹ� ���� ����)
 // > 2���� ��ǥ��
 matrix projectionMatrix;

 // ��������� pixel�� ��Ÿ���� �ȴ�.
};


//////////////
// TYPEDEFS //
//////////////

// float4 : ���� 4������ ǥ������, (x, y, z, w), (r, g, b, a) ��
// > 4���� float���� ����
// 4�� ¥���� ���� matrix�� ���� ����

// �ϳ��� Vertex�� ������ ����
struct VertexInputType
{
 float4 position : POSITION;
 float4 color : COLOR;
};

// 
struct PixelInputType
{
 float4 position : SV_POSITION;
 float4 color : COLOR;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

// �Լ�

PixelInputType ColorVertexShader(VertexInputType input)
{
 PixelInputType output;

 // Change the position vector to be 4 units for proper matrix calculations.
 input.position.w = 1.0f;

 // Calculate the position of the vertex against the world, view, and projection matrices.

 // �⺻ ��ǥ���� worldMatrix�� ����
 output.position = mul(input.position, worldMatrix);
 // ���ؼ� ���°��� viewMatrix�� ����
 output.position = mul(output.position, viewMatrix);
 // ���ؼ� ���� ���� projectionMatrix�� ����
 output.position = mul(output.position, projectionMatrix);
 
 // Store the input color for the pixel shader to use.
 output.color = input.color;

 return output;
}