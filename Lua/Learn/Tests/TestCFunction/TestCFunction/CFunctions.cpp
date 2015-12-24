#include "CFunctions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Tool.h"


int CFunction_Sin(lua_State *L);
int CFunction_Cos(lua_State *L);
int CFunction_Add(lua_State *L);

void CFunction_Register(lua_State *L)
{
	CFunction cFunctions[] =
	{
		CFunction_Sin,
		CFunction_Cos,
		CFunction_Add,
	};

	int len = sizeof(lFunctionNames) / sizeof(lFunctionNames[0]);
	for (int i = 0; i < len; i++)
	{
		lua_pushcfunction(L, cFunctions[i]);
		lua_setglobal(L, lFunctionNames[i]);
	}
}


int CFunction_Sin(lua_State *L)
{
 	double d = luaL_checknumber(L, 1);
 	lua_pushnumber(L, sin(d));

	return 1;
}

int CFunction_Cos(lua_State *L)
{
	double d = luaL_checknumber(L, 1);
	lua_pushnumber(L, cos(d));

	return 1;
}

int CFunction_Add(lua_State *L)
{
	double a = luaL_checknumber(L, 1);
	double b = luaL_checknumber(L, 2);
	lua_pushnumber(L, a+b);

	return 1;
}


void CFunction_Foo1(lua_State *L, double a, double b, double *c, double *d)
{
	if (luaL_loadfile(L, "LFunctions.lua") || lua_pcall(L, 0, 0, 0))
	{
		error(L, "cannot run config. file: %s.\n", lua_tostring(L, -1));
	}
	
	lua_getglobal(L, "LFunction_Foo1");
	lua_pushnumber(L, a);
	lua_pushnumber(L, b);

	if (lua_pcall(L, 2, 2, 0))
	{
		error(L, "error running function 'LFunction_Foo1' : %s.\n", lua_tostring(L, -1));
	}

	if (!lua_isnumber(L, -2) || !lua_isnumber(L, -1))
	{
		error(L, "function 'LFunction_Foo1' : must return two number.\n");
	}

	*c = lua_tonumber(L, -2);
	*d = lua_tonumber(L, -1);
}

void CFunction_Foo2(lua_State *L, double a, double b, double *c)
{
	if (luaL_loadfile(L, "LFunctions.lua") || lua_pcall(L, 0, 0, 0))
	{
		error(L, "cannot run config. file: %s.\n", lua_tostring(L, -1));
	}

	lua_getglobal(L, "LFunction_Foo2");
	lua_pushnumber(L, a);
	lua_pushnumber(L, b);

	if (lua_pcall(L, 2, 1, 0))
	{
		error(L, "error running function 'LFunction_Foo2' : %s.\n", lua_tostring(L, -1));
	}

	if (!lua_isnumber(L, -1))
	{
		error(L, "function 'LFunction_Foo2' : must return a number.\n");
	}

	*c = lua_tonumber(L, -1);
}
