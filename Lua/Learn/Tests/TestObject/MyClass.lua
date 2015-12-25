local MyClass = 
{
	name = "russell",
	age = 19
}

function MyClass:showName()
	print(self.name)
end

function MyClass:showAge()
	print(self.age)
end

return MyClass
