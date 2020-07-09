import os

# To Do
lua_funcs = dict()
lua_funcs['u32'] = '(u32)lua_tonumber'
lua_funcs['f32'] = '(f32)lua_tonumber'
lua_funcs['int'] = '(int)lua_tonumber'
lua_funcs['char*'] = 'lua_tostring'
lua_funcs['bool'] = 'lua_toboolean'

# To Do
lua_pushFuncs = dict()
lua_pushFuncs['u32'] = 'lua_pushinteger'
lua_pushFuncs['f32'] = 'lua_pushnumber'
lua_pushFuncs['int'] = 'lua_pushinteger'
lua_pushFuncs['char*'] = 'lua_pushstring'
lua_pushFuncs['bool'] = 'lua_pushboolean'
lua_pushFuncs['pointer'] = 'lua_pushlightuserdata'

namespaceGlua = 'glua'
namespaceEngine = 'Engine'

# To Do
lua_pushClasses = dict()
# lua_pushClasses['test'] = ['apple', 'orgrange']
# lua_pushClasses['testagain'] = ['apple', 'orgrange']

# lua_registerFuncs = []

class Argument:
    def __init__(self, type, name):
        self.type = type
        self.name = name

        print("Type: " + type)
        print("Name: " + name)

    def serialize_cast(self, stack_location):
        the_type = self.type.replace('const','')
        the_type = the_type.replace('&', '').strip(' ')
        print(the_type)

        lua_func = 'static_cast<{0}>(lua_touserdata'.\
            format(the_type)

        is_user_data = True
        if the_type in lua_funcs.keys():
            lua_func = lua_funcs[the_type]
            is_user_data = False;

        # return type name = the item for dic(pState, how far it off the stack
        result = '{0} _{1} = {2}(pState, {3})'.\
            format(the_type, self.name, lua_func, stack_location)

        if is_user_data:
            result += ')'

        return result


class Function:
    def __init__(self, class_name='Error', args=[], return_type='void', name='Error'):
        self.args = args
        self.return_type = return_type
        self.name = name
        self.class_name = class_name

    def serialize_header(self):
        return 'int {0}_{1}(lua_State* pState);'.format(self.class_name, self.name)

    def register_lua(self):
        if self.class_name not in lua_pushClasses.keys():
            lua_pushClasses[self.class_name] = []
        lua_pushClasses[self.class_name].append('{0}_{1}'.format(self.class_name, self.name))

    def parse(self, line):
        self.args = []
        open_paren = line.find('(')
        close_paren = line.find(')')
        space = line.rfind(' ', 0, open_paren)
        print(open_paren, close_paren, space)

        self.name = line[space + 1:open_paren]
        print('Found function - Name: ' + self.name)
        self.return_type = line[:space]

        # Deal with arguments
        arg_text = line[open_paren + 1:close_paren]
        args = arg_text.split(',')

        if args[0] != '':
            for arg in args:
                space = arg.rfind(' ')
                self.args.append(Argument(arg[:space], arg[space + 1:]))

        pass


