#include "test2.h"
#include "test2.gen.h"
#include <Lua\Lua.hpp>

int FooTest_Bar(lua_State* pState);
{
	using namespace Engine;
	FooTest* pFooTest = reinterpret_cast<FooTest*>(lua_touserdata(pState, -1);
	lua_pop(pState,1);
	pFooTest->Bar();
	return 0;
}

int FooTest_Baz(lua_State* pState);
{
	using namespace Engine;
	FooTest* pFooTest = reinterpret_cast<FooTest*>(lua_touserdata(pState, -2);
	int _x = (int)lua_tonumber(pState, -1);
	lua_pop(pState,2);
	auto _result = pFooTest->Baz(_x);
	lua_pushinteger(pState,_result);
	return 1;
}

int FooTest_Bah(lua_State* pState);
{
	using namespace Engine;
	FooTest* pFooTest = reinterpret_cast<FooTest*>(lua_touserdata(pState, -3);
	Foo* _pFoo = static_cast<Foo*>(lua_touserdata(pState, -2));
	char* _pChar = (std::string)lua_tostring(pState, -1);
	lua_pop(pState,3);
	auto _result = pFooTest->Bah(_pFoo,_pChar);
	lua_pushlightuserdata(pState,_result);
	return 1;
}

int FooTest_Get(lua_State* pState);
{
	using namespace Engine;
	FooTest* pFooTest = reinterpret_cast<FooTest*>(lua_touserdata(pState, -1);
	lua_pop(pState,1);
	auto _result = pFooTest->Get();
	lua_pushinteger(pState,_result);
	return 1;
}

