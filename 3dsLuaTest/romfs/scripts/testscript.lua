testVar = 8 + 9;
name = "Mason Butler";

print("LUA: Hello, "..name);
print("LUA: The number is "..testVar);

function PrintColour(num)
	if num == 1 then
		print("LUA: RED!");
	elseif num == 2 then
		print("LUA: GREEN!");
	elseif num == 3 then
		print("LUA: BLUE!");
	else
		print("LUA: I only know 3 colours :(")
	end
end

function CallCPPNativeFunction()
	DrawCircle(100, 100, 20);
end