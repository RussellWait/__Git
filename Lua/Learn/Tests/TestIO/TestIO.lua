local f = assert(io.open("TestIO.lua", 'r'))

local str = f:read("*all")
print(str)

f:close()


f = assert(io.open("TestIO.lua", 'a'))

local str = f:write("\n--Can you see me?")

f:close()


