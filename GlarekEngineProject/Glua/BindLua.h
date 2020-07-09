namespace Engine
{
	void RegisterAllWithLua(lua_State * pState)
	{
		lua_newtable(pState); //create the table

		lua_pushcfunction(pState, glua::Foo_Bar); // + 1
		lua_setfield(pState,  -2, "Foo_Bar")

		lua_pushcfunction(pState, glua::Foo_Baz); // + 1
		lua_setfield(pState,  -2, "Foo_Baz")

		lua_pushcfunction(pState, glua::Foo_Bah); // + 1
		lua_setfield(pState,  -2, "Foo_Bah")

		lua_pushcfunction(pState, glua::Foo_Get); // + 1
		lua_setfield(pState,  -2, "Foo_Get")

        lua_setglobal(pState, "Foo") //set the name of the table
        //new global
        //name of the class

	}
}

// Get foo instance
fi
Foo.Foo_Bar(fi, 1, 2)
//component functions outside the actor table cause they are all the same
//but the data goes into the actor itself.