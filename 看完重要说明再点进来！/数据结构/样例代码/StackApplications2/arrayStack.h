
typedef struct {
	int key;
}element;

typedef struct {
	element *buffer;  // ��̬����
	int capacity; // ���������
	int top;  // ջ������λ��
} stack;

// �½�һ������Ϊcapacity���������洢��ջ
stack aCreate(int capacity );
// �ж϶�ջ�Ƿ�Ϊ�������Ϊ�շ���-1�����򷵻�0
int aIsFull(stack s);
// �ж϶�ջ�Ƿ�Ϊ�գ����Ϊ�շ���-1�����򷵻�0
int aIsEmpty(stack s);
// ��ջ
void apush(stack *s, element item);
// ��ջ
element apop(stack *s);