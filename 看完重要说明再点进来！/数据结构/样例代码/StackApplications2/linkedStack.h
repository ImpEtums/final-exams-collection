
#define MAX_STACKS 10
typedef struct {
	int key;
}element;
typedef struct stack *stackPointer;
typedef struct stack {
	element data;
	stackPointer link;
};

// �½���һ��ͷ���ĵ�����
stackPointer Create();
// �ж϶�ջ�Ƿ�Ϊ�������Ϊ�շ���-1�����򷵻�0
int IsFull(stackPointer top);
// �ж϶�ջ�Ƿ�Ϊ�գ����Ϊ�շ���-1�����򷵻�0
int IsEmpty(stackPointer top);
// ��ջ
void push(stackPointer top, element item);
// ��ջ
element pop(stackPointer top);

