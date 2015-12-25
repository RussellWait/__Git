#ifndef __HASH_LIST_H__


#include "ToolDef.h"


STRUCT_STATEMENT(Node)

VALUE_STATEMENT(Value)

typedef void (*PrintV)(Value *);


void HashList_initHashTab();

Value *HashList_get(char *key);

int HashList_install(char *key, Value *value);

Value *HashList_delete(char *key);

void HashList_display(PrintV printV);

void HashList_cleanUp();


#endif // !__HASH_LIST_H__
