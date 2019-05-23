#include <iostream>
#include <string>
#include "BaseArray.h"
#include "Printer.h"
#include "Airplane.h"

using namespace std;

void main()
{
	//MyQueue mQ(100);
	//int n;
	//cout << "큐에 삽입할 5개의 정수를 입력하라>> ";
	//for (int i = 0; i < 5; i++) {
	//	cin >> n;
	//	mQ.enqueue(n); // 큐에 삽입 
	//}
	//cout << "큐의 용량: " << mQ.capacity() << ", 큐의 크기: " << mQ.length() << endl;
	//cout << "큐의 원소를 순서대로 제거하여 출력한다>> ";
	//while (mQ.length() != 0) {
	//	cout << mQ.dequeue() << ' '; // 큐에서 제거하여 출력 
	//}
	//cout << endl << "큐의 현재 크기: " << mQ.length() << endl;
	//8-5번

	/*InkJetPrinter inkJet("Office V40", "HP", 5, 10);
	LaserPrinter laser("SCX-6x45", "삼성전자", 3, 20);

	cout << "현재 작동중인 2대의 프린터는 아래와 같다" << endl;
	cout << "잉크젯 : ";
	inkJet.InkJetDataShow();

	cout << "레이저 : ";
	laser.laserDataShow();

	int choice;
	int pages;
	char yorn;
	do
	{
		cout << "프린터(1:잉크젯, 2:레이저)와 매수 입력) >>";
		cin >> choice >> pages;

		if (choice == 1)
		{
			if (inkJet.printInkJet(pages))
				cout << "프린트 하였습니다" << endl;
			else
				cout << "프린트 할 수 없습니다" << endl;
		}
		else if (choice == 2)
		{
			if (laser.printLaser(pages))
				cout << "프린트 하였습니다" << endl;
			else
				cout << "프린트 할 수 없습니다" << endl;
		}
		inkJet.InkJetDataShow();
		laser.laserDataShow();

		cout << "계속 프린트 하시겠습니까(y/n)";
		cin >> yorn;
	} while (yorn == 'y');*/
	//8-8번

	/*int first = 0;
	int second = 0;
	Airport airport(7, 12, 17);
	int seat = -1;
	string name;

	cout << "*** 한성항공에 오신것을 환영합니다 ***" << endl << endl;
	cout << "*** 좌석번호는 0~7입니다. ***" << endl << endl;
	while (1)
	{
		cout << "예약 : 0, 취소 : 1, 보기 : 2, 끝내기 : 3  >>" << endl;
		cin >> first;
		switch (first)
		{
		case(0):
			cout << "7시 : 0, 12시 : 1, 17시 : 2 >> ";
			cin >> second;

			airport.printAt(second);
			cout << "좌석 번호 >>";
			cin >> seat;
			cout << "이름 입력 >>";
			cin >> name;

			airport.reservationManage(second, seat, name);
			break;
		case(1):
			cout << "7시 : 0, 12시 : 1, 17시 : 2 >> ";
			cin >> second;

			airport.printAt(second);
			cout << "좌석 번호 >>";
			cin >> seat;
			cout << "이름 입력 >>";
			cin >> name;

			airport.cancelManage(second, seat, name);
			break;
		case(2):
			airport.printAll();
			break;
		case(3):exit(0);
		}
	}*/
	//8-9번
}