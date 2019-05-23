#include <iostream>
#include <string>
#include "MyVector.h"
#include "ArrayUtility2.h"
#include "Trace.h"

using namespace std;

void f() 
{
	int a, b, c;
	cout << "두 개의 정수를 입력하세요>>";
	cin >> a >> b;
	Trace::put("f()", "정수를 입력받았음"); // 디버깅 정보 저장 
	c = a + b;
	Trace::put("f()", "합 계산"); // 디버깅 정보 저장 
	cout << "합은 " << c << endl;
}

int main()
{
	//MyVector normal;
	//MyVector special(10, 5);

	//normal.getMember();//size와 mem을 꺼내오는 함수
	//special.getMember();

	/*int x[5];
	int y[5];
	int* returnValue;
	cout << "정수를 5 개 입력하라. 배열 x에 삽입한다 >>";
	for (int i = 0; i < 5; i++)
	{
		cin >> x[i];
	}
	cout << "정수를 5 개 입력하라. 배열 y에 삽입한다 >>";
	for (int i = 0; i < 5; i++)
	{
		cin >> y[i];
	}
	cout << "합친 정수 배열을 출력한다." << endl;
	returnValue = ArrayUtility2::concat(x, y, (sizeof(x) + sizeof(y)/4));
	for (int i = 0; i < (sizeof(x) + sizeof(y)+1)/4; i++)
		cout << returnValue[i] << " ";
	delete returnValue;
	cout << "배열 x[]에서 y[]를 뺸 결과를 출력한다" << "개수는 ";
	int retSize;
	returnValue = ArrayUtility2::remove(x, y, (sizeof(x) + sizeof(y)+1)/4, retSize);
	cout << retSize << endl;
	for (int i = 0; i < retSize; i++)
		cout << returnValue[i] << " ";
	delete returnValue;*/

	Trace::put("main()", "프로그램 시작합니다"); // 디버깅 정보 저장 
	f();
	Trace::put("main()", "종료"); // put()의 첫번째 매개 변수는 태그이고 두번째 매개변수는 디버깅 정보이다. 
	Trace::print("f()"); // "f()" 태그를 가진 디버깅 정보를 모두 출력한다. 
	Trace::print(); // 모든 디버깅 정보를 출력한다. 

	return 0;
}