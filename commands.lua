MOVE = function (x, y)
print("[LUA] MOVE" .. x .. " " .. y)
c = HostFunction(x, y)
print("C function returned: " .. c)
--call move function in C++
end

MOVE(5, 7)

