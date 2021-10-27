

MOVE = function (x, y)
print("[LUA] MOVE " .. x .. " " .. y)
c = inlua_move_player(manager, x, y)
print("[LUA] C function returned: " .. c)
--call move function in C++
end

MOVE(8, 8)

