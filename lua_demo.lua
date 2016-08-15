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

function list_iter(t) --- t 是table
	local i = 0
	local n = table.getn(t)
	return function()
		i = i + 1
		if i <= n then return t[i] end
	end
end

t = {10,20,30}
iter = list_iter(t)
while true do
	local element = iter()
	if element == nil then break end
	print(element)
end
print("\n")
t = {10,20,30}
for element in list_iter(t) do
	print(element)
end

----- lua 实现数据结构
--1. 数组, 在lua 中通过整数下标访问。

a = {}
for i = 1, 1000 do
	a[i] = 0
end

squares = {1, 4, 9, 16, 25, 36, 49, 64, 81}

---- n 行 m 列 矩阵
mt = {}
N = 10 
M = 10
for i = 1, N-1 do
	for j = 1, M do
		mt[i*M + j] = i*M + j
	end
end

print("\n")
print_lua_table(mt)

---- 链表， lua 中用table 很容易实现链表，每个节点都是一个table
--根节点
list = nil

-- 在链表的开头插入一个值为v 的节点
list = {next = list, value = "list_node_value"}

-- 要遍历这个链表只需要
local l = list
while l do
	print(l.value)
	l = l.next
end

--- 双向链表
function ListNew()
	return {first = 0, last = -1}
end

List = {}
function List.New()
	return {first = 0, last = -1}
end

-- 可以在常量时间内，完成在队列的两端进行插入删除操作
function List.PushFront(list,value)
	local first = list.first - 1
	list.first = first
	list[first] = value 
end

function List.PushBack(list,value)
	local last = list.last + 1
	list.last = last
	list[last] = value
end



