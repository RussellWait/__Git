#include "CFunctions.h"
#include "MyLib.h"

int main()
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	luaopen_myLib(L);
	CFunction_Register(L);
	luaL_dofile(L, "LDofile.lua");

	printf("=========================\n");

	double a = 0, b = 0;
	CFunction_Foo1(L, 3, 8, &a, &b);
	printf("a = %lf, b = %lf\n", a, b);
	CFunction_Foo2(L, 1, 2, &a);
	printf("a = %lf\n", a);

	lua_close(L);

	return 0;
}
