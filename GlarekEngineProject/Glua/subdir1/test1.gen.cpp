#include "test1.h"
#include "test1.gen.h"
#include <Lua\Lua.hpp>

int ComponentZoo_Bar(lua_State* pState);
{
	using namespace Engine;
	ComponentZoo* pComponentZoo = reinterpret_cast<ComponentZoo*>(lua_touserdata(pState, -1);
	lua_pop(pState,1);
	pComponentZoo->Bar();
	return 0;
}

int ComponentZoo_Baz(lua_State* pState);
{
	using namespace Engine;
	ComponentZoo* pComponentZoo = reinterpret_cast<ComponentZoo*>(lua_touserdata(pState, -2);
	int _x = (int)lua_tonumber(pState, -1);
	lua_pop(pState,2);
	auto _result = pComponentZoo->Baz(_x);
	lua_pushinteger(pState,_result);
	return 1;
}

int ComponentZoo_Bah(lua_State* pState);
{
	using namespace Engine;
	ComponentZoo* pComponentZoo = reinterpret_cast<ComponentZoo*>(lua_touserdata(pState, -3);
	Foo* _pFoo = static_cast<Foo*>(lua_touserdata(pState, -2));
	char* _pChar = (std::string)lua_tostring(pState, -1);
	lua_pop(pState,3);
	auto _result = pComponentZoo->Bah(_pFoo,_pChar);
	lua_pushlightuserdata(pState,_result);
	return 1;
}

int ComponentZoo_Get(lua_State* pState);
{
	using namespace Engine;
	ComponentZoo* pComponentZoo = reinterpret_cast<ComponentZoo*>(lua_touserdata(pState, -1);
	lua_pop(pState,1);
	auto _result = pComponentZoo->Get();
	lua_pushinteger(pState,_result);
	return 1;
}

