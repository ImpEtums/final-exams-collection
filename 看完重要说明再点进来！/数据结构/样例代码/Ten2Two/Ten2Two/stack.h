#pragma once

#ifndef __STACK__
#define __STACK__

#define MAX_STACKS 10
typedef struct{
	int key;
}element;
typedef struct stack *stackPointer;
typedef struct stack{
	element data;
	stackPointer link;
};

//�½���i����ջ������ö�ջ�ǿգ���Ҫ��ոö�ջ
void Create(int i);
//�жϵ�i����ջ�Ƿ�Ϊ��
int IsFull(int i);
//��Ԫ��item���i����ջ
void Push(int i, element item);
//�жϵ�i����ջ�Ƿ�Ϊ��
int IsEmpty(int i);
//�ӵ�i����ջ��ջ
element Pop(int i);

#endif
