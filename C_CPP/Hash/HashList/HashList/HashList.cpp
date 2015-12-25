#include "HashList.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

STRUCT_INSTANCE(Node)
{
	char		*m_key;
	Value		*m_value;
	Node		*m_next;
};

const static int HASH_SIZE = 101;
static Node *hashTab[HASH_SIZE];


void HashList_initHashTab()
{
	for (int i = 0; i < HASH_SIZE; i++)
	{
		hashTab[i] = nullptr;
	}
}

unsigned int HashList_hashFunc(char *key)
{
	unsigned int h = 0;
	for (; *key; key++)
	{
		h = *key + h*31;
	}

	return h % HASH_SIZE;
}

Node *HashList_getNode(char *key)
{
	unsigned int hi = HashList_hashFunc(key);
	Node *np = hashTab[hi];
	for (; np; np = np->m_next)
	{
		if (!strcmp(np->m_key, key))
		{
			return np;
		}
	}

	return nullptr;
}

Value *HashList_get(char *key)
{
	Node *n = HashList_getNode(key);
	return n ? n->m_value : nullptr;
}

int HashList_install(char *key, Value *value)
{
	Node *np = HashList_getNode(key);
	if (!np)
	{
		unsigned int hi = HashList_hashFunc(key);
		np = (Node *)malloc(sizeof(Node));
		if (np)
		{
			np->m_key = key;
			np->m_next = hashTab[hi];
			hashTab[hi] = np;
		}
		else
		{
			return 0;
		}
	}
	np->m_value = value;

	return 1;
}

Value *HashList_delete(char *key)
{
	Node *delN = HashList_getNode(key);
	if (delN)
	{
		Value *ret = delN->m_value;
		Node *nexN = delN->m_next;
		free(delN);

		unsigned int hi = HashList_hashFunc(key);
		Node *preN = hashTab[hi];

		if (preN == delN)
		{
			hashTab[hi] = nexN;
			return ret;
		}
		else
		{
			while (preN)
			{
				if (preN->m_next == delN)
				{
					preN->m_next = nexN;
					return ret;
				}
				preN = preN->m_next;
			}
		}
	}

	return nullptr;
}

void HashList_display(PrintV printV)
{
	for (int i = 0; i < HASH_SIZE; i++)
	{
		Node *node = hashTab[i];
		if (node)
		{
			printf("<");
			for (; node; node = node->m_next)
			{
				printf("(%s, ", node->m_key);
				printV(node->m_value);
				printf(") ");
			}
			printf(">, ");
		}
		else
		{
			printf("<>, ");
		}
	}
	printf("\n");
}

void HashList_cleanUp()
{
	for (int i = 0; i < HASH_SIZE; i++)
	{
		Node *node = hashTab[i];
		if (node)
		{
			while (node)
			{
				Node *tNode = node;
				node = node->m_next;
				free(tNode);
			}
		}
	}
}
