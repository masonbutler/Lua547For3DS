#include <iostream>
#include <string>
#include <citro2d.h>
#include "lua/lua.hpp"


// We need to define this since the 3DS is 32-bit
// and Lua default builsd to 64-bit
#ifndef LUA_32BITS
#define LUA_32BITS	1
#endif

// Function prototypes
int lua_DrawCircle(lua_State *vm);
bool CheckLuaError(lua_State *vm, int r);
void DrawCircleFromLua(lua_State *vm);
void GetNameFromLua(lua_State *vm);
void CallLuaFunction(lua_State *vm);


int main() 
{
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);
    C3D_RenderTarget *screen = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	int keysD;

	// Create our Lua VM
    lua_State *luaVm = luaL_newstate();
	// Open all standard libraries for Lua (so we can print, do math etc)
    luaL_openlibs(luaVm);
    // Register the native CPP function lua_DrawCircle to be called as DrawCircle in Lua
    lua_register(luaVm, "DrawCircle", lua_DrawCircle);

	// Open the test script and check for errors
    if(CheckLuaError(luaVm, luaL_dofile(luaVm, "romfs:/scripts/testscript.lua")))
    {
		GetNameFromLua(luaVm);
		CallLuaFunction(luaVm);
    }

	while (aptMainLoop()) {
		// Handle user input
		hidScanInput();
		keysD = hidKeysDown();

		if (keysD & KEY_START) break;

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

			C2D_TargetClear(screen, C2D_Color32(0xff, 0xff, 0xff, 0xff));
			C2D_SceneBegin(screen);
			DrawCircleFromLua(luaVm);

    	C3D_FrameEnd(0);
	}
	
	lua_close(luaVm);
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	return 0;
}

int lua_DrawCircle(lua_State *vm)
{
	// Get the arguments from the stack
    int x = (int) lua_tonumber(vm, 1);
    int y = (int) lua_tonumber(vm, 2);
    int r = (int) lua_tonumber(vm, 3);

	// Draw a circle 
	u32 color = C2D_Color32(0, 0, 255, 255);
	C2D_DrawCircleSolid(x, y, 1.0f, r, color);

  	// Num of arguments passed back to Lua 
    return 0;
}


bool CheckLuaError(lua_State *vm, int result)
{
    if(result != LUA_OK)
    {
        std::string errorMsg = lua_tostring(vm, -1);
        std::cout << errorMsg << std::endl;
        return false;
    }
    
    return true;
}

void GetNameFromLua(lua_State *vm)
{
	// Get the variable "name" from the Lua script
	lua_getglobal(vm, "name");
	// Check if it is a string (-1 is the position on the Lua stack)
	if(lua_isstring(vm, -1))
	{
		// Convert to a string and store in CPP string
		std::string name = lua_tostring(vm, -1);
		std::cout << "CPP: This was made by " << name << "\n";
	}
}

void CallLuaFunction(lua_State *vm)
{
	// Call a function PrintColour in Lua
	lua_getglobal(vm, "PrintColour");
	// Check if it is a function (-1 is the position on the Lua stack)
	if(lua_isfunction(vm, -1))
	{
		// Push the number "2" onto the Lua stack, this is our argument to the function
		lua_pushnumber(vm, 2);
		// Call the function, Pcall takes the Number of arguments, the number of values returned, and the error handling (0)
		if(CheckLuaError(vm, lua_pcall(vm, 1, 0, 0)))
		{

		}
	}
}

void DrawCircleFromLua(lua_State *vm)
{
	lua_getglobal(vm, "CallCPPNativeFunction");
	if(lua_isfunction(vm, -1))
	{
		if(CheckLuaError(vm, lua_pcall(vm, 0, 3, 0)))
		{

		}
	}
}