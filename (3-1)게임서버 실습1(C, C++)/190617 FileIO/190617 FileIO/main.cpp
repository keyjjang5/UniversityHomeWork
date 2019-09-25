#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readData()
{
	FILE *fp;

	fp = fopen("UserData.txt", "a");
	fprintf(fp, "test 1324\n");

	fclose(fp);

	fp = fopen("UserData.txt", "r");

	int input = NULL;
	int count = 0;
	int number = 0;


	// 로그인 확인용 데이터
	// int userNumber[10];
	string userId[10];
	string userPass[10];

	char tempId[20];
	char tempPass[20];

	while (input = fgetc(fp) != EOF)
	{
		// 파일에서 아이디 번호 뽑아내기
		/*input = fgetc(fp);

		userNumber[number] = input;*/

		// 파일에서 유저 아이디 뽑아내기
		tempId[count] = input;
		while (1)
		{
			if (input = fgetc(fp) == ' ')
			{
				++count;
				tempId[count] = '\0';
				break;
			}
			++count;

			tempId[count] = input;
			printf("input : %c\n", input);
		}
		count = 0;

		// 파일에서 유저 패스워드 뽑아내기
		tempPass[count] = input;
		while (1)
		{
			if (input = fgetc(fp) == '\n')
			{
				++count;

				tempPass[count] = '\0';
				break;
			}
			++count;

			tempPass[count] = input;
		}
		count = 0;
		if (input == '\n')
		{
			userId[number] = tempId;
			userPass[number] = tempPass;
			++number;
		}
	}

	fclose(fp);


	for (int i = 0; i < number; i++)
	{
		printf("User ID : %s\nUser PassWord : %s\n", userId[i], userPass[i]);
	}

	return;
}

void readData2()
{
	bool done = false;
	ifstream fin;
	char input;
	char filename[20] = "UserData.txt";

	int count = 0;
	int number = 0;


	// 로그인 확인용 데이터
	// int userNumber[10];
	string userId[10];
	string userPass[10];

	char tempId[20];
	char tempPass[20];


	fin.open(filename);
	if (fin.good())
	{
		done = true;
	}
	else
	{
		// If the file does not exist or there was an issue opening it then notify the user and repeat the process.
		fin.clear();
		cout << endl;
		cout << "File " << filename << " could not be opened." << endl << endl;
	}

	fin.close();

	fin.open(filename);
	if (fin.fail() == true)
	{
		return;
	}

	fin.get(input);
	while (!fin.eof())
	{
		tempId[count] = input;
		printf("input : %c\n", input);
		while (1)
		{
			fin.get(input);
			if (input == ' ')
			{
				++count;
				tempId[count] = '\0';
				break;
			}
			++count;

			tempId[count] = input;
			printf("input : %c\n", input);
		}
		count = 0;

		// 파일에서 유저 패스워드 뽑아내기
		fin.get(input);
		tempPass[count] = input;
		printf("input : %c\n", input);
		while (1)
		{
			fin.get(input);
			if (input == '\n')
			{
				++count;

				tempPass[count] = '\0';
				break;
			}
			++count;

			tempPass[count] = input;
			printf("input : %c\n", input);
		}
		count = 0;
		if (input == '\n')
		{
			userId[number].clear();
			userId[number].append(tempId);
			userPass[number].clear();
			userPass[number].append(tempPass);

			cout << "userId : " << userId[number] << endl;
			cout << "userPass : " << userPass[number] << endl;

			++number;
		}

		fin.get(input);
	}
}

int main()
{
	FILE *fp;

	int index;
	int data;

	fp = fopen("Log.txt", "a");

	fprintf(fp, "로그 제작중..\n");

	fclose(fp);

	
	readData2();

	return 0;

}