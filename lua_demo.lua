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

function print_lua_table (lua_table, indent)

	indent = indent or 0
	for k, v in pairs(lua_table) do
		if type(k) == "string" then
			k = string.format("%q", k)
		end
		local szSuffix = ""
		if type(v) == "table" then
			szSuffix = "{"
		end
		local szPrefix = string.rep("    ", indent)
		formatting = szPrefix.."["..k.."]".." = "..szSuffix
		if type(v) == "table" then
			print(formatting)
			print_lua_table(v, indent + 1)
			print(szPrefix.."},")
		else
			local szValue = ""
			if type(v) == "string" then
				szValue = string.format("%q", v)
			else
				szValue = tostring(v)
			end
			print(formatting..szValue..",")
		end
	end
end

network = {
	{name = "grauna",        IP = "210.26.30.34"},
    {name = "arraial",    IP = "210.26.30.23"},
    {name = "lua",        IP = "210.26.23.12"},
    {name = "derain",        IP = "210.26.23.20"},
}

---  根据name 来排序
table.sort(network,function(a,b)
	return (a.name < b.name)
end)

print_lua_table(network)