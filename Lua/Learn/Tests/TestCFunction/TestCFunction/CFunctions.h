/************************************************************************/
/* 将C函数注册到lua中供其调用                                                                     */
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


// lua调用的C函数原型
typedef int (*CFunction)(lua_State *L);

// 注册到lua的函数名
const static char *lFunctionNames[] = 
{
	"RFunction_Sin",
	"RFunction_Cos",
	"RFunction_Add",
};


// 注册函数
void CFunction_Register(lua_State *L);

// 调用LFunctions.lua中的函数
void CFunction_Foo1(lua_State *L, double a, double b, double *c, double *d);
void CFunction_Foo2(lua_State *L, double a, double b, double *c);
