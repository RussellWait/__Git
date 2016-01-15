/*************************************************************/
/* �ó����ж����������Ƿ���ͨ�����δ��ͨ����֮ͨ
/* parents��������Ϊ�ýڵ�����Ӧ���ڵ�
/*************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000


int main(void)
{
	int parents[MAX_SIZE];
	int usingSize, id1, id2, i, j;

	for (i = 0; i < MAX_SIZE; i++)
	{
		parents[i] = i;
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
			parents[i] = j;
			printf("���ӣ� %d %d\n", id1, id2);
		}

		printf("------parents: (");
		for (i = 0; i < usingSize; i++)
		{
			printf(" %d", parents[i]);
		}
		printf(" )\n\n");
	}

	return 0;
}
