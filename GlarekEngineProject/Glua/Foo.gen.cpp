#include "Foo.h"
#include "Foo.gen.h"
#include <Lua\Lua.hpp>

int Foo_Bar(lua_State* pState);
{
	using namespace Engine;
	Foo* pFoo = reinterpret_cast<Foo*>(lua_touserdata(pState, -1);
	lua_pop(pState,1);
	pFoo->Bar();
	return 0;
}

int Foo_Baz(lua_State* pState);
{
	using namespace Engine;
	Foo* pFoo = reinterpret_cast<Foo*>(lua_touserdata(pState, -2);
	int _x = (int)lua_tonumber(pState, -1);
	lua_pop(pState,2);
	auto _result = pFoo->Baz(_x);
	lua_pushinteger(pState,_result);
	return 1;
}

int Foo_Bah(lua_State* pState);
{
	using namespace Engine;
	Foo* pFoo = reinterpret_cast<Foo*>(lua_touserdata(pState, -3);
	Foo* _pFoo = static_cast<Foo*>(lua_touserdata(pState, -2));
	char* _pChar = (std::string)lua_tostring(pState, -1);
	lua_pop(pState,3);
	auto _result = pFoo->Bah(_pFoo,_pChar);
	lua_pushlightuserdata(pState,_result);
	return 1;
}

int Foo_Get(lua_State* pState);
{
	using namespace Engine;
	Foo* pFoo = reinterpret_cast<Foo*>(lua_touserdata(pState, -1);
	lua_pop(pState,1);
	auto _result = pFoo->Get();
	lua_pushinteger(pState,_result);
	return 1;
}

