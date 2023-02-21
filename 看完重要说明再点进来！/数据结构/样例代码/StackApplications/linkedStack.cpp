#include "linkedStack.h"
#include <stdlib.h>
#include <stdio.h>
// �½���һ��ͷ���ĵ�����stack)
stackPointer Create(void )
{
	stackPointer top = NULL;
	// ����ͷ���
	top = (stackPointer)malloc(sizeof(stack));
	top->link = NULL;
	return top;
}
// �ж϶�ջ�Ƿ�Ϊ�������Ϊ�շ���-1�����򷵻�0
int IsFull(stackPointer top)
{
	return 0;
}
// �ж϶�ջ�Ƿ�Ϊ�գ����Ϊ�շ���-1�����򷵻�0
int IsEmpty(stackPointer top)
{
	return top->link==NULL;
}
// ��ջ
void push(stackPointer top, element item)
{
	stackPointer temp;
	temp = (stackPointer)malloc(sizeof(*temp));
	temp->data = item;
	temp->link = top->link;
	top->link = temp;
}

element stackEmpty()
{
	printf("ERROR: stack is empty.");
	exit(0);
}

// ��ջ
element pop(stackPointer top)
{
	stackPointer temp = top->link;
	element item;
	if (!temp)
		return stackEmpty();
	item = temp->data;
	top->link = temp->link;
	free(temp);
	return item;
}

