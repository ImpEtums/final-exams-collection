#include<iostream>
#include<stdlib.h>
using namespace std;

int counter = 0;
/***************** Parameter Setting *****************/
int const InsideCount = 3;//frames
int Inside[InsideCount];
int const PageCount = 20;//�ܵ�ҳ����
int Page[PageCount] = { 1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6 };

int insert = 0;//��used in FIFO
double lost = 0.0;

bool isInside(int num)//check whether the page is in memory or not
{
	for (int i = 0; i < InsideCount; i++)
	{
		if (Inside[i] == Page[num])
		{
			return true;
		}
	}
	return false;
}

void LRU(int num)
{
	int max = 0;   //��ʾ�ڴ��е�ҳ�ţ���һ�γ��ֵľ���
	int maxchange; //��ʾ�ڴ����´γ��־�������ҳ�����ڴ��е�λ��
	int k;
	if (isInside(num))
	{
		cout << "It is already in memory!" << endl;
		for (int i = 0; i <InsideCount; i++)
			cout << "Inside[" << i << "]:" << Inside[i] << endl;
	}
	else
		if (counter == InsideCount)
		{
			lost++;
			for (int j = 0; j < InsideCount; j++)
			{
				//�ӵ�ǰ��ҳ����ǰ��������ҳ�����ڴ��е�ҳ����ͬ��break ���Ƚ��ڴ�������ҳ�ţ�����һ���ߵ�Զ����max��¼
				//*****************************�����ﲹ���㷨*****************************************
				
				
				
			}
			Inside[maxchange] = Page[num];
			for (int i = 0; i <InsideCount; i++)
				cout << "Inside[" << i << "]:" << Inside[i] << endl;
		}
		else
		{
			Inside[counter] = Page[num];
			counter++;

			for (int i = 0; i <InsideCount; i++)
				cout << "Inside[" << i << "]:" << Inside[i] << endl;
		}
}

void FIFO(int num)
{
	if (isInside(num))
	{
		cout << "It is already in memory!" << endl;
		for (int i = 0; i <InsideCount; i++)
			cout << "Inside[" << i << "]:" << Inside[i] << endl;
	}
	else
		if (counter == InsideCount)
		{
		   //*****************************�����ﲹ���㷨*****************************************
			
			for (int i = 0; i <InsideCount; i++)
				cout << "Inside[" << i << "]:" << Inside[i] << endl;
		}
		else
		{
			Inside[counter] = Page[num];
			counter++;
			for (int i = 0; i <InsideCount; i++)
				cout << "Inside[" << i << "]:" << Inside[i] << endl;
		}
}

void MIN(int num)
{
	int max = 0; // ��ʾ�ڴ��е�ҳ�ţ���һ�γ��ֵľ���
	int maxchange; //��ʾ�ڴ����´γ��־�������ҳ�����ڴ��е�λ��
	int k;
	if (isInside(num))
	{
		cout << "It is already in memory!" << endl;
		for (int i = 0; i <InsideCount; i++)
			cout << "Inside[" << i << "]:" << Inside[i] << endl;
	}
	else
		if (counter == InsideCount)
		{
			lost++;
			for (int j = 0; j < InsideCount; j++)
			{
				//*****************************�����ﲹ���㷨*****************************************
				
				
				
			}
			
			
			for (int i = 0; i <InsideCount; i++)
				cout << "Inside[" << i << "]:" << Inside[i] << endl;
		}
		else
		{
			Inside[counter] = Page[num];
			counter++;
			for (int i = 0; i <InsideCount; i++)
				cout << "Inside[" << i << "]:" << Inside[i] << endl;
		}
}

int main()
{
	char ch;
	while (1)
	{
		cout << "M: MIN" << "\n" << endl;
		cout << "F: FIFO" << "\n" << endl;
		cout << "L: LRU" << "\n" << endl;
		cin >> ch;
		switch (ch)
		{
		case 'M':
		{
			lost = 0;
			counter = 0;
			for (int j = 0; j < InsideCount; j++)
			{
				Inside[j] = 0;
			}
			for (int i = 0; i < PageCount; i++)
			{
				cout << "Accessing Page[" << i << "]=" << Page[i] << endl;
				MIN(i);
			}
			cout << "Accessing " << PageCount << " pages, " << "page faults " << lost << " times, page-fault rate is " << lost / (PageCount) << "\n\n" << endl;
		}
		break;
		case 'F':
		{
			lost = 0;
			counter = 0;
			for (int j = 0; j < InsideCount; j++)
			{
				Inside[j] = 0;
			}
			for (int i = 0; i < PageCount; i++)
			{
				cout << "Accessing Page[" << i << "]=" << Page[i] << endl;
				FIFO(i);
			}
			cout << "Accessing " << PageCount << " pages, " << "page faults " << lost << " times, page-fault rate is " << lost / (PageCount) << "\n\n" << endl;
		}
		break;
		case 'L':
		{
			lost = 0;
			counter = 0;
			for (int j = 0; j < InsideCount; j++)
			{
				Inside[j] = 0;
			}
			for (int i = 0; i < PageCount; i++)
			{
				cout << "Accessing Page[" << i << "]=" << Page[i] << endl;
				LRU(i);
			}
			cout << "Accessing " << PageCount << " pages, " << "page faults " << lost << " times, page-fault rate is " << lost / (PageCount) << "\n\n" << endl;
		}
		break;
		}
	}
	return 0;
}
