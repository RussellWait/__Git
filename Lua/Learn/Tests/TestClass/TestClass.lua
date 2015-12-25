Account1 = {balance = 0}

function Account1.withdraw(v)
	Account1.balance = Account1.balance - v
	print(Account1.balance)
end

Account1.withdraw(100)

a = Account1
a.withdraw(100)

--[[
Account1 = nil
a.withdraw(100)
--]]

function Account1.atdraw(self, v)
	self.balance = self.balance - v
	print(self.balance)
end

a = Account1
Account1 = nil
a.atdraw(a, 100)


print("------------------------------------------------------------")

Account2 =
{
	balance = 0,
	withdraw = function(self, v)
		self.balance = self.balance - v
		print(self.balance)
	end
}

function Account2:deposit(v)
	self.balance = self.balance + v
	print(self.balance)
end

b = Account2
--Account2 = nil
b.withdraw(b, 100)
b.deposit(b, 100)
b:withdraw(10)
b:deposit(10)


print("------------------------------------------------------------")

function Account2:new(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	return o
end

c = Account2:new{balance = 100}
c:deposit(100)

d = Account2:new()
d:deposit(100)

print(Account2.balance)


print("------------------------------------------------------------")

Account3 = {balance = 0}

function Account3:new(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	return o
end

function Account3:getBalance()
	return self.balance
end

function Account3:deposit(v)
	self.balance = self.balance + v
end

function Account3:withdraw(v)
	if v > self.balance then
		error "insufficient funds"
	else
		self.balance = self.balance - v
	end
end

SepcialAccount = Account3:new()

function SepcialAccount:withdraw(v)
	if v - self.balance >= self.getLimit() then
		error "insufficient funds"
	else
		self.balance = self.balance - v
	end
end

function SepcialAccount:getLimit()
	return self.limit or 0
end


s = SepcialAccount:new{limit = 1000.00}
s:deposit(100)
print(s:getBalance())


print("------------------------------------------------------------")

local function search(k, plist)
	for i = 1, table.getn(plist) do
		local v = plist[i][k]
		if v then return v end
	end
end

function createClass(...)

	local c = {}

	setmetatable(c,
				{
					__index = function(t, k)
						return search(k, arg)
					end
				})

	c.__index = c

	function c:new(o)
		o = o or {}
		setmetatable(o, c)
		return o
	end

	return c
end

Named = {}

function Named:getname()
	return self.name
end

function Named:setname(n)
	self.name = n
end

NamedAccount = createClass(Account3, Named)

account = NamedAccount:new {name = "Paul"}
print(account:getname())


print("------------------------------------------------------------")

function newAccount(initialBalance)

	local self = {balance = initialBalance}

	local withdraw = function(v)
		self.balance = self.balance - v
	end

	local deposit = function(v)
		self.balance = self.balance + v
	end

	local getBalance = function()
		return self.balance
	end

	return
	{
		withdraw	= withdraw,
		deposit		= deposit,
		getBalance	= getBalance,
	}

end

acc = newAccount(100)
acc.withdraw(40)
print(acc.getBalance())


print("------------------------------------------------------------")

function newObject(value)
	return function (action, v)
		if "get" == action then return value
		elseif "set" == action then value = v
		else error("invalid action")
		end
	end
end

d = newObject(10)
print(d("get"))
d("set", 100)
print(d("get"))
