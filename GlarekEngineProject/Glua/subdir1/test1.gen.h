#pragma once

struct lua_State;

namespace glua
{
	int ComponentZoo_Bar(lua_State* pState);;
	int ComponentZoo_Baz(lua_State* pState);;
	int ComponentZoo_Bah(lua_State* pState);;
	int ComponentZoo_Get(lua_State* pState);;
}

