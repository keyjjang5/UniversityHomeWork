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
	//cout << "ť�� ������ 5���� ������ �Է��϶�>> ";
	//for (int i = 0; i < 5; i++) {
	//	cin >> n;
	//	mQ.enqueue(n); // ť�� ���� 
	//}
	//cout << "ť�� �뷮: " << mQ.capacity() << ", ť�� ũ��: " << mQ.length() << endl;
	//cout << "ť�� ���Ҹ� ������� �����Ͽ� ����Ѵ�>> ";
	//while (mQ.length() != 0) {
	//	cout << mQ.dequeue() << ' '; // ť���� �����Ͽ� ��� 
	//}
	//cout << endl << "ť�� ���� ũ��: " << mQ.length() << endl;
	//8-5��

	/*InkJetPrinter inkJet("Office V40", "HP", 5, 10);
	LaserPrinter laser("SCX-6x45", "�Ｚ����", 3, 20);

	cout << "���� �۵����� 2���� �����ʹ� �Ʒ��� ����" << endl;
	cout << "��ũ�� : ";
	inkJet.InkJetDataShow();

	cout << "������ : ";
	laser.laserDataShow();

	int choice;
	int pages;
	char yorn;
	do
	{
		cout << "������(1:��ũ��, 2:������)�� �ż� �Է�) >>";
		cin >> choice >> pages;

		if (choice == 1)
		{
			if (inkJet.printInkJet(pages))
				cout << "����Ʈ �Ͽ����ϴ�" << endl;
			else
				cout << "����Ʈ �� �� �����ϴ�" << endl;
		}
		else if (choice == 2)
		{
			if (laser.printLaser(pages))
				cout << "����Ʈ �Ͽ����ϴ�" << endl;
			else
				cout << "����Ʈ �� �� �����ϴ�" << endl;
		}
		inkJet.InkJetDataShow();
		laser.laserDataShow();

		cout << "��� ����Ʈ �Ͻðڽ��ϱ�(y/n)";
		cin >> yorn;
	} while (yorn == 'y');*/
	//8-8��

	/*int first = 0;
	int second = 0;
	Airport airport(7, 12, 17);
	int seat = -1;
	string name;

	cout << "*** �Ѽ��װ��� ���Ű��� ȯ���մϴ� ***" << endl << endl;
	cout << "*** �¼���ȣ�� 0~7�Դϴ�. ***" << endl << endl;
	while (1)
	{
		cout << "���� : 0, ��� : 1, ���� : 2, ������ : 3  >>" << endl;
		cin >> first;
		switch (first)
		{
		case(0):
			cout << "7�� : 0, 12�� : 1, 17�� : 2 >> ";
			cin >> second;

			airport.printAt(second);
			cout << "�¼� ��ȣ >>";
			cin >> seat;
			cout << "�̸� �Է� >>";
			cin >> name;

			airport.reservationManage(second, seat, name);
			break;
		case(1):
			cout << "7�� : 0, 12�� : 1, 17�� : 2 >> ";
			cin >> second;

			airport.printAt(second);
			cout << "�¼� ��ȣ >>";
			cin >> seat;
			cout << "�̸� �Է� >>";
			cin >> name;

			airport.cancelManage(second, seat, name);
			break;
		case(2):
			airport.printAll();
			break;
		case(3):exit(0);
		}
	}*/
	//8-9��
}