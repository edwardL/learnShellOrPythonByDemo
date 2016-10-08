#include<iostream>
using namespace std;
#include<string>
#include<sstream>
#include<stdio.h>

//将字符串转成基础数据类型
template<class T>
bool StringToBaseType(const std::string& str, T& val)
{
 std::istringstream stream;
 stream.str(str);
 if (stream >> val){
 return true;
 }
 return false;
}

template<class T>
bool BaseTypeToString(const T& src, std::string& tar)
{
 std::ostringstream stream;
 if(stream << src)
 {
   tar = stream.str();
   return true;
 }
 return false;
}

int main()
{
 int a = 11;
 std::string str;
 BaseTypeToString(a,str);
 std::cout<<"a is "<<str;
 
 std::string str2= "1234";
 int val2;
 StringToBaseType(str2,val2);
 printf("\n val2 is %d\n",val2);
 return 0;
}
