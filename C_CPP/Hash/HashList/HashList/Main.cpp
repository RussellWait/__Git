#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "HashList.h"

VALUE_STATEMENT(SaveValue)
typedef char MyValue;

void printV(SaveValue *v)
{
	printf("%s", (MyValue *)v);
}


int main()
{
	char* names[]={"name","address","phone","k101","k110"};
	MyValue* descs[]={"Sourav","Sinagor","26300788","Value1","Value2"};

	HashList_initHashTab();
	
	int len = sizeof(names) / sizeof(names[0]);
	for (int i = 0; i < len; i++)
	{
		HashList_install(names[i], descs[i]);
	}
	HashList_display(printV);
	printf("================================\n\n");

	HashList_install("name", "newName");
	HashList_display(printV);
	printf("================================\n\n");

	printV(HashList_delete("k101"));
	printf("---------------\n");
	HashList_display(printV);
	printf("================================\n\n");

	HashList_install("abcdek", "test1");
	HashList_install("123464", "test2");
	HashList_install("26554", "test3");
	HashList_install("feuje", "test4");
	HashList_install("uefhuhafjdgh", "test5");
	HashList_display(printV);
	printf("================================\n\n");

	printV(HashList_delete("k101"));
	printf("---------------\n");
	printV(HashList_delete("26554"));
	printf("---------------\n");
	printV(HashList_delete("abcdek"));
	printf("---------------\n");
	printV(HashList_delete("feuje"));
	printf("---------------\n");
	HashList_display(printV);
	printf("================================\n\n");

	HashList_cleanUp();

	return 0;
}
