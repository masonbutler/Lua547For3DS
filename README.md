## Lua 5.47 Running on the 3DS
Thought it would be interesting to see how much effort it would take to get Lua running on my 3DS. Turns out that Lua doesn't take much effort to get running without too much of a pain in the butt (only a little).

## Compiling the library (lib3dslua547)
This requires DevKitPro to be installed with devkitARM GCC version 14.2.1 20241119 (Arm GNU Toolchain 14.2.Rel1 (Build arm-14.52)). I built this on Windows 11 in VS Code, so if you are using another platform, it may have a couple hiccups.

Simply put the source files for Lua into the source folder, run the makefile from the base directory, and output the .a file into the lib folder in the base directory. If there is update to Lua, the makefile will probably still work.

## Compiling the test project (3dsLuaTest)
This requires DevKitPro to be installed with devkitARM GCC version 14.2.1 20241119 (Arm GNU Toolchain 14.2.Rel1 (Build arm-14.52)). I built this on Windows 11 in VS Code, so if you are using another platform, it may have a couple hiccups.

I already have the lib file in this, but if you need to replace it, just drop it in there and change the makefile, if necessary.

This program contains a basic Lua test script put in the filesystem of the device (romfs:/scripts). The program opens the test script and does the following: 
- Prints the name defined in the script
- Adds two numbers and prints the result in Lua
- Calls a Lua function from C++ and passes an argument
- Calls a CPP function from within Lua to draw a circle

## Running on a real 3DS
  ![image](https://github.com/user-attachments/assets/22939df3-bf1f-4a58-a260-d263b7b603d1)
