--[[
for n in pairs(_G) do
	print(n)
end
--]]

--------------------------------------------------

function getfield(f)
	local v = _G
	for w in string.gfind(f, "[%w_]+") do
		v = v[w]
	end
	return v
end

function setfield(f, v)
	local t = _G
	for w, d in string.gfind(f, "([%w_]+)(.?)") do
		if "." == d then
			t[w] = t[w] or {}
			t = t[w]
		else
			t[w] = v
		end
	end
end

setfield("t.x.y", 10)
print(t.x.y)
print(getfield("t.x.y"))


--------------------------------------------------------

local noIndex =
{
	__newindex = function(_, n)
		error("attempt to write to undeclared variable" .. n, 2)
	end,

	__index = function(_, n)
		error("attempt to read undeclared variable " .. n, 2)
	end
}

function declare(name, initval)
	rawset(_G, name, initval or false)
end

--setmetatable(_G, noIndex)

a = 3
declare("b", 4)
print(b)


------------------------------------------------------------

local declaredNames = {}

function declare(name, initval)
	rawset(_G, name, initval)
	declaredNames[name] = true
end

setmetatable(_G,
	{
		__newindex = function(t, k, v)
			if not declaredNames[k] then
				error("attempt to write to undeclared var. " .. k, 2)
			else
				rawset(t, k, v)
			end
		end,

		__index = function(t, k)
			if not declaredNames[k] then
				error("attempt to read undeclared var. " .. k, 2)
			else
				return nil
			end
		end
	}
)


---------------------------------------------------------------

a = 1
--setfenv(1, {})
--print(a)

setfenv(1, {_G = _G})
--print(a)
_G.print(a)
_G.print(_G.a)
