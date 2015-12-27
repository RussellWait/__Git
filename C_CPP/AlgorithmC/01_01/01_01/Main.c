/*************************************************************/
/* 该程序判断输入两点是否联通
/* 如果未联通则联通之，已经连通则提示所有与之联通的点
/* 数组内容相同的节点表示连通
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

	printf("请输入连接点范围：");
	scanf("%d", &useSize);

	while (2 == scanf("%d %d", &num1, &num2))
	{
		if (num1 < 0 || num1 > useSize || num2 < 0 || num2 > useSize)
		{
			break;
		}

		if (array[num1] == array[num2])
		{
			printf("已经连接");
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
			printf("连接 %d %d\n", num1, num2);
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
