
#include "stdafx.h"
#include "stack.h"
#include <stdlib.h>
#define MALLOC(p,s) \
	if(!((p)=(stackPointer)malloc(s))){ \
	fprintf(stderr, "Insufficient memory"); \
	exit(EXIT_FAILURE);\
	}
//�½���i����ջ������ö�ջ�ǿգ���Ҫ��ոö�ջ

extern stackPointer top[MAX_STACKS] ;

void Create(int i)
{
	top[i] = NULL;
	// todo
}
//�жϵ�i����ջ�Ƿ�Ϊ��
int IsFull(int i)
{
	return 0;
}
//��Ԫ��item���i����ջ
void Push(int i, element item)
{
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = top[i];
	top[i] = temp;
}
//�жϵ�i����ջ�Ƿ�Ϊ��
int IsEmpty(int i)
{
	return top[i]==NULL;
}
element stackEmpty()
{
	element item;
	item.key = -1;
	return item;
}
//�ӵ�i����ջ��ջ
element Pop(int i)
{
	stackPointer temp  = top[i];
	element item;
	if(!temp)
		return stackEmpty();
	item = temp->data;
	top[i] = temp->link;
	free(temp);
	return item;

}
