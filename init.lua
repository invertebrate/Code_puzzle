MOVE = function (x, y)
	print("[LUA] MOVE " .. x .. " " .. y)
	c = inlua_move_player(manager, x, y)
	print("[LUA] C move function returned: " .. c)
	--call move function in C++
end
