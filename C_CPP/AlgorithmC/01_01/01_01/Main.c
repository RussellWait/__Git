/*************************************************************/
/* �ó����ж����������Ƿ���ͨ
/* ���δ��ͨ����֮ͨ���Ѿ���ͨ����ʾ������֮��ͨ�ĵ�
/* ����������ͬ�Ľڵ��ʾ��ͨ
/*************************************************************/

#include <stdio.h>

#define MAX_SIZE 1000


int main(void)
{
	int array[MAX_SIZE];
	int useSize, num1, num2, temp, i;

	for (i = 0; i < MAX_SIZE; i++)
	{
		array[i] = i;
	}

	printf("���������ӵ㷶Χ��");
	scanf("%d", &useSize);

	while (2 == scanf("%d %d", &num1, &num2))
	{
		if (num1 < 0 || num1 > useSize || num2 < 0 || num2 > useSize)
		{
			break;
		}

		if (array[num1] == array[num2])
		{
			printf("�Ѿ�����");
			for (i = 0; i < useSize; i++)
			{
				if (array[i] == array[num1])
				{
					printf(" %d", i);
				}
			}
			printf("\n");
		}
		else
		{
			temp = array[num1];
			for (i = 0; i < useSize; i++)
			{
				if (array[i] == temp)
				{
					array[i] = array[num2];
				}
			}
			printf("���� %d %d\n", num1, num2);
		}

		printf("------��������:(");
		for (i = 0; i < useSize; i++)
		{
			printf(" %d", array[i]);
		}
		printf(" )\n\n");
	}

	return 0;
}
