/*************************************************************/
/* �ó����ж����������Ƿ���ͨ�����δ��ͨ����֮ͨ
/* parents��������Ϊ�ýڵ�����Ӧ���ڵ�
/* childrenCount����Ϊ�ýڵ�ӵ���ӽڵ�������������
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

	printf("���������ӵ㷶Χ��");
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
			printf("�Ѿ�����\n");
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

			printf("���ӣ� %d %d\n", id1, id2);
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
