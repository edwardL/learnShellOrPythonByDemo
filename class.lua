Class = {}
Class.__index = Class

function Class.New(x,y)
	local cls = {}
	setmetatable(cls,Class)
	cls.x = x
	cls.y = y
	return cls
end

function Class:test()
	print(self.x,self.y)
end

object = Class.New(10,20)

object:test()
