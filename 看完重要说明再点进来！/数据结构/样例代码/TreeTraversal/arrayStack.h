#include "BinaryTree.h"

typedef treePointer element;

// ������һ����ջ�Ľṹ��
typedef struct {
	element *buffer;  // ������Ԫ�ص�����
	int capacity;     // ���������
	int top;          // ��ջջ����λ��
} stack;

stack Create(int capacity); // ��ʼ����ջ
int IsFull(stack s);  // �жϵ�i�������Ƿ�Ϊ��
int IsEmpty(stack s); // �жϵ�i�������Ƿ�Ϊ��
element Pop(stack *s);
void Push(stack *s, element item);
