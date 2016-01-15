/************************************************************************/
/* 创建C库供lua调用                                                                     */
/************************************************************************/

#pragma once

#include <stdio.h>

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


static int l_Hello(lua_State *L)
{
	printf("Hello Lua.\n");
	return 0;
}

static int l_Sub(lua_State *L)
{
	double a = luaL_checknumber(L, -2);
	double b = luaL_checknumber(L, -1);
	lua_pushnumber(L, a-b);

	return 1;
}

static const struct luaL_reg myLib[] = 
{
	{"hello", l_Hello},
	{"sub", l_Sub},
	{NULL, NULL}
};

int luaopen_myLib(lua_State *L)
{
	luaL_openlib(L, "myLib", myLib, 0);
	return 1;
}
