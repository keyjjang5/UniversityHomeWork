#include <iostream>

using namespace std;

// 한 점을 기준으로 왼쪽 방향, 오른쪽 방향 으로 넣어야 바깥쪽 벡터가 나옴
void crossProduct(float vect_A[], float vect_B[], float cross_P[])

{

	cross_P[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
	cross_P[1] = vect_A[0] * vect_B[2] - vect_A[2] * vect_B[0];
	cross_P[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];
}

void vector(float pointA[], float pointB[], float returnVector[])
{
	returnVector[0] = pointB[0] - pointA[0];
	returnVector[1] = pointB[1] - pointA[1];
	returnVector[2] = pointB[2] - pointA[2];
}

int main()
{
	//float dot[3] = { -4.0, 1.0, -1.0 };
	//float leftFront[3] = { -5.0, -1.0, 0.0 };
	//float lightFront[3] = { -3.0, -1.0, 0.0 };
	//float middleBack[3] = { -4.0, -1.0, -2.0 };

	//float frontState[3];
	//float leftState[3];
	//float lightState[3];
	//float floor[3];

	//float vec1[3];
	//float vec2[3];

	//vector(dot, leftFront, vec1);
	//vector(dot, lightFront, vec2);
	//crossProduct(vec1, vec2, frontState);

	//cout << frontState[0] << ", " << frontState[1] << ", " << frontState[2] << endl;

	//vector(dot, lightFront, vec1);
	//vector(dot, middleBack, vec2);
	//crossProduct(vec1, vec2, lightState);

	//cout << lightState[0] << ", " << lightState[1] << ", " << lightState[2] << endl;

	//vector(dot, middleBack, vec1);	// 왼쪽
	//vector(dot, leftFront, vec2);	// 오른쪽
	//crossProduct(vec1, vec2, leftState);

	//cout << leftState[0] << ", " << leftState[1] << ", " << leftState[2] << endl;

	//vector(leftFront, middleBack, vec1);
	//vector(leftFront, lightFront, vec2);
	//crossProduct(vec1, vec2, floor);

	//cout << floor[0] << ", " << floor[1] << ", " << floor[2] << endl;

	float pointA[3];
	float pointB[3];
	float pointC[3];

	float vecA[3];
	float vecB[3];

	float sum[3];

	cin >> pointA[0] >> pointA[1] >> pointA[2];
	cin >> pointB[0] >> pointB[1] >> pointB[2];
	cin >> pointC[0] >> pointC[1] >> pointC[2];

	vector(pointA, pointB, vecA);
	vector(pointA, pointC, vecB);
	crossProduct(vecA, vecB, sum);

	printf("%.1f, %.1f, %.1f", sum[0], sum[1], sum[2]);


	return 0;
}