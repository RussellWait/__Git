--[[
complex = {}

function complex.new (r, i) return {r = r, i = i} end

complex.i = complex.new(0, 1)

function complex.add(c1, c2)
	return complex.new(c1.r+c2.r, c1.i+c2.i)
end

function complex.sub(c1, c2)
	return complex.new(c1.r-r2.r, c1.i-c2.i)
end

--return complex

c1 = complex.new(2, 3)
c2 = complex.new(3, 4)
c3 = complex.add(c1, c2)
--]]

-----------------------------------------------------------------

require "TestComplex"

c1 = complex.new(1, 2)
c2 = complex.new(3, 4)
c3 = complex.add(c1, c2)
pub(c3)


----------------------------------------------------------------

local P = {Old = getfenv()}
ENV = P
setfenv(1, P)

function bbb()
	Old.print("hehe")
	Old.setfenv(1, P.Old)
	print("haha")
end

P.bbb()
