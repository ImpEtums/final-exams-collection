// Ten2Two.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include "stdafx.h"
#include "stack.h"

stackPointer top[MAX_STACKS]; 

void conversion(int decimal)
{
	int shang, yushu;
	element item;
	shang = decimal;

	// ��ջ��ʼ��
	Create(0);
	// �õ�ÿһ��������������ջ
	while(shang!=0){
		yushu = shang % 2;
		shang = shang / 2;
		item.key = yushu;
		Push(0,item);
	}
	printf("\nThe corresponding binary version is:");
	item = Pop(0);
	while(item.key>-1){
		printf("%d",item.key);
		item = Pop(0);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int decimal;

	printf("Please input the decimal number:");
	scanf_s("%d", &decimal);
	while(decimal >= 0){
		conversion(decimal);
		printf("\nPlease input the decimal number:");
		scanf_s("%d", &decimal);
	}

	return 0;
}

