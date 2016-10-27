#ifndef NETPROTOCALBUFF_H
#define NETPROTOCALBUFF_H

class NetProtocalBuff
{
public:
	static void WriteBegin(int msg_type);
	static void WriteFmt(const char* fmt, ...);
	static void WriteChar(char v);
	static void WriteUChar(unsigned char v);
	static void WriteShort(short v);
	static void WriteUShort(unsigned short v);
	static void WriteInt(int v);
	static void WriteUInt(unsigned int v);
	static void WriteLL(long long v);
	static void WriteULL(unsigned long long v);
	static void WriteFloat(float v);
	static void WriteDouble(double v);
	static void WriteString(const char *v, int len);
	static const char* GetProtocalBuff();
	static int GetProtocalBuffLen();
};



#endif
