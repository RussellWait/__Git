/*************************************************************/
/* �ó����ж����������Ƿ���ͨ
/* ���δ��ͨ����֮ͨ���Ѿ���ͨ����ʾ������֮��ͨ�ĵ�
/* ��������Ϊ�ýڵ�����Ӧ���ڵ�
/*************************************************************/

#include <stdio.h>

#define MAX_SIZE 1000


int main(void)
{
	int array[MAX_SIZE];
	int useSize, num1, num2, i, j;

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

		for (i = num1; i != array[i]; i = array[i]);
		for (j = num2; j != array[j]; j = array[j]);

		if (i == j)
		{
			printf("�Ѿ�����\n");
		}
		else
		{
			array[i] = j;
			printf("���ӣ� %d %d\n", num1, num2);
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
