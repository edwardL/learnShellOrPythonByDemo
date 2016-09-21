
function print_lua_table(lua_table,indent)
  indent = indent or 0
  for k,v in pairs(lua_table) do
    if type(k) == "string" then
      k = string.format("%q",k)
    end
    local szSuffix = ""
    if type(v) == "table" then
	szSuffix = "{"
    end
    local szPrefix = string.rep("	",indent)
    formatting = szPrefix .. "[" .. k .. "]" .. "=" ..szSuffix
    if type(v) == "table" then
	print(formatting)
	print_lua_table(v,indent+1)
	print(szPrefix .. "},")
    else
	local szValue =""
	if type(v) =="string" then
	   szValue = string.format("%q",v)
	else
	   szValue = tostring(v)
	end
	print(formatting .. szValue .. ",")
    end
  end
end
----二维数组
mt = {}
N,M = 4,5
for i=1,N do
 mt[i] = {}
 for j = 1, M do
   mt[i][j] = 0
 end
end

print_lua_table(mt)

---链表
list = nil 
list = {next = list,value = 1}

local l = list
while l do
 print(l.value)
 l = l.next
end

---  队列和双端队列
function ListNew()
   return {first = 0, last = -1}
end

List = {}

function List.New()
   return {first = 0, last = -1}
end

function List.PushLeft(list,value)
  local first = list.first - 1
  list.first = first
  list[first] = value 
end

function List.PushRight(list,value)
  local last = list.last + 1
  list.last = last
  list[last] = value
end

function List.PopLeft(list)
  local first = list.first
  if first > list.last then error("list is empty") end
  local value = list[first]
  list[first] = nil
  list.first = first + 1
  return value
end


function List.PopRight(list)
  local last = list.last
  if list.first > last then error("list is empty") end
  local value = list[last]
  list[last] = nil
  list.last = last - 1
  return value
end



local list = List.New()
List.PushLeft(list,1)
List.PushLeft(list,2)
List.PushRight(list,3)
List.PushRight(list,4)
List.PushLeft(list,0)
print_lua_table(list)
print("---------------")
List.PopLeft(list)
List.PopRight(list)
print_lua_table(list)

--------------- 集合和包
function Set(list)
   local set = {}
   for _, v in ipairs(list) do  set[l] = true end
   return set
end

-----序列化
function serialize(o)
 if type(o) == "number" then
   io.write(o)
 elseif type(o) == "string" then
   io.write(string.format("%q",o))
 elseif type(o) == "table" then
    io.write("{\n")
    for k,v in pairs(o) do
      io.write(" ",k, " = ")
      serialize(v)
      io.write(",\n")
    end
    io.write("}\n")
 else
    error("cannot serialize a "..type(o))
 end
end

serialize(list)


print("---------------Metatables and Metamethods")

t = {}
print(getmetatable(t))
t1 = {}
setmetatable(t,t1)
assert(getmetatable(t) == t1)

print("-----------实现继承的方法BaseClass")

print("---------------------")
for n in pairs(_G) do print(n) end

function getfield(f)
   local v = _G
   for w in string.gfind(f,"[%w_]+]") do 
     v = v[w]
   end
   return v
end

if rawget(_G,"Set") == nil then
  print("print nil")
end

complex = {}

function complex.new(r,i) return {r = r, i = i} end

complex.i = complex.new(0,1)

function complex.add(c1,c2)
  return complex.new(c1.r + c2.r, c1.i + c2.i)
end

function complex.sub(c1,c2)
  return complex.new(c1.r - c2.r, c1.i - c2.i)
end

local function checkComplex(c)
   if not ((type(c) == "table") and tonumber(c.r) and tonumber(c.i)) then
     error("bad complex number,3")
   end
end

function BaseClass(super)
 local obj = {}
 setmetatable(obj,{__index = super})
 return obj
end

local s = {a = 1}
local c = c or BaseClass(s)
print("child.a = ",c.a)






