function serializeZ(o)
	local lType = type(o)
	if "number" == lType then
		io.write(o)
	elseif "string" == lType then
		io.write(string.format("%q", o))
	elseif "table" == lType then
		io.write("{\n")
		for k, v in pairs(o) do
			io.write(" {")
			serializeZ(k)
			io.write("] = ")
			serializeZ(v)
			io.write(", \n")
		end
		io.write("}\n")
	else
		error("cannot serialize a " .. type(o))
	end
end


serializeZ {a = 12, b = "Lua", key = "another \"one\""}


-----------------------------------------------------------

function basicSerialize(o)
	if "number" == type(o) then
		return tostring(o)
	elseif "string" == type(o) then
		return string.format("%q", o)
	end
end

function save(name, value, saved)
	local saved = saved or {}
	io.write(name, " = ")
	if "number" == type(value) or "string" == type(value) then
		io.write(basicSerialize(value), "\n")
	elseif "table" == type(value) then
		if saved[value] then
			io.write(saved[value], "\n")
		else
			saved[value] = name
			io.write("{}\n")
			for k, v in pairs(value) do
				local fieldname = string.format("%s[%s]", name, basicSerialize(k))
				save(fieldname, v, saved)
			end
		end
	else
		error("cannot save a " .. type(value))
	end
end


a = {x = 1, y = 2; {3, 4, 5}}
a[2] = a
a.z = a[1]

save("a", a)
