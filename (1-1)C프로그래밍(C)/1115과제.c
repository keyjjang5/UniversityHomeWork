#include <stdio.h>

int check(char checkc[20], char str[20]);
char change(char bchar);

//int firstQ()
//{
//	//1. ��ȣ�� �Է¹ް� �� ��ȣ�� �������� �׽�Ʈ �Ѵ� ����, �ҹ��� �빮�� �ʿ�
//	char password[20];
//
//
//	
//	while (1)
//	{
//		int check[3] = {0, 0, 0};
//
//		printf("��ȣ�� �Է��ϼ���");
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
//			printf("��й�ȣ�� �����մϴ�");
//			break;
//		}
//		else
//		{
//			printf("��й�ȣ�� �������� �ʽ��ϴ�.");
//			continue;
//		}
//	}
//
//	return 0;
//}

//int main()
//{
//	//3. ���ڿ� �ȿ� ���Ե� ���ڵ��� ���� Ƚ���� ����Ѵ�.
//	//���� : ���ڿ��� �� ��Ÿ�� ���ڵ鸸 �̾Ƽ� ���� Ƚ���� ����Ѵ�.
//	//��� �ؾ��ϴ°�?
//	//1. ���ڿ��� ��Ÿ�� ���ڵ��� ������ �˾Ƴ���.
//	//2. �� ���ڵ��� ��� ��Ÿ������ ����Ѵ�.
//	//3. �װ��� ȭ�鿡 ����Ѵ�.
//	char str[20];  //���ڿ�
//	char checkc[20]; //� ���ڰ� ������ üũ��
//	int checki[20];
//	
//
//	printf("���ڿ��� �Է����ּ���");
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
//		printf("%c���ڰ� %d�� ����!", checkc[i], checki[i]);
//	}
//
//}

//int main()
//{
//	char text[50];
//
//	printf("�ؽ�Ʈ�� �Է��Ͻʽÿ�");
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
//	printf("�Է��Ͻʽÿ�");
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
//	printf("�Է��Ͻÿ�");
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
//	printf("�Է��Ͻÿ�");
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
//	printf("�ܾ��� ������ %d���̴�.", check);
//
//	return 0;
//}

//int main()
//{
//	char text;
//
//	printf("���ڸ� �Է��Ͻÿ�");
//	scanf("%c", &text);
//
//	printf("������ �ƽ�Ű �ڵ�� %d�̴�.", text);
//
//	return 0;
//}

//int main()
//{
//		char text[50];
//	
//		printf("�ؽ�Ʈ�� �Է��Ͻʽÿ�");
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