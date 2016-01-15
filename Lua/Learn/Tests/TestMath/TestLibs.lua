
t = os.time()
r = math.randomseed(t)
print(t, r)


print("-----------------------------------------------")

a = {1, 2, 3, 4, nil, 5, 6, 7, nil}
print(table.getn(a))

--table.setn(a, 1000)
print(table.getn(a))

b = {n = 10}
print(table.getn(b))

table.insert(a, 0, 10)
for k, v in pairs(a) do
	print("k=" .. k .. ", " .. v)
end

print()

lines =
{
	luaH_set = 10,
	luaH_get = 24,
	luaH_present = 48
}

c = {}
for k in pairs(lines) do table.insert(c, k) end
table.sort(c)
for k, v in pairs(c) do print(v) end


print("-----------------------------------------------")

s = "abcdefghijklmnabcdefabc"

print(string.len(s))
ms = string.rep("a", 2^20)
print(string.len(ms))

print(string.upper("afjiej348./,.,.fa"))
print(string.lower("FUIEHUjfehfiuFIUEHU"))
print(string.byte("abc", 2))
print(string.format("pi = %.4f", math.pi))

print(string.find(s, "bcde"))
print(string.find(s, "bcde", 10))
print(string.sub(s, 3, 5))

st = "fjieojfioje\nfjifeijfiiyue\nyy37438nmaz.cmdnfe\nJFfekfe"
local t = {}
local b = 1
local e = 0
while true do
	e = string.find(st, "\n", b)
	if e then
		table.insert(t, string.sub(st, b, e-1))
		b = e + 1
	else
		e = string.len(st)
		table.insert(t, string.sub(st, b, e))
		break
	end
end

for k, v in pairs(t) do
	print(v)
end

print(string.gsub("Lua is cute cute cute", "cute", "great"))
print(string.gsub("abcabcabcabc", "a", "x", 2))

s = "deadline is 30/05/1999, firm"
date = "%d%d/%d%d/%d%d%d%d"
print(string.sub(s, string.find(s, date)))
