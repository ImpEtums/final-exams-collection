#include<stdio.h>
#include<string.h>

// �ڴ����
const int FrameCount = 3;
// ҳ��
const int PageCount = 20;
// ҳ������ֵ + 1
const int PageMax = 8;
// һ���Ƚϴ��ֵ
const int INF = 0x3f3f3f3f;
// �Ƿ����ڴ����
bool isInframe[PageMax];
// ����ȱҳ����
int lost;
// �ڴ��ռ�����
int Frame[FrameCount];

int Page[] = { 1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6 };

// ����Ϊ������
int temp[FrameCount][PageCount + 10];
void Output(int type) {
	if (type == 1)printf("The result of FIFO:\n");
	else if (type == 2)printf("The result of OPT:\n");
	else printf("The result of LRU:\n");
	char s[FrameCount][(PageCount + 10) * 2];
	char p[(PageCount + 10) * 2];
	for (int i = 0; i < PageCount; ++i) 
	{
		for (int j = 0; j < FrameCount; ++j)
		{
			if (i == 0) {
				if (temp[j][i] == 0)s[j][i * 2] = ' ';
				else s[j][i * 2] = temp[j][i] + '0';
				s[j][i * 2 + 1] = '|';
			}
			else {
				if (temp[j][i] == 0 || temp[j][i] == temp[j][i - 1])s[j][i * 2] = ' ';
				else s[j][i * 2] = temp[j][i] + '0';
				s[j][i * 2 + 1] = '|';
			}
		}
		p[i * 2] = Page[i] + '0';
		p[i * 2 + 1] = '|';
	}
	p[PageCount * 2] = '\0';
	for (int i = 0; i < FrameCount; ++i)s[i][PageCount * 2] = '\0';
	printf("P: %s\n", p);
	for (int i = 0; i < FrameCount; ++i) {
		printf("%c: %s\n", i + 'A', s[i]);
	}
	printf("Accessing %d pages, page faults %d times, page-fault rate is %.2f\n\n", PageCount, lost, lost * 1.0 / PageCount * 100);
}

//����Ϊ�㷨����
void FIFO() {
	// ��ʼ��
	// Frame	��Ϊ0     ��ʾ�����ڴ�鶼Ϊ��
	// isInpage ��Ϊfalse ��ʾ����ҳ��δ�����ڴ��
	// lostһ��ʼΪ0����ȱҳ������0
	lost = 0;
	memset(Frame, 0, sizeof(Frame));
	memset(isInframe, 0, sizeof(isInframe));
	memset(temp, 0, sizeof(temp));
	// ָ��, ��ʾFIFO��ָ��浽����
	int point = 0;
	// �������
	for (int i = 0; i < PageCount; ++i) 
	{
		if (isInframe[Page[i]] == false)
		{
			//***************************�����ﲹ���㷨****************************
		}
		/****������****/
		for (int j = 0; j < FrameCount; ++j) 
		{
			temp[j][i] = Frame[j];
		}
		/***************/
	}
	// ���
	Output(1);
}
void OPT() {
	// ��ʼ��
	// Frame	��Ϊ0     ��ʾ�����ڴ�鶼Ϊ��
	// isInpage ��Ϊfalse ��ʾ����ҳ��δ�����ڴ��
	lost = 0;
	memset(Frame, 0, sizeof(Frame));
	memset(isInframe, 0, sizeof(isInframe));
	memset(temp, 0, sizeof(temp));

	// �ж��ڴ���Ƿ񶼴�����
	int isFull = 0;

	// Ԥ����
	// nxt[i][j] ��ʾ �� j λ�õ�ҳ�� i ��һ�γ�������
	// pos[i]    ��ʾ ҳ�� i ��һ�γ�������, �粻����, ֵ�ó�INF
	int nxt[PageMax][PageCount];
	int pos[PageMax];
	memset(pos, INF, sizeof(pos));
	for (int i = PageCount - 1; i >= 0; --i) 
	{
		for (int j = 1; j < PageMax; ++j) 
		{
			nxt[j][i] = pos[j];
		}
		pos[Page[i]] = i;
	}
	// �������
	for (int i = 0; i < PageCount; ++i) 
	{
		// δ���ڴ����
		if (isInframe[Page[i]] == false) 
		{
			lost++;
			// �Ѵ���
			if (isFull == FrameCount)
			{
				// max_next ����ҳ����, ��һ�γ��ֵ�λ������ֵΪ����
				// number	����ҳ����, ��һ�γ��ֵ�λ�������Ǹ�ҳ����
				int max_next = 0, number;
				//***************************�����ﲹ���㷨****************************
				
				
			}
			// δ����
			else
			{
				isInframe[Page[i]] = true;
				Frame[isFull++] = Page[i];
			}
		}
		/****������****/
		for (int j = 0; j < FrameCount; ++j)
		{
			temp[j][i] = Frame[j];
		}
		/***************/
	}
	// ���
	Output(2);
}
void LRU() 
{
	// ��ʼ��
	// Frame	��Ϊ0     ��ʾ�����ڴ�鶼Ϊ��
	// isInpage ��Ϊfalse ��ʾ����ҳ��δ�����ڴ��
	lost = 0;
	memset(Frame, 0, sizeof(Frame));
	memset(isInframe, 0, sizeof(isInframe));
	memset(temp, 0, sizeof(temp));
	// �ж��ڴ���Ƿ񶼴�����
	int isFull = 0;

	// Ԥ����
	// pre[i][j] ��ʾ �� j λ�õ�ҳ�� i ǰһ��һ�γ�������
	// pos[i]    ��ʾ ҳ�� i ǰһ�γ�������, �粻����, ֵ�ó�INF
	int pre[PageMax][PageCount];
	int pos[PageMax];
	memset(pos, INF, sizeof(pos));
	for (int i = 0; i < PageCount; ++i)
	{
		for (int j = 1; j < PageMax; ++j)
		{
			pre[j][i] = pos[j];
		}
		pos[Page[i]] = i;
	}
	// �������
	for (int i = 0; i < PageCount; ++i)
	{
		// δ���ڴ����
		if (isInframe[Page[i]] == false)
		{
			lost++;
			// �Ѵ���
			if (isFull == FrameCount)
			{
				// min_pre ����ҳ����, ǰһ��һ�γ��ֵ�λ����С��ֵΪ����
				// number	����ҳ����, ǰһ��һ�γ��ֵ�λ����С���Ǹ�ҳ����
				int min_pre = INF + 1, number;
				//***************************�����ﲹ���㷨****************************
				
				
			}
			// δ����
			else
			{
				isInframe[Page[i]] = true;
				Frame[isFull++] = Page[i];
			}
		}
		/****������****/
		for (int j = 0; j < FrameCount; ++j)
		{
			temp[j][i] = Frame[j];
		}
		/***************/
	}
	// ���
	Output(3);
}

// ����������
int main() {
	int ty;
	printf("1:FIFO\n");
	printf("2:OPT\n");
	printf("3:LRU\n");
	printf("0:Quit\n");
	printf("input the type you choose:\n");
	while (scanf("%d", &ty), ty)
	{
		if(ty == 1)FIFO();
		else if(ty == 2)OPT();
		else LRU();
	}
}