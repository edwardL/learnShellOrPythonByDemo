#include<memory>
#include<stdarg.h>
#include<stdlib.h>
#include<string.h>

#include"netprotocalbuff.h"

#define MAX_MSG_SIZE (8*1024*1024) //最大的消息包不超过8M

char g_protocal_buff[MAX_MSG_SIZE];
int  g_protocal_cur_len;

namespace Protocal
{
   enum
   {
	MT_INVALID = 0;
   }
   class MessageHeader
   {
   public:
	MessageHeader():msg_type(MT_INVALID){}
	MessageHeader(int type):msg_type(type){}
	int msg_type;	
   };
}

void NetProtocalBuff::WriteBegin(int msg_type)
{
	g_protocal_cur_len = sizeof(Protocal::MessageHeader);
	Protocal::MessageHeader *header = (Protocal::MessageHeader*)g_protocal_buff;
	header->msg_type = msg_type;
}

#define PROTOCAL_BUFF_WRITE_VALUE(T)\
	memcpy(g_protocal_buff + g_protocal_cur_len, &v , sizeof(T));
	g_protocal_cur_len += sizeof(T);

void NetProtocalBuff::WriteChar(char v)
{
	PROTOCAL_BUFF_WRITE_VALUE(char);
}

void NetProtocalBuff::WriteUChar(unsigned char v)
{
	PROTOCAL_BUFF_WRITE_VALUE(unsigned char);
}

void NetProtocalBuff::WriteShort(short v)
{
	PROTOCAL_BUFF_WRITE_VALUE(short);
}

void NetProtocalBuff::WriteUShort(unsigned short v)
{
	PROTOCAL_BUFF_WRITE_VALUE(unsigned short);
}

void NetProtocalBuff::WriteInt(int v)
{
	PROTOCAL_BUFF_WRITE_VALUE(int);
}

void NetProtocalBuff::WriteUInt(unsigned int v)
{
	PROTOCAL_BUFF_WRITE_VALUE(unsigned int);
}

void NetProtocalBuff::WriteLL(long long v)
{
	PROTOCAL_BUFF_WRITE_VALUE(long long);
}

void NetProtocalBuff::WriteULL(unsigned long long v)
{
	PROTOCAL_BUFF_WRITE_VALUE(unsigned long long);
}

void NetProtocalBuff::WriteFloat(float v)
{
	PROTOCAL_BUFF_WRITE_VALUE(float);
}

void NetProtocalBuff::WriteDouble(double v)
{
	PROTOCAL_BUFF_WRITE_VALUE(double);
}

void NetProtocalBuff::WriteString(const char* v, int len)
{
	strncpy(g_protocal_buff + g_protocal_cur_len , v , len);
	g_protocal_cur_len += len;
	g_protocal_buff[g_protocal_cur_len - 1] = 0;
}

const char* NetProtocalBuff::GetProtocalBuff()
{
	return g_protocal_buff;
}

int NetProtocalBuff::GetProtocalBuffLen()
{
	return g_protocal_cur_len;
}


////缺少WriteFmt

