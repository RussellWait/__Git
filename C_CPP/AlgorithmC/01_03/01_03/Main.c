/*************************************************************/
/* 该程序判断输入两点是否联通，如果未联通则联通之
/* parents数组内容为该节点所对应父节点
/* childrenCount数组为该节点拥有子节点数（包括自身）
/*************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000


int main(void)
{
	int parents[MAX_SIZE], childrenCount[MAX_SIZE];
	int usingSize, id1, id2, i, j;

	for (i = 0; i < MAX_SIZE; i++)
	{
		parents[i] = i;
		childrenCount[i] = 1;
	}

	printf("请输入连接点范围：");
	scanf("%d", &usingSize);
	if (usingSize <= 0 || usingSize >= MAX_SIZE)
	{
		exit(0);
	}

	while (2 == scanf("%d %d", &id1, &id2))
	{
		if (id1 < 0 || id1 >= usingSize || id2 < 0 || id2 >= usingSize)
		{
			exit(0);
		}

		for (i = id1; i != parents[i]; i = parents[i]);
		for (j = id2; j != parents[j]; j = parents[j]);

		if (i == j)
		{
			printf("已经连接\n");
		}
		else
		{
			if (childrenCount[i] < childrenCount[j])
			{
				parents[i] = j;
				childrenCount[j] += childrenCount[i];
			}
			else
			{
				parents[j] = i;
				childrenCount[i] += childrenCount[j];
			}

			printf("连接： %d %d\n", id1, id2);
		}

		printf("------parents: (");
		for (i = 0; i < usingSize; i++)
		{
			printf(" %d", parents[i]);
		}
		printf(" )\n");
		printf("------childrenCount: (");
		for (i = 0; i < usingSize; i++)
		{
			printf(" %d", childrenCount[i]);
		}
		printf(" )\n\n");
	}

	return 0;
}
