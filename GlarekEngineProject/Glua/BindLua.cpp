#include "BindLua.h"
#include <Lua\Lua.hpp>
void Engine::RegisterAllWithLua(lua_State * pState)
{
		lua_newmetatable(pState, "Foo");

		lua_pushcfunction(pState, glua::Foo_Bar); // + 1
		lua_setfield(pState,  -2, "Foo_Bar")

		lua_pushcfunction(pState, glua::Foo_Baz); // + 1
		lua_setfield(pState,  -2, "Foo_Baz")

		lua_pushcfunction(pState, glua::Foo_Bah); // + 1
		lua_setfield(pState,  -2, "Foo_Bah")

		lua_pushcfunction(pState, glua::Foo_Get); // + 1
		lua_setfield(pState,  -2, "Foo_Get")

		lua_setfield(pState, -2, "Foo");
}