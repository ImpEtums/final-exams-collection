#include "arrayStack.h"
#include <stdlib.h>
#include <stdio.h>
// �½�һ������Ϊcapacity���������洢��ջ
stack aCreate(int capacity )
{
	stack s;
	s.buffer = (element *)malloc(sizeof(element)*capacity);
	s.capacity = capacity;
	s.top = -1;
	return s;
}
// �ж϶�ջ�Ƿ�Ϊ�������Ϊ�շ���-1�����򷵻�0
int aIsFull(stack s)
{
	return s.top == s.capacity-1;
}
// �ж϶�ջ�Ƿ�Ϊ�գ����Ϊ�շ���-1�����򷵻�0
int aIsEmpty(stack s)
{
	return s.top == -1;
}
void astackFull()
{
	printf("ERROR:stack is full");
	exit(0);
}
// ��ջ
void apush(stack *s, element item)
{
	if(!aIsFull(*s)){
		(*s).buffer[++(*s).top] = item;
	}
	else
		return astackFull();
}
element astackEmpty()
{
	printf("ERROR:stack is empty");
	exit(0);
}
// ��ջ
element apop(stack *s)
{
	element temp;
	if(!aIsEmpty(*s)){
		temp = (*s).buffer[(*s).top--];
		return temp;
	}
	else
		return astackEmpty();
}