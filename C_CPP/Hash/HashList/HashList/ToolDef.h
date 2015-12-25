#ifndef __TOOL_DEF_H__


#define VALUE_STATEMENT(NAME)		\
	typedef void NAME;


#define STRUCT_STATEMENT(NAME)		\
	struct _NAME;					\
	typedef struct _NAME NAME;

#define STRUCT_INSTANCE(NAME)		\
	struct _NAME

#endif // !__TOOL_DEF_H__
