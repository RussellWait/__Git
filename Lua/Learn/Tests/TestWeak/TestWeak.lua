
a = {}
b = {}
setmetatable(a, b)

key1 = {}
a[key1] = 1
key1 = {}
a[key1] = 2

collectgarbage()

for k, v in pairs(a) do
	print(v)
end

print()

b.__mode = "k"

key2 = {}
a[key2] = 3
key2 = {}
a[key2] = 4

collectgarbage()

for k, v in pairs(a) do
	print(v)
end

print()

c = {}
d = {}

setmetatable(c, d)
d.__mode = "v"

value = {10}
c[1] = value
value = {20}
c[1] = value

collectgarbage()

for k, v in pairs(c) do
	print(v[1])
end


print("-------------------------------------------------------")

local results = {}
setmetatable(results, {__mode = "kv"})

function mem_loadstring(s)
	if results[s] then
		return results[s]
	else
		local res = loadstring(s)
		results[s] = res
		return res
	end
end

function createRGB(r, g, b)
	local key = r .. "-" .. g .. "-" .. b
	if results[key] then
		return results[key]
	else
		local newColor = {red = r, green = g, blue = b}
		results[key] = newColor
		return newColor
	end
end


print("-------------------------------------------------------")

local defaults = {}

setmetatable(defaults, {__mode = "k"})

local mt = {__index = function(t) return defaults[t] end}

function setDefault(t, d)
	defaults[t] = d
	setmetatable(t, mt)
end

print()

local metas = {}

setmetatable(metas, {__mode = "v"})

function setMetas(t, d)
	local mt = metas[d]
	if not mt then
		mt = {__index = function() return d end}
		metas[d] = mt
	end
	setmetatable(t, mt)
end
