Set = {}
Set.mt = {}

function Set.new(t)
	local set = {}
	setmetatable(set, Set.mt)
	for _, l in ipairs(t) do set[l] = true end
	return set
end

Set.mt.__le = function(a, b)
	for k in pairs(a) do
		if not b[k] then return false end
	end
	return true
end

Set.mt.__lt = function(a, b)
	return a <= b and not (b <= a)
end

Set.mt.__eq = function(a, b)
	return a <= b and b <= a
end

Set.mt.__mul = function(a, b)
	local res = Set.new{}
	for k in pairs(a) do
		res[k] = b[k]
	end
	return res
end


s1 = Set.new {2, 4}
s2 = Set.new {4, 10, 2}

print(s1 <= s2)
print(s1 < s2)
print(s1 >= s1)
print(s1 > s1)
print(s1 == s2 * s1)


---------------------------------------------------------------

function Set.mt.__tostring(set)
	local s = "{"
	local sep = ""
	for e in pairs(set) do
		s = s .. sep ..e
		sep = ", "
	end
	return s .. "}"
end

print(s1)

Set.mt.__metatable = "not your business"	-- ±£»¤metaTable


----------------------------------------------------------------

Window = {}
Window.prototype = {x = 0, y = 0, width = 100, height = 100}
Window.mt = {}

function Window.new(o)
	setmetatable(o, Window.mt)
	return o
end

--[[
Window.mt.__index = function(table, key)
	return Window.prototype[key]
end
--]]
Window.mt.__index = Window.prototype

w = Window.new{}
print(w.width)
print(rawget(w, width))


-----------------------------------------------------------------

function setDefault(t, d)
	local mt = {__index = function() return d end}
	setmetatable(t, mt)
end

t1 = {x = 10, y = 20}
print(t1.x, t1.z)
setDefault(t1, 3)
print(t1.x, t1.z)


-------------------------------------------------------------------

t = {}
local _t = t

t = {}

local mt =
{
	__index = function(t, k)
		print("*access to element " .. tostring(k))
		return _t[k]
	end,

	__newindex = function(t, k, v)
		print("*update of element " .. tostring(k) .. " to " .. tostring(v))
		_t[k] = v
	end
}
setmetatable(t, mt)

t[2] = "hello"
print(t[2])
t[2] = "How are you"
print(t[2])


-----------------------------------------------------------------------

function readOnly(t)
	local proxy = {}
	local mt =
	{
		__index = t,
		__newindex = function(t, k, v)
			error("attempt to update a read-only table", 2)
		end
	}
	setmetatable(proxy, mt)
	return proxy
end

days = readOnly{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}
print(days[1])
--days[2] = "Noday"
