t = {}
print(getmetatable(t))

t1 = {}
setmetatable(t, t1)
print(getmetatable(t))


-----------------------------------------------------

Set = {}

function Set.new(t)
	local set = {}
	for _, l in ipairs(t) do
		set[1] = true
	end
	return set
end

function Set.union(a, b)
	local res = Set.new {}
	for k in pairs(a) do res[k] = true end
	for k in pairs(b) do res[k] = true end
	return res
end

function Set.intersection(a, b)
	local res = Set.new {}
	for k in pairs(a) do
		res[k] = b[k]
	end
	return res
end

function Set.tostring(set)
	local s = "{"
	local sep = ""
	for e in pairs(set) do
		s = s .. sep ..e
		sep = ", "
	end
	return s .. "}"
end

function Set.print(s)
	print(Set.tostring(s))
end


----------------------------------------------

Set.mt = {}
function Set.new(t)
	local set = {}
	setmetatable(set, Set.mt)
	for _, l in ipairs(t) do set[l] = true end
	return set
end


s1 = Set.new {10, 20, 30, 50}
s2 = Set.new {30, 1}
print(getmetatable(s1))
print(getmetatable(s2))

Set.mt.__add = Set.union
s3 = s1 + s2
Set.print(s3)

Set.mt.__mul = Set.intersection
Set.print(s3 * s1)

s4 = Set.new {1, 2, 3}
--s4 = s4 + 8
--set.print(s4)
