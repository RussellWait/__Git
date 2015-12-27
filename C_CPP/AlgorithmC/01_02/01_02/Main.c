/*************************************************************/
/* 该程序判断输入两点是否联通
/* 如果未联通则联通之，已经连通则提示所有与之联通的点
/* 数组内容为该节点所对应父节点
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

	printf("请输入连接点范围：");
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
			printf("已经连接\n");
		}
		else
		{
			array[i] = j;
			printf("连接： %d %d\n", num1, num2);
		}

		printf("------数组内容:(");
		for (i = 0; i < useSize; i++)
		{
			printf(" %d", array[i]);
		}
		printf(" )\n\n");
	}

	return 0;
}
