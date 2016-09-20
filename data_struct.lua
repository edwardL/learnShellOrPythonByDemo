
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

local list = List.New()
List.PushLeft(list,1)
List.PushLeft(list,2)
List.PushRight(list,3)
List.PushRight(list,4)
List.PushLeft(list,0)
print_lua_table(list)








