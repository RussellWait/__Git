

local function new (r, i) return {r = r, i = i} end

local function checkComplex(c)
	if not ("table" == type(c) and tonumber(c.r) and tonumber(c.i)) then
		error("bad complex number", 3)
	end
end

local function add(c1, c2)
	checkComplex(c1)
	checkComplex(c2)
	return new(c1.r+c2.r, c1.i+c2.i)
end

local function sub(c1, c2)
	checkComplex(c1)
	checkComplex(c2)
	return new(c1.r-c2.r, c1.i-c2.i)
end

function pub(c)
	print("pub: r=" .. c.r .. ", i=" .. c.i)
end


complex =
{
	new = new,
	add = add,
	sub = sub
}

return complex
