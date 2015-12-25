#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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


void func1(lua_State *L);
void func2(lua_State *L);
void func3(lua_State *L);
void func4(lua_State *L);
void func5(lua_State *L);
void func6(lua_State *L);


int main(void)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

// 	func1(L);
// 	func2(L);
// 	func3(L);
//	func4(L);
//	func5(L);
	func6(L);

	lua_close(L);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
void func1(lua_State *L)
{
	printf("func1\n");

	char buff[256];
	int error;

	while (NULL != fgets(buff, sizeof(buff), stdin))
	{
		error = luaL_loadbuffer(L, buff, strlen(buff), "line") || lua_pcall(L, 0, 0, 0);
		if (error)
		{
			fprintf(stderr, "%s", lua_tostring(L, -1));
			lua_pop(L, 1);	// 弹出栈中的错误消息
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
static void stackDump(lua_State *L)
{
	for (int i = 1; i <= lua_gettop(L); i++)
	{
		int t = lua_type(L, i);
		switch (t)
		{
		case LUA_TSTRING:
			{
				printf("'%s'", lua_tostring(L, i));
				break;
			}

		case LUA_TBOOLEAN:
			{
				printf(lua_toboolean(L, i) ? "true" : "false");
				break;
			}

		case LUA_TNUMBER:
			{
				printf("%g", lua_tonumber(L, i));
				break;
			}

		default:
			{
				printf("%s", lua_typename(L, i));
			}
		}
		printf("\t");
	}
	printf("\n");
}

void func2(lua_State *L)
{
	printf("func2\n");

	lua_pushboolean(L, 1);
	lua_pushnumber(L, 10);
	lua_pushnil(L);
	lua_pushstring(L, "hello");
	stackDump(L);

	lua_pushvalue(L, -4);
	stackDump(L);

	lua_replace(L, 3);
	stackDump(L);

	lua_settop(L, 7);
	stackDump(L);

	lua_remove(L, -3);
	stackDump(L);
}

/////////////////////////////////////////////////////////////////////////////
#define MAX_COLOR	255

struct ColorTable
{
	char *name;
	unsigned char red, green, blue;
};

void error(lua_State *L, const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	lua_close(L);
	exit(EXIT_FAILURE);
}

void loadSize(lua_State *L, const char *fileName, int *w, int *h)
{
	if (luaL_loadfile(L, fileName) || lua_pcall(L, 0, 0, 0))
	{
		error(L, "cannot run config. file: %s.\n", lua_tostring(L, -1));
	}

	lua_getglobal(L, "width");
	lua_getglobal(L, "height");

	if (!lua_isnumber(L, -2))
	{
		error(L, "'width' should be a number\n");
	}
	if (!lua_isnumber(L, -1))
	{
		error(L, "'heith' sholud be a number\n");
	}

	*w = lua_tointeger(L, -2);
	*h = lua_tointeger(L, -1);
}

int getField(lua_State *L, const char *key)
{
	lua_pushstring(L, key);
	lua_gettable(L, -2);

	if (!lua_isnumber(L, -1))
	{
		error(L, "invalid component in background color.\n");
	}

	int result = (int)(lua_tonumber(L, -1) * MAX_COLOR);
	lua_pop(L, 1);

	return result;
}

void loadColor(lua_State *L, const char *fileName, const char *colorName, ColorTable *color)
{
	if (luaL_loadfile(L, fileName) || lua_pcall(L, 0, 0, 0))
	{
		error(L, "cannot run config. file:%s.\n", lua_tostring(L, -1));
	}

	lua_getglobal(L, colorName);

	if (!lua_istable(L, -1))
	{
		error(L, "color name is not a valid color table.\n");
	}

	color->red = getField(L, "r");
	color->green = getField(L, "g");
	color->blue = getField(L, "b");
}

void func3(lua_State *L)
{
	printf("func3\n");

	int width = 0, height = 0;
	ColorTable table = {0, 0, 0};

	loadSize(L, "Datas.lua", &width, &height);
	loadColor(L, "Datas.lua", "background", &table);

	printf("size: width=%d, height=%d\n", width, height);
	printf("color: r=%d, g=%d, b=%d\n", table.red, table.green, table.blue);
}


/////////////////////////////////////////////////////////////////////////////
double foo(lua_State *L, const char *fileName, double x, double y)
{
	if (luaL_loadfile(L, fileName) || lua_pcall(L, 0, 0, 0))
	{
		error(L, "cannot run config. file:%s.\n", lua_tostring(L, -1));
	}

	lua_getglobal(L, "foo");
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	if (0 != lua_pcall(L, 2, 1, 0))
	{
		error(L, "error running function 'foo' : %s.\n", lua_tostring(L, -1));
	}

	if (!lua_isnumber(L, -1))
	{
		error(L, "function 'foo' : must return a number.\n");
	}

	double z = lua_tonumber(L, -1);

	return z;
}

void func4(lua_State *L)
{
	printf("func4\n");

	double z = foo(L, "Function.lua", 2, 1.57);
	printf("z = %2f\n", z);
}

/////////////////////////////////////////////////////////////////////////////
void call_va(lua_State *L, const char *fileName, const char *func, const char *sig, ...)
{
	if (luaL_loadfile(L, fileName) || lua_pcall(L, 0, 0, 0))
	{
		error(L, "cannot run config. file:%s.\n", lua_tostring(L, -1));
	}

	va_list vl;
	int narg = 0;
	int nres = 0;

	va_start(vl, sig);
	lua_getglobal(L, func);

	bool b = true;
	while (*sig)
	{
		switch (*sig++)
		{
		case 'd':
			{
				lua_pushnumber(L, va_arg(vl, double));
				break;
			}

		case 'i':
			{
				lua_pushnumber(L, va_arg(vl, int));
				break;
			}

		case 's':
			{
				lua_pushstring(L, va_arg(vl, char*));
				break;
			}

		case '>':
			{
				b = false;
				break;
			}

		default:
			{
				error(L, "invalid option (%c).\n", *(sig-1));
				break;
			}
		}

		if(!b)
		{
			break;
		}

		narg++;
		luaL_checkstack(L, 1, "too many arguments");
	}

	nres = strlen(sig);
	if (lua_pcall(L, narg, nres, 0))
	{
		error(L, "error running function '%s' : '%s'.", func, lua_tostring(L, -1));
	}

	nres = -nres;
	while (*sig)
	{
		switch (*sig++)
		{
		case 'd':
			{
				if (!lua_isnumber(L, nres))
				{
					error(L, "wrong result type");
				}
				*va_arg(vl, double *) = lua_tonumber(L, nres);
				break;
			}

		case 'i':
			{
				if (!lua_isnumber(L, nres))
				{
					error(L, "wrong result type");
				}
				*va_arg(vl, int *) = lua_tonumber(L, nres);
				break;
			}

		case 's':
			{
				if (!lua_isstring(L, nres))
				{
					error(L, "worng result type");
				}
				*va_arg(vl, const char **) = lua_tostring(L, nres);
				break;
			}

		default:
			{
				error(L, "invalid option (%c).", *(sig-1));
				break;
			}
		}
		nres++;
	}

	va_end(vl);
}

void func5(lua_State *L)
{
	printf("func5\n");

	double x = 2, y = 1.57;
	double z = 0;
	call_va(L, "Function.lua", "foo", "dd>d", x, y, &z);
	printf("z = %2f\n", z);
}

/////////////////////////////////////////////////////////////////////////////
void printState(lua_State *L)
{
	printf("---------------------------------------------------\n");

	size_t len = lua_gettop(L);
	for (int i = 1; i <= len; i++)
	{
		printf("%d>> ", i);

		if (lua_isnumber(L, i))
		{
			printf("num: %d\n", lua_tonumber(L, i));
		}
		else if (lua_isboolean(L, i))
		{
			printf("bool: %d\n", lua_toboolean(L, i));
		}
		else if (lua_isstring(L, i))
		{
			printf("str: %s\n", lua_tostring(L, i));
		}
		else if (lua_istable(L, i))
		{
			printf("table\n");
		}
		else if (lua_isfunction(L, i))
		{
			printf("function\n");
		}
	}

	printf("===================================================\n\n");
}

void func6(lua_State *L)
{
	printState(L);

	lua_createtable(L, 0, 1);
	lua_pushboolean(L, 3);
	lua_pushnumber(L, 100);
	lua_setfield(L, -3, "hehe");
	lua_pushstring(L, "abc");
	printState(L);

	lua_settop(L, 0);
	lua_createtable(L, 0, 1);
	lua_pushliteral(L, "");
	lua_pushvalue(L, -2);
	printState(L);
	lua_setmetatable(L, -2);
	printState(L);
}
