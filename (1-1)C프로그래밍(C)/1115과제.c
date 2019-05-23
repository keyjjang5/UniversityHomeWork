#include <stdio.h>

int check(char checkc[20], char str[20]);
char change(char bchar);

//int firstQ()
//{
//	//1. 암호를 입력받고 그 암호가 안전한지 테스트 한다 숫자, 소문자 대문자 필요
//	char password[20];
//
//
//	
//	while (1)
//	{
//		int check[3] = {0, 0, 0};
//
//		printf("암호를 입력하세요");
//		scanf(" %s", password);
//		printf(" %s", password);
//		
//
//		for(int i = 0; i < strlen(password) - 1; i++)
//		{
//			if ('a' <= password[i] && 'z' >= password[i])
//			{
//				
//				check[0] = 1;
//			}
//			else if ('A' <= password[i] && 'Z' >= password[i])
//			{
//				
//				check[1] = 1;
//			}
//			else if ('0' <= password[i] && '9' >= password[i])
//			{
//			
//				check[2] = 1;
//			}
//		}
//	
//		if (check[0] == 1 && check[1] == 1 && check[2] == 1)
//		{
//			printf("비밀번호가 안전합니다");
//			break;
//		}
//		else
//		{
//			printf("비밀번호가 안전하지 않습니다.");
//			continue;
//		}
//	}
//
//	return 0;
//}

//int main()
//{
//	//3. 문자열 안에 포함된 문자들의 출현 횟수를 계산한다.
//	//목적 : 문자열안 에 나타난 문자들만 뽑아서 출현 횟수를 계산한다.
//	//어떻게 해야하는가?
//	//1. 문자열에 나타난 문자들의 종류를 알아낸다.
//	//2. 각 문자들이 몇번 나타났는지 계산한다.
//	//3. 그것을 화면에 출력한다.
//	char str[20];  //문자열
//	char checkc[20]; //어떤 문자가 들어갔는지 체크함
//	int checki[20];
//	
//
//	printf("문자열을 입력해주세요");
//	scanf_s(" %s", str, strlen(str));
//
//	for (int i = 0; i < strlen(checki); i++)
//	{
//		checki[i] = 0;
//	}
//
//	int check(checkc, str);
//	
//	
//
//	return 0;
//}
//
//int check(char checkc[20], char str[20])
//{
//	static int k = 0;
//	int checki[20];
//
//
//	for (int i = 0; i < 20; i++)
//	{
//		for (k = 0; k < 20; k++)
//		{
//			if (checkc[k] != str[i])
//			{
//				checkc[k] = str[i];
//			}
//		}
//		for (int j = 0; j < 19; j++)
//		{
//			if (checkc[j] == str[i])
//			{
//				checki[j]++;
//			}
//			break;
//		}
//	}
//	
//	for (int i = 0; i < strlen(checkc); i++)
//	{
//		printf("%c문자가 %d번 등장!", checkc[i], checki[i]);
//	}
//
//}

//int main()
//{
//	char text[50];
//
//	printf("텍스트를 입력하십시오");
//	gets(text);
//
//	printf("%s\n", text);
//	for (int i = 0; i < strlen(text); i++)
//	{
//		if (text[i] == ' ' && text[i+1] == ' ')
//		{
//			
//		}
//		else
//		{
//			printf("%c", text[i]);
//		}
//	}
//
//	return 0;
//}

//int main()
//{
//	char text[50];
//
//	printf("입력하십시오");
//	gets(text);
//
//	for (int i = strlen(text); i > 0; i--)
//	{
//		printf("%c", text[i]);
//	}
//
//	return 0;
//}

//int main()
//{
//	char text[50];
//
//	printf("입력하시오");
//	gets(text);
//
//	for (int i = 0; i < strlen(text); i++)
//	{
//		if (text[i] >= 'A' && text[i] <= 'Z')
//		{
//			text[i] = change(text[i]);
//		}
//	}
//
//	printf("%s", text);
//
//	return 0;
//}
//
//char change(char bchar)
//{
//	bchar = bchar - ('A' - 'a');
//
//	return bchar;
//}

//int main()
//{
//	char text[50];
//	int check = 1;
//
//	printf("입력하시오");
//	gets(text);
//
//	for (int i = 0; i < strlen(text); i++)
//	{
//		if (text[i] == ' ' || text[i] == NULL)
//		{
//			check++;
//		}
//	}
//
//	printf("단어의 개수는 %d개이다.", check);
//
//	return 0;
//}

//int main()
//{
//	char text;
//
//	printf("문자를 입력하시오");
//	scanf("%c", &text);
//
//	printf("문자의 아스키 코드는 %d이다.", text);
//
//	return 0;
//}

//int main()
//{
//		char text[50];
//	
//		printf("텍스트를 입력하십시오");
//		gets(text);
//	
//		printf("%s\n", text);
//		for (int i = 0; i < strlen(text); i++)
//		{
//			if (text[i] == ' ')
//			{
//				
//			}
//			else
//			{
//				printf("%c", text[i]);
//			}
//		}
//	
//		return 0;
//}