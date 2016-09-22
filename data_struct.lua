
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

math.randomseed(os.time())
print(math.random())
print(math.random(10))

--- 数组
print("table len",table.getn{2,3,4})
print("table len with nil", table.getn{10,2,nil})
print("table len with n " , table.getn{10,2,nil; n = 3})
print("table len with n =100",table.getn{n=1000})

a = {}
b = {1,2,3,4,5}
for k,v in ipairs(b)  do
 table.insert(a,v)
end
print_lua_table(a)

print(table.remove(a,4))


function pairsByKeys(t,f)
  local a = {}
  for n in pairs(t) do table.insert(a,n) end
  table.sort(a,f)
  local i = 0
  local iter = function()
    i  = i + 1
    if a[i] == nil then return nil
    else return a[i],t[a[i]]
    end
  end
  return iter
end

a = {'A',"b","C","d"}
table.sort(a,function(a,b) return string.lower(a) < string.lower(b) end)
print_lua_table(a)

s = "[in brackets]"
print(string.sub(s,2,-2))

print(string.format("pi = %.4f",3.1315926))
d = 5; m = 11; y = 1882
print(string.format("%02d/%02d/%04d",d,m,y))

function GetTableSize(t)
 local count = 0
 for _ in pairs(t) do count = count + 1 end
 return count
end

print(GetTableSize({a=1,b=2}))

s = "dead line 20/03/1999 , asdlaa"
date ="%d%d/%d%d/%d%d%d%d"
print(string.sub(s,string.find(s,date)))

function fsize(file)
  local current = file:seek()
  local size = file:seek("end")
  file:seek("set",current)
  return size
end

function createDir(dirname)
  os.execute("mkdir " .. dirname) 
end

----------Debug 库
function test_debug_get_info()
	print_lua_table(debug.getinfo(test_debug_get_info))
	traceback()
end


function traceback()
	local level = 1
	while true do
	   local info = debug.getinfo(level,"Sl")
	   if not info then break end
	   if info.what == "C" then
		print(level,"C func")
	   else
		print(string.format("[%s]:%d",info.short_src,info.currentline))
	   end
	   level = level + 1
	end
end

test_debug_get_info()

print("access local val----------------"
function foo(a,b)
   local x
   do local c = a - b end
   local a = 1
   while true do 
    local name ,value = debug.getlocal(1,a)
    if not name then break end
    print(name,value)
    a = a + 1
   end
end

foo(1,2)
