/************************************************************************/
/* ��C����ע�ᵽlua�й������                                                                     */
/************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#ifdef __cplusplus
}
#endif // __cplusplus


// lua���õ�C����ԭ��
typedef int (*CFunction)(lua_State *L);

// ע�ᵽlua�ĺ�����
const static char *lFunctionNames[] = 
{
	"RFunction_Sin",
	"RFunction_Cos",
	"RFunction_Add",
};


// ע�ắ��
void CFunction_Register(lua_State *L);

// ����LFunctions.lua�еĺ���
void CFunction_Foo1(lua_State *L, double a, double b, double *c, double *d);
void CFunction_Foo2(lua_State *L, double a, double b, double *c);
