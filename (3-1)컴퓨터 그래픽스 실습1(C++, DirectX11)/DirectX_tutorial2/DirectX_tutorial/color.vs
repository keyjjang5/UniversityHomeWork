////////////////////////////////////////////////////////////////////////////////
// Filename: color.vs
////////////////////////////////////////////////////////////////////////////////

// cpp와 비슷함

/////////////
// GLOBALS //
/////////////

// Struct 같은 거임
// 뭔가 버퍼를 잡으려면 사용하는 자료형 cbuffer
cbuffer MatrixBuffer
{
 // 각 matrix의 크기는 4 * 4 행렬
 // 처음 들어오는 정점(vertex)는 Local좌표계
 // > Local 좌표계 : 모델 하나를 정의하기 위한 좌표계

 // Local좌표계를 World좌표계로 바꾸기 위한 행렬
 // > World좌표계 : DirextX에서 사용하는 좌표계
 matrix worldMatrix;
 // World좌표계를 우리가 카메라로 볼때 보이는 좌표계로 바꾸기 위한 행렬
 // > Camera좌표 혹은 View좌표 : 우리가 카메라로 볼 때 보이는 좌표
 // > 3차원 좌표계
 matrix viewMatrix;
 // 실제 우리에게 보이는 화면으로 바꾸는 행렬(원근법 등을 적용)
 // > 2차원 좌표계
 matrix projectionMatrix;

 // 결과적으로 pixel로 나타나게 된다.
};


//////////////
// TYPEDEFS //
//////////////

// float4 : 뭐든 4가지로 표현가능, (x, y, z, w), (r, g, b, a) 등
// > 4개의 float값을 가짐
// 4개 짜리라서 위의 matrix와 연산 가능

// 하나의 Vertex가 가지는 정보
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

// 함수

PixelInputType ColorVertexShader(VertexInputType input)
{
 PixelInputType output;

 // Change the position vector to be 4 units for proper matrix calculations.
 input.position.w = 1.0f;

 // Calculate the position of the vertex against the world, view, and projection matrices.

 // 기본 좌표값에 worldMatrix를 곱합
 output.position = mul(input.position, worldMatrix);
 // 곱해서 나온값에 viewMatrix를 곱합
 output.position = mul(output.position, viewMatrix);
 // 곱해서 나온 값에 projectionMatrix를 곱함
 output.position = mul(output.position, projectionMatrix);
 
 // Store the input color for the pixel shader to use.
 output.color = input.color;

 return output;
}