def parse_file(filename):
    f = open(filename)
    lines = f.readlines()
    ready_to_parse = False
    class_name = ''
    functions = []
    for line in lines:

        if '//' in line:
            print('Found Comment in ' + line)
            line = line[0:line.find('//')]
            print('Cleaned: ' + line)

        if len(line) < 1:
            continue

        if 'class' in line and ';' not in line and 'enum' not in line:
            words = line.split(' ')
            class_name = words[1]
            class_name = class_name.rstrip(' \r\n\t')

        if ready_to_parse:
            ready_to_parse = False;
            function = Function(class_name)
            function.parse(line)

            functions.append(function)

        if 'GLUA' in line:
            ready_to_parse = True

    f.close()

    if len(functions) == 0:
        return

    # Found all functions in the file to output
    f = open(filename.replace('.h', '.gen.h'), 'w')

    # Header
    f.write('#pragma once\n'
            '\n'
            'struct lua_State;\n'
            '\n'
            'namespace {0}\n'.format(namespaceGlua) +
            '{\n'
            )

    # Loop through the functions
    for function in functions:
        f.write('\t' + function.serialize_header() + ';\n')

    f.write('}\n\n')
    f = open(filename.replace('.h', '.cpp'), 'w')

    # Include the files we need
    f.write('#include "' + filename + '"\n')
    f.write('#include "' + filename.replace('.h', '.gen.h') + '"\n')
    f.write('#include <Lua\\Lua.hpp>\n\n')

    for function in functions:
        function.register_lua();
        f.write(function.serialize_header() + '\n')
        f.write('{\n')

        # Get 'this' and cast it
        f.write('\tusing namespace {0};\n'.format(namespaceEngine))
        f.write('\t{0}* p{0} = reinterpret_cast<{0}*>(lua_touserdata(pState, {1});\n'.
                format(function.class_name, -(len(function.args) + 1)))

        # Get Other arguments
        offset = -len(function.args)
        parameters = ''
        for arg in function.args:
            f.write('\t' + arg.serialize_cast(offset) + ';\n')
            parameters += '_' + arg.name + ','
            offset += 1

        parameters = parameters[:-1]

        # TODO: pop off the stack
        # if len(function.args)> 0:
        f.write('\tlua_pop(pState,{1});\n'.format(function.class_name, len(function.args)+1))

        # TODO: Call the actual function
        # TODO: Handle return types/values
        # TODO: Push result onto stack (if any)
        # TODO: Return the number of return values

        the_type = function.return_type
        if 'void' in the_type:
            f.write('\tp{0}->{1}({2});\n'.format(function.class_name, function.name, parameters))
            f.write('\treturn 0;\n')

        else:
            lua_pushFunc = ''
            f.write('\tauto _result = p{0}->{1}({2});\n'.format(function.class_name, function.name, parameters))

            findType = False
            for key in lua_pushFuncs.keys():
                if key in the_type:
                    lua_pushFunc = lua_pushFuncs[key]
                    findType = True;
                    break;

            if not findType:
                lua_pushFunc = lua_pushFuncs['pointer']

            f.write('\t{0}({1},{2});\n'.format(lua_pushFunc, 'pState', '_result'));
            f.write('\treturn 1;\n')

        f.write('}\n\n')

    f.close()


for root, dirs, files in os.walk('.'):
    for file in files:
        if '.h' in file and '.gen' not in file:
            parse_file(file)
            print('Parsing:' + file)


# TODO: Remember all functions that were generated
# TODO: Write a function that will register every single one
f = open('BindLua.h', 'w')
f.write('namespace {0}'.format(namespaceEngine)
        + '\n{\n')
f.write('\tvoid RegisterAllWithLua(lua_State * pState)\n' + '\t{\n')

# TODO: different class will have different lua_table
# TODO: setfield: function name

# for func in lua_registerFuncs:
#     f.write('\t\tlua_pushcfunction(pState, {0}::'.format(namespaceGlua) + func + '); // + 1\n')
# f.write('\t}\n}\n')


for key in lua_pushClasses.keys():
    # TODO: for Component class
    if 'Component' in key:
        f.write('\t\tlua_newtable(pState);\n')
        f.write('\t\tlua_pushlightuserdata(pState, this);\n')
        f.write('\t\tlua_setfield(pState, -2, "this");\n')
        f.write('\t\t\n')
    else:
        f.write('\t\tlua_newmetatable(pState, "{0}");\n\n'.format(key)) # ??? what is metaTable

    for func in lua_pushClasses[key]:
        f.write('\t\tlua_pushcfunction(pState, {0}::'.format(namespaceGlua) + func + '); // + 1\n')
        f.write('\t\tlua_setfield(pState,  -2, "{0}")\n\n'.format(func))
    f.write('\t}\n}')

    # TODO: set -2 index to be the class
    f.write('\t\tlua_setfield(pState, -2, "{0}");\n'.format(key))

f.close()

#.gen.cpp
#.gen.h include .h

#add generated files to the solution:
#header declare the register everything function : define in cpp

#figure out if a function is template specialized
#make own compiler warming
#do sth in
#own tool to parse : one function need to know are u specialized
#events: go through all events => queue => dispatching automatically to lua => only when it have the push to lua
#check at compile time: trivia type
#lua event overwrite a function and call
#easy fast, register to a c++ event without to do much parsing

#TDD: test driven development
#test before code

#AI Unit Test: use AI to test your game

#benefits from structured mem allocation
#block of mem
#if someone broke the game, just output the memory block to mem.txt
#difficult for pointers still

#have blocks: arenas for textures...
#override new and delete

#What to test?
#link to the dll unit test in visual studio, write the tests ourselves
#Object Creation/ Loading Assets/ Components/ Lua/ Math /Operating System Stuff/ Balancing the time

#Deterministic: do the same things every time



