/*************************************************************/
/* 该程序判断输入两点是否联通
/* 如果未联通则联通之，已经连通则提示所有与之联通的点
/* states数组中内容相同的节点之间表示连通
/*************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000


int main(void)
{
	int states[MAX_SIZE];
	int usingSize, id1, id2, temp, i;

	for (i = 0; i < MAX_SIZE; i++)
	{
		states[i] = i;
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

		if (states[id1] == states[id2])
		{
			printf("已经连接");
			for (i = 0; i < usingSize; i++)
			{
				if (states[i] == states[id1])
				{
					printf(" %d", i);
				}
			}
			printf("\n");
		}
		else
		{
			temp = states[id1];
			for (i = 0; i < usingSize; i++)
			{
				if (states[i] == temp)
				{
					states[i] = states[id2];
				}
			}
			printf("连接 %d %d\n", id1, id2);
		}

		printf("------states: (");
		for (i = 0; i < usingSize; i++)
		{
			printf(" %d", states[i]);
		}
		printf(" )\n\n");
	}

	return 0;
}
