#include "stdafx.h"
#ifdef FLOAT256_
#define AppEqual_IgnoreBitsCount 2
namespace LJ
{
	namespace Equation
	{

		//尾数类函数，验证通过
		void FloatData256::operator<<=(long long mov)
		{//
			if(mov<=0)
			{	
				if(mov)*this >>= -mov;
				return;
			}
			if(!(mov&0x3f))
			{
				switch(mov)
				{
				case 64:
					ull[3] = ull[2];ull[2] = ull[1];ull[1] = ull[0];
					ull[0] = 0;
					return;
				case 128:
					ull[3] = ull[1];ull[2] = ull[0];
					ull[1] = ull[0] = 0;
					return;
				case 192:
					ull[3] = ull[0];
					ull[2] = ull[1] = ull[0] = 0;
					return;
				default:
					ull[0] = ull[1] = ull[2] = ull[3] = 0;
				}
				return;
			}
			switch(mov>>6)
			{
			case 0:
				ull[3] = (ull[3]<<mov) | (ull[2]>>(64-mov));
				ull[2] = (ull[2]<<mov) | (ull[1]>>(64-mov));
				ull[1] = (ull[1]<<mov) | (ull[0]>>(64-mov));
				ull[0] <<= mov;
				return;
			case 1:
				ull[3] = (ull[2]<<(mov-64)) | (ull[1]>>(128-mov));
				ull[2] = (ull[1]<<(mov-64)) | (ull[0]>>(128-mov));
				ull[1] = ull[0]<<(mov-64);
				ull[0] = 0;
				return;
			case 2:
				ull[3] = (ull[1]<<(mov-128)) | (ull[0]>>(192-mov));
				ull[2] = ull[0]<<(mov-128);
				ull[1] = ull[0] = 0;
				return;
			case 3:
				ull[3] = ull[0]<<(mov-192);
				ull[2] = ull[1] = ull[0] = 0;
				return;
			default:
				ull[0] = ull[1] = ull[2] = ull[3] = 0;
			}
		}
		void FloatData256::operator>>=(long long mov)
		{
			if(mov<=0)
			{	
				if(mov)*this<<= -mov;
				return;
			}
			if(!(mov&0x3f))//
			{
				switch(mov)
				{
				case 64:
					ull[0] = ull[1];
					ull[1] = ull[2];
					ull[2] = ull[3];
					ull[3] = 0;
					return;
				case 128:
					ull[0] = ull[2];
					ull[1] = ull[3];
					ull[2] = ull[3] = 0;
					return;
				case 192:
					ull[0] = ull[3];
					ull[1] = ull[2] = ull[3] = 0;
					return;
				default:
					ull[0] = ull[1] = ull[2] = ull[3] = 0;
				}
				return;
			}
			switch(mov>>6)
			{
			case 0:
				ull[0] = (ull[0]>>mov) | (ull[1]<<(64-mov));
				ull[1] = (ull[1]>>mov) | (ull[2]<<(64-mov));
				ull[2] = (ull[2]>>mov) | (ull[3]<<(64-mov));
				ull[3] >>= mov;
				return;
			case 1:
				ull[0] = (ull[1]>>(mov-64)) | (ull[2]<<(128-mov));
				ull[1] = (ull[2]>>(mov-64)) | (ull[3]<<(128-mov));
				ull[2] = ull[3]>>(mov-64);
				ull[3] = 0;
				return;
			case 2:
				ull[0] = (ull[2]>>(mov-128)) | (ull[3]<<(192-mov));
				ull[1] = ull[3]>>(mov-128);
				ull[2] = ull[3] = 0;
				return;
			case 3:
				ull[0] = ull[3]>>(mov-192);
				ull[1] = ull[2] = ull[3] = 0;
				return;
			default:
				ull[0] = ull[1] = ull[2] = ull[3] = 0;
			}
		}
		bool FloatData256::operator-=(FloatData256 &data)
		{
			bool sign1,sign2;
			sign1 = ull[0] < data.ull[0];
			ull[0] -= data.ull[0];
			if(sign1)sign2 = ull[1] <= data.ull[1];
			else sign2 = ull[1] < data.ull[1];
			ull[1] -= data.ull[1] + sign1;
			if(sign2)sign1 = ull[2] <= data.ull[2];
			else sign1 = ull[2] < data.ull[2];
			ull[2] -= data.ull[2] + sign2;
			if(sign1)sign2 = ull[3] <= data.ull[3];
			else sign2 = ull[3] < data.ull[3];
			ull[3] -= data.ull[3] + sign1;
			return sign2;
		}
		bool FloatData256::operator+=(FloatData256 &data)
		{
			bool sign1,sign2;
			sign1 = ull[0] > (0xffffffffffffffff ^ data.ull[0]);
			ull[0] += data.ull[0];
			if(sign1)sign2 = ull[1] >= (data.ull[1] ^ 0xffffffffffffffff);
			else sign2 = ull[1] > (data.ull[1] ^ 0xffffffffffffffff);
			ull[1] += data.ull[1] + sign1;
			if(sign2)sign1 = ull[2] >= (data.ull[2] ^ 0xffffffffffffffff);
			else sign1 = ull[2] > (data.ull[2] ^ 0xffffffffffffffff);
			ull[2] += data.ull[2] + sign2;
			if(sign1)sign2 = ull[3] >= (data.ull[3] ^ 0xffffffffffffffff);
			else sign2 = ull[3] > (data.ull[3] ^ 0xffffffffffffffff);
			ull[3] += data.ull[3] + sign1;
			return sign2;
		}
		bool FloatData256::operator++()
		{
			if(0==(++ull[0]))if(0==(++ull[1]))if(0==(++ull[2]))if(0==(++ull[3]))return true;
			return false;
		}
		bool FloatData256::operator--()
		{
			if(0==(ull[0]--))if(0==(ull[1]--))if(0==(ull[2]--))if(0==(ull[3]--))return true;
			return false;
		}
		long long FloatData256::BitsZeroCount()//二分法查找前导0的数量，返回值可能为0~256,已加速
		{
			unsigned long long i,j;
			if(ull[3]){i=ull[3];j=0;}
			else if(ull[2]){i=ull[2];j=64;}
			else if(ull[1]){i=ull[1];j=128;}
			else if(ull[0]){i=ull[0];j=192;}
			else return 256;

			if(    i<0x0000000100000000)//很有意思的感觉，呵呵
			{	if(i<0x0000000000010000)
			{	if(i<0x0000000000000100)
			{	if(i<0x0000000000000010)
			{	if(i<0x0000000000000004)
			{	if(i<0x0000000000000002)return j+63;return j+62;
			}	if(i<0x0000000000000008)return j+61;return j+60;
			}	if(i<0x0000000000000040)
			{	if(i<0x0000000000000020)return j+59;return j+58;
			}	if(i<0x0000000000000080)return j+57;return j+56;
			}	if(i<0x0000000000001000)
			{	if(i<0x0000000000000400)
			{	if(i<0x0000000000000200)return j+55;return j+54;
			}	if(i<0x0000000000000800)return j+53;return j+52;
			}	if(i<0x0000000000004000)
			{	if(i<0x0000000000002000)return j+51;return j+50;
			}	if(i<0x0000000000008000)return j+49;return j+48;
			}	if(i<0x0000000001000000)
			{	if(i<0x0000000000100000)
			{	if(i<0x0000000000040000)
			{	if(i<0x0000000000020000)return j+47;return j+46;
			}	if(i<0x0000000000080000)return j+45;return j+44;
			}	if(i<0x0000000000400000)
			{	if(i<0x0000000000200000)return j+43;return j+42;
			}	if(i<0x0000000000800000)return j+41;return j+40;
			}	if(i<0x0000000010000000)
			{	if(i<0x0000000004000000)
			{	if(i<0x0000000002000000)return j+39;return j+38;
			}	if(i<0x0000000008000000)return j+37;return j+36;
			}	if(i<0x0000000040000000)
			{	if(i<0x0000000020000000)return j+35;return j+34;
			}	if(i<0x0000000080000000)return j+33;return j+32;
			}	if(i<0x0001000000000000)
			{	if(i<0x0000010000000000)
			{	if(i<0x0000001000000000)
			{	if(i<0x0000000400000000)
			{	if(i<0x0000000200000000)return j+31;return j+30;
			}	if(i<0x0000000800000000)return j+29;return j+28;
			}	if(i<0x0000004000000000)
			{	if(i<0x0000002000000000)return j+27;return j+26;
			}	if(i<0x0000008000000000)return j+25;return j+24;
			}	if(i<0x0000100000000000)
			{	if(i<0x0000040000000000)
			{	if(i<0x0000020000000000)return j+23;return j+22;
			}	if(i<0x0000080000000000)return j+21;return j+20;
			}	if(i<0x0000400000000000)
			{	if(i<0x0000200000000000)return j+19;return j+18;
			}	if(i<0x0000800000000000)return j+17;return j+16;
			}	if(i<0x0100000000000000)
			{	if(i<0x0010000000000000)
			{	if(i<0x0004000000000000)
			{	if(i<0x0002000000000000)return j+15;return j+14;
			}	if(i<0x0008000000000000)return j+13;return j+12;
			}	if(i<0x0040000000000000)
			{	if(i<0x0020000000000000)return j+11;return j+10;
			}	if(i<0x0080000000000000)return j+9;return j+8;
			}	if(i<0x1000000000000000)
			{	if(i<0x0400000000000000)
			{	if(i<0x0200000000000000)return j+7;return j+6;
			}	if(i<0x0800000000000000)return j+5;return j+4;
			}	if(i<0x4000000000000000)
			{	if(i<0x2000000000000000)return j+3;return j+2;
			}	if(i<0x8000000000000000)return j+1;return j;
		}
		bool FloatData256::operator>(const FloatData256 &data)const
		{
			if(ull[3]!=data.ull[3])return ull[3]>data.ull[3];
			if(ull[2]!=data.ull[2])return ull[2]>data.ull[2];
			if(ull[1]!=data.ull[1])return ull[1]>data.ull[1];
			return ull[0]>data.ull[0];
		}
		bool FloatData256::operator<(const FloatData256 &data)const
		{
			if(ull[3]!=data.ull[3])return ull[3]<data.ull[3];
			if(ull[2]!=data.ull[2])return ull[2]<data.ull[2];
			if(ull[1]!=data.ull[1])return ull[1]<data.ull[1];
			return ull[0]<data.ull[0];
		}
		bool FloatData256::operator==(const FloatData256 &data)const
		{
			return ull[3]==data.ull[3] && ull[2]==data.ull[2] && ull[1]==data.ull[1] && ull[0]==data.ull[0];
		}
		bool FloatData256::operator!=(const FloatData256 &data)const
		{
			return ull[3]!=data.ull[3] || ull[2]!=data.ull[2] || ull[1]!=data.ull[1] || ull[0]!=data.ull[0];
		}
		bool FloatData256::operator>=(const FloatData256 &data)const
		{
			if(ull[3]!=data.ull[3])return ull[3]>data.ull[3];
			if(ull[2]!=data.ull[2])return ull[2]>data.ull[2];
			if(ull[1]!=data.ull[1])return ull[1]>data.ull[1];
			return ull[0]>=data.ull[0];
		}
		bool FloatData256::operator<=(const FloatData256 &data)const
		{
			if(ull[3]!=data.ull[3])return ull[3]<data.ull[3];
			if(ull[2]!=data.ull[2])return ull[2]<data.ull[2];
			if(ull[1]!=data.ull[1])return ull[1]<data.ull[1];
			return ull[0]<=data.ull[0];
		}

		//Float256类的函数
		const long long Float256::ExpMaxValue=0x007fffffffffffff;
		const long long Float256::ExpMinValue=0xff80000000000000;
		void Float256::BitsMoveLeft(unsigned long long* pull)
		{//已验证
			pull[3] = (pull[3]<<1) | (pull[2]>0x7fffffffffffffff);
			pull[2] = (pull[2]<<1) | (pull[1]>0x7fffffffffffffff);
			pull[1] = (pull[1]<<1) | (pull[0]>0x7fffffffffffffff);
			pull[0] <<= 1;
		}
		void Float256::BitsMoveRight(unsigned long long* pull)
		{//已验证
			if(*pull&1)
			{
				pull[0] = (pull[0]>>1) | (pull[1]<<63);
				pull[1] = (pull[1]>>1) | (pull[2]<<63);
				pull[2] = (pull[2]>>1) | (pull[3]<<63);
				pull[3] >>= 1;
				if(0==++pull[0])if(0==++pull[1])if(0==++pull[2])++pull[3];
				return;
			}
			pull[0] = (pull[0]>>1) | (pull[1]<<63);
			pull[1] = (pull[1]>>1) | (pull[2]<<63);
			pull[2] = (pull[2]>>1) | (pull[3]<<63);
			pull[3] >>= 1;
		}
		unsigned long Float256::BitsMultiply(FloatData256 &dat,FloatData256 &desdat,unsigned long long& num)
		{
			union{unsigned long long ull;unsigned int ui[2];}tmp;

			tmp.ull = dat.ui[0] * num;
			unsigned long t = tmp.ui[0];
			tmp.ull = tmp.ui[1] + dat.ui[1] * num;
			desdat.ui[0] = tmp.ui[0];
			tmp.ull = tmp.ui[1] + dat.ui[2] * num;
			desdat.ui[1] = tmp.ui[0];
			tmp.ull = tmp.ui[1] + dat.ui[3] * num;
			desdat.ui[2] = tmp.ui[0];
			tmp.ull = tmp.ui[1] + dat.ui[4] * num;
			desdat.ui[3] = tmp.ui[0];
			tmp.ull = tmp.ui[1] + dat.ui[5] * num;
			desdat.ui[4] = tmp.ui[0];
			tmp.ull = tmp.ui[1] + dat.ui[6] * num;
			desdat.ui[5] = tmp.ui[0];
			tmp.ull = tmp.ui[1] + dat.ui[7] * num;
			desdat.ull[3] = tmp.ull;
			return t;
		}
		Float256::Float256(double number)//计算100万次Float(1.1)用时0.018秒
		{//验证通过
			unsigned long long num;
			num = *reinterpret_cast<unsigned long long*>(&number);
			if(number!=0)
			{
				Exp = ((0x7ff0000000000000 & num)>>52)-1023;
				Data.ull[3] = num<<11 | 0x8000000000000000;
				if(number>0)
					Sign =1;
				else
					Sign = -1;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(float number)
		{
			unsigned long long num=*reinterpret_cast<unsigned long*>(&number);;
			if(num!=0)
			{
				Exp = ((0x7f800000 & num)>>23)-127;
				Data.ull[3] = (num<<40)|0x8000000000000000;
				if(number>0)
					Sign =1;
				else
					Sign = -1;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(long long number)
		{
			if(number!=0)
			{
				if(number>0)
					Sign =1;
				else
				{
					Sign = -1;
					number = -number;
				}
				int count = XBase::Bits::LeftZeroCount64(number);
				Exp = 63-count;
				Data.ull[3] = number<<count;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(unsigned long long number)
		{
			if(number!=0)
			{
				Sign =1;
				int count = XBase::Bits::LeftZeroCount64(number);
				Exp = 63-count;
				Data.ull[3] = number<<count;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(long number)
		{
			if(number!=0)
			{
				if(number>0)
					Sign =1;
				else
				{
					Sign = -1;
					number = -number;
				}
				int count = XBase::Bits::LeftZeroCount64(number);
				Exp = 63-count;
				Data.ull[3] = unsigned long long(number)<<count;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(unsigned long number)
		{
			if(number!=0)
			{
				Sign =1;
				int count = XBase::Bits::LeftZeroCount64(number);
				Exp = 63-count;
				Data.ull[3] = unsigned long long(number)<<count;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(int number)
		{
			if(number!=0)
			{
				if(number>0)
					Sign =1;
				else
				{
					Sign = -1;
					number = -number;
				}
				int count = XBase::Bits::LeftZeroCount64(number);
				Exp = 63-count;
				Data.ull[3] = unsigned long long(number)<<count;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(unsigned int number)
		{
			if(number!=0)
			{
				Sign =1;
				int count = XBase::Bits::LeftZeroCount64(number);
				Exp = 63-count;
				Data.ull[3] = unsigned long long(number)<<count;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(short number)
		{
			if(number!=0)
			{
				if(number>0)
					Sign =1;
				else
				{
					Sign = -1;
					number = -number;
				}
				int count = XBase::Bits::LeftZeroCount64(number);
				Exp = 63-count;
				Data.ull[3] = unsigned long long(number)<<count;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(unsigned short number)
		{
			if(number!=0)
			{
				Sign =1;
				int count = XBase::Bits::LeftZeroCount64(number);
				Exp = 63-count;
				Data.ull[3] = unsigned long long(number)<<count;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(signed char number)
		{
			if(number!=0)
			{
				if(number>0)
					Sign =1;
				else
				{
					Sign = -1;
					number = -number;
				}
				int count = XBase::Bits::LeftZeroCount64(number);
				Exp = 63-count;
				Data.ull[3] = unsigned long long(number)<<count;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(unsigned char number)
		{
			if(number!=0)
			{
				Sign =1;
				int count = XBase::Bits::LeftZeroCount64(number);
				Exp = 63-count;
				Data.ull[3] = unsigned long long(number)<<count;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(char number)
		{
			if(number!=0)
			{
				if(number>0)
					Sign =1;
				else
				{
					Sign = -1;
					number = -number;
				}
				int count = XBase::Bits::LeftZeroCount64(number);
				Exp = 63-count;
				Data.ull[3] = unsigned long long(number)<<count;
			}
			else 
			{
				Exp = 0;
				Sign = 0;
				Data.ull[3]=0;
			}
			Data.ull[0] = Data.ull[1] = Data.ull[2] = 0;
		}
		Float256::Float256(bool number)
			:Exp(0)
		{
			if(number)
			{
				Data.ull[3]=MinValues::Int64;
				Sign = 1;
			}
			else
			{
				Data.ull[3]=0;
				Sign = 0;
			}
			Data.ull[0]=Data.ull[1]=Data.ull[2]=0;
		}
		Float256::Float256(LPCWSTR pString)
			:Exp(0),Sign(0)
		{
			//清空内容
			Data.Clear();
			LPWSTR numstr=0;
			if(pString==NULL)goto End;
			int Length = VString::Strlen(pString);
			long long len;
			for(len=0;len<Length;++len)
			{
				//如果首位是逗号或者遇到连续两个符号将退出循环
				if(len && (pString[len]==',' || pString[len]=='.'))//点号和逗号前不能出现点号或逗号
				{
					if(pString[len-1]==',' || pString[len-1]=='.')
						break;
					continue;
				}
				if(len && (pString[len]&0xffdf)=='E' && (pString[len-1]&0xffdf)=='E')//两个e
					break;
				if(len && (pString[len]=='+' || pString[len]=='-'))//正负号只能出现在开头或e后面
				{
					if((pString[len-1]&0xffdf)!='E')
						break;
					continue;
				}
				if(pString[len]<='9' && pString[len]>='0')//数字字符
					continue;
				if((pString[len]&0xffdf)>='A' && (pString[len]&0xffdf)<='Z')//字母
					continue;
				if(pString[len]=='.' || pString[len]=='+' || pString[len]=='-' || pString[len]=='_')//其他符号
					continue;
				break;//不支持符号，退出
			}
			if(!len)goto End;//空内容直接为0
			numstr = new wchar_t[size_t(len+1)];
			XBase::Memory::Copy(numstr,pString,size_t(len*2));
			numstr[len] = 0;
			//通过首字初步判断是否属于特殊转换
			if(*numstr =='_' || (((*numstr)&0xffdf)>='A' && ((*numstr)&0xffdf)<='Z'))//以字母开头将进入特殊转换
			{
				if(VString::Strcmp(numstr,L"min")==0||VString::Strcmp(numstr,L"max")==0)
				{
					Exp = 0x007fffffffffffff;
					if(VString::Strcmp(numstr,L"min")==0)Sign = -1;else Sign = 1;
					Data.ull[0] |= MinValues::Int64;
					goto End;
				}
				if(VString::Strcmp(numstr,L"ln2")==0)
				{
					Exp = -1;	Sign = 1;	Data.ull[0] = 0x8a0d175b8baafa2c;Data.ull[1] = 0x40f343267298b62d;Data.ull[2] = 0xc9e3b39803f2f6af;Data.ull[3] = 0xb17217f7d1cf79ab;
					goto End;
				}
				if(0==VString::Strcmp(numstr,L"ln10"))
				{
					Exp = 1;	Sign = 1;	Data.ull[0] = 0x83c61e8201f02d78;Data.ull[1] = 0xe28fecf9da5df90e;Data.ull[2] = 0xea56d62b82d30a28;Data.ull[3] = 0x935d8dddaaa8ac16;
					goto End;
				}
				//e = "2.7182818284590452353602874713526624977572470936999595749669676277240766303536";	
				if(0==VString::Strcmp(numstr,L"e"))
				{
					Exp = 1;Sign = 1;	Data.ull[0] = 0xa9e13641146433fc;Data.ull[1] = 0xd8b9c583ce2d3695;Data.ull[2] = 0xafdc5620273d3cf1;Data.ull[3] = 0xadf85458a2bb4a9a;
					goto End;
				}
				//pi = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862";
				if(0==VString::Strcmp(numstr,L"pi"))
				{
					Exp = 1;Sign = 1;	Data.ull[0] = 0x20bbea63b139b23;Data.ull[1] = 0x29024e088a67cc74;Data.ull[2] = 0xc4c6628b80dc1cd1;Data.ull[3] = 0xc90fdaa22168c234;
					goto End;
				}
				//未能匹配特殊字符串，将进入常规字符串生成：
			}

			long long i,j;//循环用数
			long long num_exp = 0;//指数部分
			long long exp10 = 0;//e后面指数部分
			long long position_point = len;//小数点位置
			long long position_e = len;//e的位置
			//1.寻找结束位置+移除逗号+移除小数点+寻找e的位置
			for(i=j=0;i<len;++i)
			{
				if(numstr[i] == ',')
					continue;
				if(numstr[i] == '.')//小数点位置
				{
					position_point = j;
					continue;
				}
				if(i!=j)
					numstr[j] = numstr[i];
				if((numstr[j]&0xffdf) == 'E')
					position_e = j;
				++j;
			}
			len = j;
			if(position_e>len)//没找到e
				position_e = len;
			if(position_point>position_e)//小数点在e后面或没找到小数点
				position_point = position_e;
			while(j)//检测e前面是否有数值
			{
				--j;
				if(numstr[j]<='9' && numstr[j]>'0')break;
			}
			if(numstr[j]>'9' || numstr[j]<='0')goto End;
			//2.设置exp10mov(移除小数点带来的指数变动)
			//这里不用设置了，因为exp10mov 就是 position_e-position_point;
			//3.整数部分计算,将e前面的字符串的值计算出来，存到*this里面
			for(i=0;i<position_e;++i)
			{
				switch(numstr[i]) 
				{
				case L'1': ++ *this;break;
				case L'2': *this += Two;break;
				case L'3': *this += Three;break;
				case L'4': *this += Four;break;
				case L'5': *this += Five;break;
				case L'6': *this += Six;break;
				case L'7': *this += Seven;break;
				case L'8': *this += Eight;break;
				case L'9': *this += Nine;
				default:break;
				}
				if(1+i<position_e)
					*this = Multiply10();//快速乘10
			}
			//4.计算e后面的数值
			for(i=position_e+1;i<len;++i)
			{
				//如果遇到非数字字符将视为0
				if(numstr[i] >= L'1' && numstr[i]<=L'9')
					num_exp+=numstr[i]-L'0';
				if(1+i<len)
				{
					if(num_exp >= 1000000000)//数值已经溢出
						break;
					num_exp *= 10;
				}
			}
			//5.判断正负号
			if('-' == numstr[0])
				Sign = -1;
			else
				Sign = 1;;
			//6.e后面的指数减去因移除小数点带来的指数变动
			if(position_e<len && '-' == numstr[1+position_e])
				num_exp = -num_exp - (position_e-position_point);
			else
				num_exp -= position_e-position_point;
			//7.将指数的值乘到this中，此过程后要判断溢出
			if(num_exp>0)
			{
				long long texp = 1;
				int tmov=0;
				while(texp<=num_exp)
				{
					if((num_exp&texp)!=0)
					{
						*this = *this * _10e2[tmov];
						num_exp^=texp;
					}
					++tmov;
					texp<<=1;
				}
				if(IsError())
				{
					*this = MaxValue;//溢出返回最大值：2^2147483647
					if(numstr[0] == '-')*this = -(*this);
				}
			}
			else if(num_exp<0)
			{
				num_exp = -num_exp;
				unsigned long long texp = 1;
				int tmov=0;
				while(texp<=(unsigned long long)num_exp)
				{
					if((num_exp&texp)!=0)
					{
						*this = *this / _10e2[tmov];
						num_exp^=texp;
					}
					++tmov;
					texp<<=1;
				}
			}
End:;
			delete []numstr;
		}
		Float256::operator double()const
		{
			if(Equals0())return 0;
			union{unsigned long long ull;double number;}num;
			num.ull=0;
			if(Exp>=-1023)
			{
				if(Exp>1024)
				{
					if(Sign<0)num.ull = 0xfff0000000000000;
					else num.ull = 0x7ff0000000000000;
					return num.number;
				}
				num.ull |= ((unsigned long long)(Exp+1023))<<52;//指数
				if(Sign<0)num.ull |= MinValues::Int64;//负号
				num.ull |= (Data.ull[3]&MaxValues::Int64)>>11;//尾数
				if(Data.ui[6]&0x400)num.ull++;//类似十进制的四舍五入
			}
			return num.number;
		}
		Float256::operator float()const{return float(operator double());}
		Float256::operator long long()const
		{
			if(Exp > 62)
			{
				if(Sign<0)
					return MinValues::Int64;
				return MaxValues::Int64;
			}
			if(Exp <0)
				return 0;
			FloatData256 dat = Data;
			dat<<=63-Exp;
			if(dat.ull[2]>>63)
				dat.ull[3]++;
			if(Sign<0)
				return -(long long)dat.ull[3];
			return dat.ull[3];
		}
		Float256::operator unsigned long long()const
		{
			return unsigned long long (operator long long());
		}
		Float256::operator long()const
		{
			if(Exp > 30)
			{
				if(Sign<0)
					return MinValues::Int32;
				return MaxValues::Int32;
			}
			if(Exp<0)
				return 0;
			FloatData256 dat = Data;
			dat>>=31-Exp;
			if(dat.ui[6]>>31)
				dat.ui[7]++;
			if(Sign<0)
				return -(int)dat.ui[7];
			return dat.ui[7];
		}
		Float256::operator unsigned long()const
		{
			return unsigned long(operator long());
		}
		Float256::operator int()const
		{
			if(Exp > 30)
			{
				if(Sign<0)
					return MinValues::Int32;
				return MaxValues::Int32;
			}
			if(Exp<0)
				return 0;
			FloatData256 dat = Data;
			dat>>=31-Exp;
			if(dat.ui[6]>>31)
				dat.ui[7]++;
			if(Sign<0)
				return -(int)dat.ui[7];
			return dat.ui[7];
		}
		Float256::operator unsigned int()const
		{
			return unsigned int(operator int());
		}
		Float256::operator short()const
		{
			return short(operator int());
		}
		Float256::operator unsigned short()const
		{
			return unsigned short(operator unsigned int());
		}
		Float256::operator signed char()const
		{
			return signed char(operator int());
		}
		Float256::operator unsigned char()const
		{
			return unsigned char(operator unsigned int());
		}
		Float256::operator char()const
		{
			return char(operator int());
		}
		Float256::operator bool()const
		{return !Equals0();}
		Float256 Float256::operator-()const
		{
			return Float256(*this).SelfNegative();
		}
		Float256& Float256::SelfNegative()
		{
			Sign = -Sign;
			return *this;
		}
		Float256& Float256::operator++()
		{
			return *this+=One;
		}
		Float256& Float256::operator--()
		{
			return *this-=One;
		}
		Float256 Float256::operator++(int){Float256 tmp(*this);++(*this);return tmp;}
		Float256 Float256::operator--(int){Float256 tmp(*this);--(*this);return tmp;}
		Float256& Float256::operator+=(Float256 number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(double number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(float number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(long long number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(unsigned long long number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(long number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(unsigned long number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(int number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(unsigned int number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(short number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(unsigned short number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(signed char number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(unsigned char number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(char number)
		{return *this=*this+number;}
		Float256& Float256::operator+=(bool number)
		{return *this=*this+number;}
		Float256 Float256::operator+(Float256 number)const
		{
			Float256 t(*this);//为了线程安全，先取副本
			if(t.Equals0()||number.IsError())return number;//进行错误传递
			if(number.Equals0()||t.IsError())return t;//进行错误传递
			if(number.Exp!=t.Exp){//指数位不同
				if(number.Exp<t.Exp)XBase::Swap(t,number);//使得number的绝对值总是大于t
				if(number.Exp-t.Exp>256)	{
					if(number.Exp-t.Exp==257){
						if(number.Sign==t.Sign){
							if(++number.Data){
								if(number.Exp==ExpMaxValue)
									return number.MakeError(EquationError::PlusExpOverflow);
								++number.Exp;
								number.Data.ull[3]=0x8000000000000000;
							}	}
						else{
							--number.Data;
							if(number.Data.ull[3]<0x8000000000000000){
								if(number.Exp==ExpMinValue)
									return Zero;
								--number.Exp;
								BitsMoveLeft(number.Data.ull);
							}	}	}
					return number;
				}
				if(t.Data.GetBit((number.Exp-t.Exp)-1)){//判断是否发生四舍五入进位
					t.Data>>=number.Exp-t.Exp;
					++t.Data;
				}
				else t.Data>>=number.Exp-t.Exp;
			}

			if(number.Sign==t.Sign){//符号位相同
				if(number.Data+=t.Data){
					if(number.Exp==ExpMaxValue)
						return number.MakeError(EquationError::PlusExpOverflow);
					number.Exp++;
					BitsMoveRight(number.Data.ull);
					number.Data.ull[3]|=0x8000000000000000;
				}
				return number;
			}
			if(number.Data<t.Data)XBase::Swap(number,t);
			number.Data-=t.Data;
			long long mov = number.Data.BitsZeroCount();
			if(mov==256 || (number.Exp-mov)<ExpMinValue)return Zero;
			number.Exp-=mov;
			number.Data<<=mov;
			return number;
		}
		Float256 Float256::operator+(double number)const
		{return operator+(Float256(number));}
		Float256 Float256::operator+(float number)const
		{
			return operator+(double(number));
		}
		Float256 Float256::operator+(long long number)const
		{return operator+(Float256(number));}
		Float256 Float256::operator+(unsigned long long number)const
		{return operator+(Float256(number));}
		Float256 Float256::operator+(long number)const
		{
			return operator+(long long(number));
		}
		Float256 Float256::operator+(unsigned long number)const
		{
			return operator+(unsigned long long(number));
		}
		Float256 Float256::operator+(int number)const
		{
			return operator+(long(number));
		}
		Float256 Float256::operator+(unsigned int number)const
		{
			return operator+(unsigned long(number));
		}
		Float256 Float256::operator+(short number)const
		{
			return operator+(long(number));
		}
		Float256 Float256::operator+(unsigned short number)const
		{
			return operator+(unsigned long(number));
		}
		Float256 Float256::operator+(signed char number)const
		{
			return operator+(long(number));
		}
		Float256 Float256::operator+(unsigned char number)const
		{
			return operator+(unsigned long(number));
		}
		Float256 Float256::operator+(char number)const
		{
			return operator+(long(number));
		}
		Float256 Float256::operator+(bool number)const
		{
			Float256 tmp(*this);
			if(number)return ++tmp;
			return tmp;
		}

		//减法重载
		Float256& Float256::operator-=(Float256 number)
		{
			return *this=*this-number;
		}
		Float256& Float256::operator-=(double number)
		{
			if(IsError())return *this;
			*this+=-number;
			if(IsError())MakeError(EquationError::MinusExpOverflow);
			return *this;
		}
		Float256& Float256::operator-=(float number)
		{
			if(IsError())return *this;
			*this+=-number;
			if(IsError())MakeError(EquationError::MinusExpOverflow);
			return *this;
		}
		Float256& Float256::operator-=(long long number)
		{
			if(IsError())return *this;
			if(number==MinValues::Int64)*this+=(unsigned long long)MinValues::Int64;
			else *this+=-number;
			if(IsError())MakeError(EquationError::MinusExpOverflow);
			return *this;
		}
		Float256& Float256::operator-=(unsigned long long number)
		{
			return *this-=Float256(number);
		}
		Float256& Float256::operator-=(long number)
		{
			return *this-=Float256(number);
		}
		Float256& Float256::operator-=(unsigned long number)
		{
			return *this-=Float256(number);
		}
		Float256& Float256::operator-=(int number)
		{
			return *this-=Float256(number);
		}
		Float256& Float256::operator-=(unsigned int number)
		{
			return *this-=Float256(number);
		}
		Float256& Float256::operator-=(short number)
		{
			return *this-=Float256(number);
		}
		Float256& Float256::operator-=(unsigned short number)
		{
			return *this-=Float256(number);
		}
		Float256& Float256::operator-=(signed char number)
		{
			return *this-=Float256(number);
		}
		Float256& Float256::operator-=(unsigned char number)
		{
			return *this-=Float256(number);
		}
		Float256& Float256::operator-=(char number)
		{
			return *this-=Float256(number);
		}
		Float256& Float256::operator-=(bool number)
		{
			if(number)--*this;
			return *this;
		}
		Float256 Float256::operator-(Float256 number)const
		{
			if(IsError())return*this;
			if(number.IsError())return number;
			Float256 tmp(*this+(-number));
			if(tmp.IsError())return tmp.MakeError(EquationError::MinusExpOverflow);
			return tmp;
		}
		Float256 Float256::operator-(double number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(float number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(long long number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(unsigned long long number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(long number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(unsigned long number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(int number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(unsigned int number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(short number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(unsigned short number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(signed char number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(unsigned char number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(char number)const
		{return *this-Float256(number);}
		Float256 Float256::operator-(bool number)const
		{
			if(number)
				return *this-One;
			return *this;
		}
		//乘法重载
		Float256 Float256::Multiply(Float256 number)const//标准乘法
		{//验证通过
			if(IsError())return *this;
			if(number.IsError())return number;
			if(Equals0() || number.Equals0())return Zero;
			Float256 num;
			long long mov,i,j,s,k;

			union {unsigned long long ull;unsigned int ui[2];} tmp,
				sum[15],//乘积低32位
				usum[15];//乘积高32位

			for(i=14;i>=0;i--)//由14到0求和。
			{
				s = 14-i;//下标和
				sum[i].ull = usum[i].ull = 0;//置零
				j = k = 7>s?s:7;
				while(s<=k+j)//分段求和
				{
					tmp.ull =((unsigned long long) Data.ui[j]) * number.Data.ui[s-j];
					sum[i].ull += (unsigned long long)tmp.ui[0];//低32位
					usum[i].ull += (unsigned long long)tmp.ui[1];//高32位
					--j;
				}
				usum[i].ull += sum[i].ui[1];
				if(i<14)
				{
					usum[1+i].ull += sum[i].ui[0];
					usum[i].ull += usum[1+i].ui[1];
				}
			}
			num.Data.ui[0] = usum[7].ui[0];
			num.Data.ui[1] = usum[6].ui[0];
			num.Data.ui[2] = usum[5].ui[0];
			num.Data.ui[3] = usum[4].ui[0];
			num.Data.ui[4] = usum[3].ui[0];
			num.Data.ui[5] = usum[2].ui[0];
			num.Data.ui[6] = usum[1].ui[0];
			num.Data.ui[7] = usum[0].ui[0];

			mov = usum[0].ui[0] >> 31;//为0时须左移,为1时有进位
			if(mov+Exp+number.Exp<ExpMinValue)//乘积太小
				return Zero;
			if(mov+Exp+number.Exp>ExpMaxValue)//乘积溢出错误
			{
				return number.MakeError(EquationError::MultiplyExpOverflow);
			}
			num.Exp = Exp+number.Exp+mov;
			if(!mov)
			{
				BitsMoveLeft(num.Data.ull);
				num.Data.ui[0] |= usum[8].ui[0] >> 31;//补上
				if(usum[8].ui[0] & 0x40000000)//精度校正
					if(++num.Data)
					{
						if(num.Exp==ExpMaxValue)return num.MakeError(EquationError::MultiplyExpOverflow);
						++num.Exp;
						num.Data.ull[3] |= MinValues::LongLong;
					}
			}
			else if(usum[8].ui[0] >> 31)//精度校正
				if(++num.Data)
				{
					if(num.Exp==ExpMaxValue)return num.MakeError(EquationError::MultiplyExpOverflow);
					++num.Exp;
					num.Data.ull[3] |= MinValues::LongLong;
				}
				num.Sign = Sign==number.Sign?1:-1;
				return num;
		}
		Float256 Float256::Multiply10()const//快速乘10,计算100万次1.1.Multiply10()用时0.1010秒
		{
			return Float256(*this).SelfMultiply10();
		}
		Float256& Float256::SelfMultiply10()
		{
			if(IsError() || Equals0())return *this;
			if(Exp+3<=ExpMaxValue)
				Exp += 3;//乘8
			else
				return MakeError(EquationError::MultiplyExpOverflow);
			FloatData256 fd = Data;
			fd>>=2;
			if(Data.ull[0]&0x2)++fd;
			if(Data += fd)
			{
				if(Exp ==ExpMaxValue)
					return MakeError(EquationError::MinusExpOverflow);
				Exp++;
				BitsMoveRight(Data.ull);
				Data.ull[3] |= MinValues::Int64;
			}
			return *this;
		}
		Float256& Float256::operator*=(Float256 number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(double number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(float number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(long long number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(unsigned long long number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(long number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(unsigned long number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(int number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(unsigned int number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(short number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(unsigned short number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(signed char number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(unsigned char number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(char number)
		{return *this = *this*number;}
		Float256& Float256::operator*=(bool number)
		{if(IsError())return *this;if(number)return *this;return *this=Zero;}
		Float256 Float256::operator*(Float256 number)const
		{//试验通过
			Float256 num,t(*this);
			if(t.IsError())return t;
			if(number.IsError())return number;
			if(t.Equals0() || number.Equals0())return Zero;
			long long mov,i,j,s,k;

			union {unsigned long long ull;unsigned int ui[2];}
			tmp,
				sum[9],//乘积低32位
				usum[9];//乘积高32位

			for(i=8;i>=0;i--)//由7到0求和
			{
				s = 14-i;//下标和
				sum[i].ull = usum[i].ull = 0;//置零
				j = k = 7>s?s:7;
				while(s<=k+j)//分段求和
				{
					tmp.ull =((unsigned long long) t.Data.ui[j]) * number.Data.ui[s-j];
					sum[i].ull += (unsigned long long)tmp.ui[0];//低32位
					usum[i].ull += (unsigned long long)tmp.ui[1];//高32位
					--j;
				}
				usum[i].ull += sum[i].ui[1];
				if(i<8)
				{
					usum[1+i].ull += sum[i].ui[0];
					usum[i].ull += usum[1+i].ui[1];
				}
			}
			num.Data.ui[0] = usum[7].ui[0];
			num.Data.ui[1] = usum[6].ui[0];
			num.Data.ui[2] = usum[5].ui[0];
			num.Data.ui[3] = usum[4].ui[0];
			num.Data.ui[4] = usum[3].ui[0];
			num.Data.ui[5] = usum[2].ui[0];
			num.Data.ui[6] = usum[1].ui[0];
			num.Data.ui[7] = usum[0].ui[0];

			mov = usum[0].ui[0] >(unsigned int)MaxValues::Int32;//为0时须左移,为1时有进位
			if(mov+t.Exp+number.Exp<ExpMinValue)//乘积太小
				return Zero;
			if(mov+t.Exp+number.Exp>ExpMaxValue)//乘积溢出错误
				return number.MakeError(EquationError::MultiplyExpOverflow);
			num.Exp = t.Exp+number.Exp+mov;
			if(!mov)	{
				BitsMoveLeft(num.Data.ull);
				if(usum[8].ui[0]>(unsigned long)MaxValues::Int32)num.Data.ui[0] |= 1;//补上
				if((usum[8].ui[0] & 0x40000000)>0)//精度校正
					if(++num.Data){
						if(num.Exp==ExpMaxValue)return num.MakeError(EquationError::MultiplyExpOverflow);
						++num.Exp;
						num.Data.ull[3] |= MinValues::Int64;
					}
			}
			else
				if(usum[8].ui[0] > unsigned long(MaxValues::Int32))//精度校正
					if(++num.Data){
						if(num.Exp==ExpMaxValue)return num.MakeError(EquationError::MultiplyExpOverflow);
						++num.Exp;
						num.Data.ull[3] |= MinValues::Int64;
					}
					num.Sign = (t.Sign==number.Sign)?1:-1;
					return num;
		}
		Float256 Float256::operator*(double number)const
		{//试验通过
			Float256 t(*this);
			if(t.IsError())return t;
			if(t.Equals0() || number==0)
				return Zero;
			Float256 num;
			Float256 n(number);
			char mov,i,j,s,k;

			union {unsigned long long ull;unsigned int ui[2];}
			tmp,
				sum[9],//乘积低32位
				usum[9];//乘积高32位

			for(i=8;i>=0;i--)//由7到0求和
			{
				s = 14-i;//下标和
				sum[i].ull = usum[i].ull = 0;//置零
				for(j = k = 7>s?s:7;s<=k+j && j>5;j--)//分段求和
				{
					tmp.ull =((unsigned long long) t.Data.ui[s-j]) * n.Data.ui[j];
					sum[i].ull += (unsigned long long)tmp.ui[0];//低32位
					usum[i].ull += (unsigned long long)tmp.ui[1];//高32位
				}
				usum[i].ull += sum[i].ui[1];
				if(i!=8)
				{
					usum[1+i].ull += sum[i].ui[0];
					usum[i].ull += usum[1+i].ui[1];
				}
			}
			num.Data.ui[0] = usum[7].ui[0];
			num.Data.ui[1] = usum[6].ui[0];
			num.Data.ui[2] = usum[5].ui[0];
			num.Data.ui[3] = usum[4].ui[0];
			num.Data.ui[4] = usum[3].ui[0];
			num.Data.ui[5] = usum[2].ui[0];
			num.Data.ui[6] = usum[1].ui[0];
			num.Data.ui[7] = usum[0].ui[0];

			mov = usum[0].ui[0] >> 31;//为0时须左移,为1时有进位
			if(t.Exp+n.Exp+mov<ExpMinValue)//乘积太小
				return Zero;
			if(t.Exp+n.Exp+mov>ExpMaxValue)//乘积溢出,返回无穷大
			{
				if(t.Sign == n.Sign)return MaxValue;
				return MinValue;
			}
			if(t.Exp+n.Exp+mov>ExpMaxValue)
				return num.MakeError(EquationError::MultiplyExpOverflow);
			num.Exp = t.Exp+n.Exp+mov;
			if(!mov)
			{
				Float256::BitsMoveLeft(num.Data.ull);
				num.Data.ui[0] |= usum[8].ui[0] >> 31;//补上
				if(usum[8].ui[0] & 0x40000000)//精度校正
					if(++num.Data)
					{
						if(num.Exp==ExpMaxValue)return num.MakeError(EquationError::MultiplyExpOverflow);
						++num.Exp;
						num.Data.ull[3] |= MinValues::Int64;
					}
			}
			else if(usum[8].ui[0] >unsigned long(MaxValues::Int32))//精度校正
			{
				if(++num.Data)
				{
					if(num.Exp==ExpMaxValue)return num.MakeError(EquationError::MultiplyExpOverflow);
					++num.Exp;
					num.Data.ull[3] |= MinValues::Int64;
				}
			}
			num.Sign = (t.Sign==n.Sign)?1:-1;
			return num;
		}
		Float256 Float256::operator*(float number)const
		{return *this*double(number);}
		Float256 Float256::operator*(long long number)const
		{
			if(number== MinValues::Int64)return (*this*unsigned long long(MinValues::Int64)).SelfNegative();
			return (number>0)?*this*unsigned long long(number):(*this*unsigned long long(-number)).SelfNegative();
		}
		Float256 Float256::operator*(unsigned long long number)const
		{//实验通过
			Float256 t(*this);
			if(t.IsError() || t.Equals0())return t;
			if(number<=MaxValues::UnsignedLong)return operator*(unsigned long(number));
			unsigned long long uh = number>>32;
			unsigned long long ul = unsigned long(number);
			number = t.Data.ui[0]*ul;//2^-255
			unsigned long long th=0,tl=number;
			union {unsigned long long ull;unsigned long ui[2];} tt;

			for(int i=0;i<7;++i)
			{
				tt.ull = t.Data.ui[i]*uh;
				tl= tt.ui[0] + (tl>>32) + th;
				th=tt.ui[1];
				tt.ull = t.Data.ui[i+1]*ul;
				tl+=tt.ui[0]; th+=tt.ui[1];
				t.Data.ui[i] = unsigned long(tl);
			}
			th+=t.Data.ui[7]*uh+ (tl>>32);
			t.Data.ui[7] = 0;
			unsigned long bCount = Bits::LeftZeroCount64(th);
			if(t.Exp+64-bCount>ExpMaxValue)return t.MakeError(EquationError::MinusExpOverflow);
			t.Exp+=64-bCount;
			if(t.Data.GetBit(31-bCount))
			{
				t.Data>>=32-bCount;
				t.Data.ull[3] |= th<<bCount;
				if(++t.Data)
				{
					if(t.Exp==ExpMaxValue)return t.MakeError(EquationError::MultiplyExpOverflow);
					t.Exp++;
					t.Data.ui[7]=MinValues::Long;
				}
				return t;
			}
			t.Data>>=32-bCount;
			t.Data.ull[3] |= th<<bCount;
			return t;
		}
		Float256 Float256::operator*(long number)const
		{
			if(number== MinValues::Int32)return (*this*unsigned long(MinValues::Int32)).SelfNegative();
			return (number>0)?*this*unsigned long(number):(*this*unsigned long(-number)).SelfNegative();
		}
		Float256 Float256::operator*(unsigned long number)const
		{
			Float256 t(*this);
			if(t.IsError() || t.Equals0())return t;
			if(number==0)return Zero;
			unsigned long long tmp; 
			tmp=unsigned long long(t.Data.ui[0])*number;
			t.Data.ui[0] = unsigned long(tmp);
			tmp>>=32;
			tmp+=unsigned long long(t.Data.ui[1])*number;
			t.Data.ui[1] = unsigned long(tmp);
			tmp>>=32;
			tmp+=unsigned long long(t.Data.ui[2])*number;
			t.Data.ui[2] = unsigned long(tmp);
			tmp>>=32;
			tmp+=unsigned long long(t.Data.ui[3])*number;
			t.Data.ui[3] = unsigned long(tmp);
			tmp>>=32;
			tmp+=unsigned long long(t.Data.ui[4])*number;
			t.Data.ui[4] = unsigned long(tmp);
			tmp>>=32;
			tmp+=unsigned long long(t.Data.ui[5])*number;
			t.Data.ui[5] = unsigned long(tmp);
			tmp>>=32;
			tmp+=unsigned long long(t.Data.ui[6])*number;
			t.Data.ui[6] = unsigned long(tmp);
			tmp>>=32;
			tmp+=unsigned long long(t.Data.ui[7])*number;
			t.Data.ui[7] = unsigned long(tmp);
			long long mov = Bits::LeftZeroCount64(tmp);
			if(mov>32)return Zero;
			if(t.Exp+32-mov>ExpMaxValue)return t.MakeError(EquationError::MinusExpOverflow);
			t.Exp+=32-mov;
			if(mov<32 && (t.Data.ui[0]&(0x80000000>>mov))>0)
			{
				t.Data>>=32-mov;
				t.Data.ull[3] |= (tmp&0xffffffff00000000)<<mov;
				++t.Data;
			}
			else
			{
				t.Data>>=32-mov;
				t.Data.ull[3] |= (tmp&0xffffffff00000000)<<mov;
			}
			return t;
		}
		Float256 Float256::operator*(int number)const
		{return *this*long(number);}
		Float256 Float256::operator*(unsigned int number)const
		{return *this*unsigned long(number);}
		Float256 Float256::operator*(short number)const
		{return *this*long(number);}
		Float256 Float256::operator*(unsigned short number)const
		{return *this*unsigned long(number);}
		Float256 Float256::operator*(signed char number)const
		{return *this*long(number);}
		Float256 Float256::operator*(unsigned char number)const
		{return *this*unsigned long(number);}
		Float256 Float256::operator*(char number)const
		{return *this*long(number);}
		Float256 Float256::operator*(bool number)const
		{
			if(IsError() || number)return *this;
			return Zero;
		}
		//除法重载
		Float256 Float256::Divide(Float256 number)const//标准除法，计算100万次1.1/10.1用时13.73秒
		{
			if(IsError())return *this;
			if(number.Equals0())
				return number.MakeError(EquationError::Divide0);//若除数等于0则产生错误
			if(Equals0())return Zero;
			long long mov = 0;
			Float256 num;
			num.Data.Clear();
			FloatData256 dat = Data;
			unsigned long long flag = 0;
			if(dat<number.Data)
			{
				flag=dat.ull[3];
				mov = -1;
				BitsMoveLeft(dat.ull);
			}
			for(long long i=0;i<256;++i)//逐位生商
			{
				if(flag>unsigned long long(MaxValues::LongLong) || dat>=number.Data)
				{
					dat-=number.Data;
					num.Data.ull[3^(i>>6)] |= (unsigned long long)1<<(63^(0x3f&i));//12次试验试验发现略快于switch方法
					/*switch(i>>6)
					{
					case 0:num.data.ull[3] |= (unsigned long long)1<<(0x3f^i);break;
					case 1:num.data.ull[2] |= (unsigned long long)1<<(0x7f^i);break;
					case 2:num.data.ull[1] |= (unsigned long long)1<<(0xbf^i);break;
					default:num.data.ull[0] |= (unsigned long long)1<<(0xff^i);
					}*/
				}
				flag = dat.ull[3];
				BitsMoveLeft(dat.ull);
			}
			if(flag>unsigned long long(MaxValues::LongLong) || dat>=number.Data)//有进位
				++num.Data;
			num.Sign = Sign == number.Sign?1:-1;
			mov += Exp - number.Exp;
			if(mov>ExpMaxValue)
			{//产生溢出错误
				return num.MakeError(EquationError::DivideExpOverflow);
			}
			if(mov<ExpMinValue)
			{//太小，返回0
				return Zero;
			}
			num.Exp = mov;
			return num;
		}
		Float256 Float256::Half()const
		{
			Float256 t(*this);
			if(t.IsError())return t;
			if(t.Exp==ExpMinValue || t.Equals0())return Zero;
			t.Exp--;
			return t;
		}
		Float256& Float256::SelfHalf()
		{
			if(!IsError())
			{
				if(Exp==ExpMinValue || Equals0())*this = Zero;
				else Exp--;
			}
			return *this;
		}
		Float256& Float256::operator/=(Float256 number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(double number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(float number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(long long number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(unsigned long long number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(long number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(unsigned long number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(int number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(unsigned int number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(short number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(unsigned short number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(signed char number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(unsigned char number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(char number)
		{return *this=*this/number;}
		Float256& Float256::operator/=(bool number)
		{return *this=*this/number;}
		Float256 Float256::operator/(Float256 number)const
		{//试验通过，x64下计算100万次平均时间1.0秒
			Float256 t(*this);//为确保线程安全，先取副本
			if(t.IsError())return t;//错误传递
			if(number.IsError())return number;
			if(number.Equals0())//若除数等于0则产生错误
				return t.MakeError(EquationError::Divide0);
			if(t.Equals0())return t;
			long long mov = -1;
			Float256 num(Zero);
			FloatData256 dat = t.Data;
			FloatData256 dat1;
			unsigned long long flag = number.Data.ui[7]+1;
			unsigned long long q;
			unsigned long tl = 0;
			int tf;
			for(int i=7;i>=0;--i)
			{
				if(dat>=number.Data)
				{
					dat-=number.Data;
					for(int j=i+1;j<8;++j)
						if(++num.Data.ui[j]!=0)break;
				}
				q = dat.ull[3]/flag;
				tl = BitsMultiply(number.Data,dat1,q);
				dat -= dat1;
				tf = dat.ui[7];
				if(tl!=0)
				{
					--dat;
					dat<<=32;
					dat.ui[0] = -long(tl);
				}
				else dat <<= 32;
				while(tf!=0)
				{
					q++;
					if(dat -= number.Data)--tf;
				}
				num.Data.ui[i] = unsigned long(q);
			}
			if(dat>=number.Data)
			{
				dat-=number.Data;
				for(int j=0;j<4;++j)
					if(++num.Data.ull[j]!=0)break;
			}
			if(t.Data>=number.Data)
			{
				mov = 0;
				BitsMoveRight(num.Data.ull);
				num.Data.ull[3] |= 0x8000000000000000;
			}
			else if(dat.ull[3]>unsigned long long(MaxValues::LongLong) || (dat.ull[3]<<1)>=number.Data.ull[3])++num.Data;

			num.Sign = t.Sign == number.Sign?1:-1;
			mov += t.Exp - number.Exp;
			if(mov>ExpMaxValue)
			{//产生溢出错误
				return num.MakeError(EquationError::DivideExpOverflow);
			}
			if(mov<ExpMinValue)
			{//太小，返回0
				return Zero;
			}
			num.Exp = mov;
			return num;
		}
		Float256 Float256::operator/(double number)const
		{
			return operator/(Float256(number));
		}
		Float256 Float256::operator/(float number)const
		{
			return operator/(double(number));
		}
		Float256 Float256::operator/(long long number)const
		{
			if(IsError())return *this;
			if(number==MinValues::LongLong)return -operator/(unsigned long long(number));
			return -operator/(unsigned long long(-number));
		}
		Float256 Float256::operator/(unsigned long long number)const
		{//试验通过，x64下计算100万次平均时间0.6秒
			Float256 t(*this);
			if(t.IsError())return t;
			if(number==0)return t.MakeError(EquationError::Divide0);
			if(t.Equals0())return t;

			Float256 num(Zero);
			FloatData256 dat = t.Data;
			FloatData256 dat1;
			long long mov = Bits::LeftZeroCount64(number);
			number <<= mov;
			mov -=64;
			unsigned long long flag = (number>>32) + ((number&0xffffffff)>0);
			unsigned long long q;
			for(int i=7;i>=0;--i)
			{
				if(dat.ull[3]>=number)
				{
					dat.ull[3]-=number;
					for(int j=i+1;j<8;++j)
						if(++num.Data.ui[j]!=0)break;
				}
				q = dat.ull[3]/flag;
				union{unsigned long long ull;unsigned int ui[2];}tmp;
				tmp.ull = (number&0xffffffff) * q;
				dat1.ull[0]=dat1.ull[1]=dat1.ull[2]=0;
				dat1.ui[5] = tmp.ui[0];
				tmp.ull = tmp.ui[1] + (number>>32) * q;
				dat1.ull[3] = tmp.ull;
				dat -= dat1;
				unsigned int tf = dat.ui[7];
				dat <<= 32;
				while(tf!=0)
				{
					q++;
					if(dat.ull[3] < number)--tf;
					dat.ull[3] -= number;
				}
				num.Data.ui[i] = unsigned long(q);
			}
			if(dat.ull[3]>=number)
			{
				dat.ull[3]-=number;
				for(int j=0;j<4;++j)
					if(++num.Data.ull[j]!=0)break;
			}
			if(t.Data.ull[3]>=number)
			{
				mov++;
				BitsMoveRight(num.Data.ull);
				num.Data.ull[3] |= 0x8000000000000000;
			}
			else if(dat.ull[3]>unsigned long long(MaxValues::LongLong) || (dat.ull[3]<<1)>=number)++num.Data;
			num.Sign = t.Sign;
			mov += t.Exp;
			if(mov>ExpMaxValue)
			{//产生溢出错误
				return num.MakeError(EquationError::DivideExpOverflow);
			}
			if(mov<ExpMinValue)
			{//太小，返回0
				return Zero;
			}
			num.Exp = mov;
			return num;
		}
		Float256 Float256::operator/(long number)const
		{
			if(IsError())return *this;
			if(number==MinValues::Long)return -operator/(unsigned long(number));
			if(number<0)return -operator/(unsigned long(-number));
			return operator/(unsigned long(number));
		}
		Float256 Float256::operator/(unsigned long number)const
		{//x64下计算100万次平均时间0.6秒
			Float256 t(*this);
			if(t.IsError())return t;
			if(number==0)return t.MakeError(EquationError::Divide0);
			if(t.Equals0())return t;
			long long bCount = Bits::LeftZeroCount64(number)-32;
			number<<=bCount;
			bCount = 32-bCount;//bCount为number的exp
			bool te = t.Data.ui[7]>=number;
			unsigned long long tmp;
			tmp = t.Data.ull[3]%number;
			t.Data.ui[7] = unsigned long(t.Data.ull[3]/number);
			tmp = (tmp<<32) | unsigned long(t.Data.ui[5]);
			t.Data.ui[6] = unsigned long(tmp/number);
			tmp %= number;
			tmp = (tmp<<32) | unsigned long(t.Data.ui[4]);
			t.Data.ui[5] = unsigned long(tmp/number);
			tmp %= number;
			tmp = (tmp<<32) | unsigned long(t.Data.ui[3]);
			t.Data.ui[4] = unsigned long(tmp/number);
			tmp %= number;
			tmp = (tmp<<32) | unsigned long(t.Data.ui[2]);
			t.Data.ui[3] = unsigned long(tmp/number);
			tmp %= number;
			tmp = (tmp<<32) | unsigned long(t.Data.ui[1]);
			t.Data.ui[2] = unsigned long(tmp/number);
			tmp %= number;
			tmp = (tmp<<32) | unsigned long(t.Data.ui[0]);
			t.Data.ui[1] = unsigned long(tmp/number);
			tmp %= number;
			tmp<<=32;
			t.Data.ui[0] = unsigned long(tmp/number);
			if(t.Exp-bCount+te<ExpMinValue)return Zero;
			t.Exp-=bCount-te;
			if(te)
			{
				BitsMoveRight(t.Data.ull);
				t.Data.ull[3]|=unsigned long long(MinValues::LongLong);
			}
			else
			{
				if(tmp%number>=number/2)
				{
					++t.Data;
				}
			}
			return t;
		}
		Float256 Float256::operator/(int number)const
		{
			return operator/(long(number));
		}
		Float256 Float256::operator/(unsigned int number)const
		{
			return operator/(unsigned long(number));
		}
		Float256 Float256::operator/(short number)const
		{
			return operator/(long(number));
		}
		Float256 Float256::operator/(unsigned short number)const
		{
			return operator/(unsigned long(number));
		}
		Float256 Float256::operator/(signed char number)const
		{
			return operator/(long(number));
		}
		Float256 Float256::operator/(unsigned char number)const
		{
			return operator/(unsigned long(number));
		}
		Float256 Float256::operator/(char number)const
		{
			return operator/(long(number));
		}
		Float256 Float256::operator/(bool number)const
		{
			Float256 tmp(*this);
			if(tmp.IsError() || number)return tmp;
			return tmp.MakeError(EquationError::Divide0);
		}
		//逻辑运算符
		bool Float256::operator!()const{return Equals0();}
		//比较运算符
		bool Float256::operator>(const Float256& number)const
		{
			if(Sign!=number.Sign)return Sign>number.Sign;
			if(Exp!=number.Exp)return Sign>0?(Exp>number.Exp):Exp<number.Exp;
			return Sign>0?Data>number.Data:Data<number.Data;
		}
		bool Float256::operator>(double number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(float number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(unsigned long long number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(long long number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(unsigned long number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(long number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(unsigned int number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(int number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(unsigned short number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(short number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(unsigned char number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(signed char number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(char number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator>(bool number)const
		{
			return operator>(Float256(number));
		}
		bool Float256::operator<(const Float256& number)const
		{
			if(Sign!=number.Sign)return Sign<number.Sign;
			if(Exp!=number.Exp)return Sign<0?(Exp>number.Exp):Exp<number.Exp;
			return Sign<0?Data>number.Data:Data<number.Data;
		}
		bool Float256::operator<(double number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(float number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(unsigned long long number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(long long number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(unsigned long number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(long number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(unsigned int number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(int number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(unsigned short number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(short number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(unsigned char number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(signed char number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(char number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator<(bool number)const
		{
			return operator<(Float256(number));
		}
		bool Float256::operator==(const Float256& number)const
		{
			return Exp==number.Exp && Data==number.Data && Sign==number.Sign;
		}
		bool Float256::operator==(double number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(float number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(unsigned long long number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(long long number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(unsigned long number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(long number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(unsigned int number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(int number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(unsigned short number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(short number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(unsigned char number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(signed char number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(char number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator==(bool number)const
		{
			return operator==(Float256(number));
		}
		bool Float256::operator>=(const Float256& number)const
		{
			if(Sign!=number.Sign)return Sign>number.Sign;
			if(Exp!=number.Exp)return Sign>0?(Exp>number.Exp):Exp<number.Exp;
			return Sign>0?Data>=number.Data:Data<=number.Data;
		}
		bool Float256::operator>=(double number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(float number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(unsigned long long number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(long long number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(unsigned long number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(long number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(unsigned int number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(int number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(unsigned short number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(short number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(unsigned char number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(signed char number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(char number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator>=(bool number)const
		{
			return operator>=(Float256(number));
		}
		bool Float256::operator<=(const Float256& number)const
		{
			if(Sign!=number.Sign)return Sign<number.Sign;
			if(Exp!=number.Exp)return Sign<0?(Exp>number.Exp):Exp<number.Exp;
			return Sign<0?Data>=number.Data:Data<=number.Data;
		}
		bool Float256::operator<=(double number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(float number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(unsigned long long number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(long long number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(unsigned long number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(long number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(unsigned int number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(int number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(unsigned short number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(short number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(unsigned char number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(signed char number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(char number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator<=(bool number)const
		{
			return operator<=(Float256(number));
		}
		bool Float256::operator!=(const Float256& number)const
		{
			return Exp!=number.Exp || Data!=number.Data || Sign!=number.Sign;
		}
		bool Float256::operator!=(double number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(float number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(unsigned long long number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(long long number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(unsigned long number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(long number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(unsigned int number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(int number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(unsigned short number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(short number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(unsigned char number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(signed char number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(char number)const
		{
			return operator!=(Float256(number));
		}
		bool Float256::operator!=(bool number)const
		{
			return operator!=(Float256(number));
		}
		//开平方
		Float256 Float256::Sqrt()const
		{
			Float256 num(*this);
			if(num.Equals0() || num.IsError())return num;
			if(num.Sign <0)return num.MakeError(EquationError::SqrtLessThan0);
			if(num.Equals(One))return num;
			Float256 num1 = num;
			num1.Exp/=2;//近似值
			Float256 num2 = num / num1;
			while(!num1.AppEquals(num2))//牛顿迭代
			{
				num1 = (num1+num2).SelfHalf();
				num2 = num/num1;
			}
			return num2;
		}
		//取绝对值
		Float256 Float256::Abs()const
		{
			if(Sign>=0)return *this;
			return -*this;
		}
		//自身取绝对值
		Float256& Float256::SelfAbs()
		{
			if(IsError() || Sign>=0)return *this;
			Sign = -Sign;
			return *this;
		}
		//求余(>=0),商保存到quotient里，余数与number同号；number<0时向上取整，number>0时向下取整
		Float256 Float256::Mod(Float256 number,Float256 &quotient)const
		{
			Float256 num(*this);
			if(num.IsError())return num;
			if(number.IsError())return number;
			if(number.Equals0())//若等于0则生成错误
			{
				return number.MakeError(EquationError::ModDivide0);
			}
			if(num.Equals0())//若等于0则返回0
			{
				quotient = Zero;
				return Zero;
			}
			if(num.Abs()<number.Abs())//绝对值比除数的绝对值小
			{
				if(number.Sign == num.Sign)
				{
					quotient = Zero;
					return num;
				}
				quotient = -One;//-1
				return num+number;
			}
			if(num.Exp - number.Exp > 255)//远大于除数,余数将无法确定
			{
				quotient = num/number;
				return Zero;
			}
			long long mov = 0;//提前位移
			long long bmov = num.Exp - number.Exp;//求商位移
			long long flag = 0;
			quotient.Data.Clear();
			FloatData256 dat = num.Data;
			long long i;
			if(dat<number.Data){flag=1;mov=1;BitsMoveLeft(dat.ull);}
			bmov -= mov;
			for(i=0;i<bmov;++i)
			{	
				if(flag || dat>=number.Data)//生商
				{	
					dat-=number.Data;
					switch(i>>6)
					{
					case 0:quotient.Data.ull[3] |= (unsigned long long)1<<(0x3f^i);break;
					case 1:quotient.Data.ull[2] |= (unsigned long long)1<<(0x7f^i);break;
					case 2:quotient.Data.ull[1] |= (unsigned long long)1<<(0xbf^i);break;
					default:break;
					}
					if(!dat)break;//没得算了
				}
				flag = dat.ull[3] > unsigned long long(MaxValues::Int64);
				BitsMoveLeft(dat.ull);//挪一位
			}
			if(i==bmov && (flag || dat>=number.Data))
			{//商最后一位
				dat-=number.Data;
				quotient.Data.ui[7^(i>>5)] |= 1<<(31^(0x1f&i));
			}
			quotient.Exp = num.Exp - number.Exp - mov;
			quotient.Sign = num.Sign == number.Sign?1:-1;
			if(!dat)//整除
				return Zero;
			//得到的data为按同为正数算出的余数
			num.Data=dat;
			bmov =num.Data.BitsZeroCount();
			num.Exp = num.Exp - i - mov - bmov;
			num.Data <<= bmov;
			if(num.Abs().AppEquals(number.Abs()))
			{
				if(quotient.Sign>0)++quotient;
				else --quotient;
				return Zero;
			}
			if(Sign != number.Sign)//异号
			{
				num = num + number;
				--quotient;//商为负值
			}
			return num;
		}
		//求余
		Float256 Float256::Mod(Float256 number)const
		{
			Float256 num(*this);
			if(num.IsError())return num;
			if(number.IsError())return number;
			if(number.Equals0())
				return number.MakeError(EquationError::ModDivide0);//求余除以0错误
			if(Equals0())return Zero;//若等于0则返回0
			if(num.Abs()<number.Abs())//绝对值比除数的绝对值小
			{
				if(number.Sign == num.Sign)
					return num;
				return num+number;
			}
			if(num.Exp > number.Exp + 255)//远大于除数,余数将无法确定
				return Zero;
			long long mov = 0;//提前位移
			long long bmov = num.Exp - number.Exp;//求商位移
			long long flag = 0;
			FloatData256 dat = num.Data;
			long long i;
			if(dat<number.Data){flag=1;mov=1;Float256::BitsMoveLeft(dat.ull);}
			bmov -= mov;
			for(i=0;i<bmov;++i)
			{	
				if(flag || dat>=number.Data)//生商
				{	
					dat-=number.Data;
					if(!dat)break;//没得算了
				}
				flag = dat.ull[3] > unsigned long long(MaxValues::Int64);
				BitsMoveLeft(dat.ull);//挪一位
			}
			if(i==bmov && (flag || dat>=number.Data))
			{//商最后一位
				dat -= number.Data;
			}
			if(!dat.ull[3])//整除
				return Zero;
			num.Data = dat;
			bmov = num.Data.BitsZeroCount();
			num.Exp = num.Exp - i - mov - bmov;
			num.Data <<= bmov;
			if(num.Abs().AppEquals(number.Abs()))
				return Zero;
			if(num.Sign != number.Sign)
				num += number;
			return num;
		}
		//返回该数以number为底的对数
		Float256 Float256::Log(Float256 number)const
		{
			return Ln()/number.Ln();
		}
		//返回该数以10为底的对数
		Float256 Float256::Lg()const
		{
			return Ln()/Ln10;
		}
		//返回该数以e为底的对数
		Float256 Float256::Ln()const
		{
			if(IsError())return *this;
			Float256 num_x;//记录x
			Float256 num_xn;//记录x^n
			num_x = *this;
			int ln2 = Exp;//exp偏移
			Float256 ln_plus=Zero;

			if(num_x<=Zero)return num_x.MakeError(EquationError::LnLessOrEqual0);
			num_x.Exp = 0;//使得num_x变为1.xxx
			for(int i=1;i<24;++i)//取值为24时加速效果较好
				if(num_x>=_2sqrt2[i])
				{
					num_x /= _2sqrt2[i];
					ln_plus += _ln2sqrt2[i];
				}

				num_x.Data.ull[3]&=MaxValues::LongLong;
				long long mov = num_x.Data.BitsZeroCount();
				if(mov==256)return ln_plus+ Ln2*ln2;
				num_x.Exp-=mov;
				num_x.Data<<=mov;

				num_xn = num_x;

				Float256 num_1 = num_x;//初始值
				Float256 num_2 = -One;//循环赋值
				for(int i=2;;i++)//泰勒展开叠加
				{
					num_xn = -num_xn*num_x;
					num_1 += num_xn/i;
					if(num_1.AppEquals(num_2))break;
					num_2 = num_1;
				}
				num_1 += ln_plus;
				if(ln2)return num_1 + Ln2*ln2;
				return num_1;
		}
		//返回该数以2为底的对数
		Float256 Float256::Log2()const
		{
			return Ln()/Ln2;
		}
		//返回e的该数次幂
		Float256 Float256::Expe()const
		{
			if(IsError())return *this;
			Float256 num_x,num_xn,num_factorial,num_1,num_2;
			if(Exp>=22)
			{
				if(Sign<0)
					return Zero;
				num_x =*this;
				return num_x.MakeError(EquationError::ExpEOverflow);
			}

			num_x = Mod(Ln2,num_factorial);
			int expmov = (int)num_factorial;
			int i;
			num_factorial = One;
			num_xn = num_x;
			num_1 = One + num_xn;
			num_2 = num_1;
			for(i=2;;i++)
			{
				num_xn = num_xn * num_x;
				num_factorial = num_factorial*i;
				num_1 += num_xn / num_factorial;
				if(num_1.AppEquals(num_2))break;
				num_2 = num_1;
			}
			if(expmov)num_1.Exp+=expmov;
			return num_1;
		}
		//返回2的该数次幂
		Float256 Float256::Exp2()const
		{
			if(IsError())return *this;
			Float256 num_x,num_xn,num_factorial,num_1,num_2;
			if(Exp>=31)
			{
				if(Sign<0)
					return Zero;
				num_x = *this;
				return num_x.MakeError(EquationError::Exp2Overflow);
			}

			num_x = GetDecimalPart();
			int expmov = (int)GetIntegerPart();
			num_x = num_x*Ln2;
			int i;
			num_factorial = One;
			num_xn = num_x;
			num_1 = One+num_x;
			num_2 = num_1;
			for(i=2;;i++)
			{
				num_xn *= num_x;
				num_factorial = num_factorial*i;
				num_1 += num_xn/num_factorial;
				if(num_1.AppEquals(num_2))break;
				num_2 = num_1;
			}
			if(expmov)num_1.Exp+=expmov;
			return num_1;
		}
		//返回该数的number次幂
		Float256 Float256::Pow(Float256 number)const
		{
			if(IsError())return(*this);
			if(number.IsError())return number;
			if(*this<=Zero)
			{
				Float256 num = *this;
				if(Equals0()&& number.Equals0())return num.MakeError(EquationError::Pow00);
				if(number.GetDecimalPart().Equals0())//整数次方
				{
					if(number.Half().GetDecimalPart())return -(Abs().Log2()*number).Exp2();
					return (Abs().Log2()*number).Exp2();
				}
				return num.MakeError(EquationError::PowLessThan0);
			}
			return (Log2()*number).Exp2();//使用Exp2来算
			//return this->Abs().Ln()*(number).Exp();//使用Exp来算
		}
		//取正弦(弧度制)
		Float256 Float256::Sin()const
		{
			if(IsError())return *this;
			Float256 num_x,num_xn,num_factorial,num_1,num_2,sum;
			num_x = Mod(Pi,num_factorial);//除以π以判断正负
			bool negative = int(num_factorial)&1;//商为奇数说明结果为负
			num_x = num_x.Mod(_pi_half2,num_factorial);//除以π/4以判断操作方法
			switch((int)num_factorial)
			{
			case 1://45~90°
				if(num_x.Equals0())//返回(根号2)/2
				{
					if(negative)return -_sqrt2_half;
					return _sqrt2_half;
				}
				num_x = _pi_half2 - num_x;//cos收敛速度快
				if(negative)return -num_x.Cos();
				return num_x.Cos();
			case 2://90~135°
				if(num_x.Equals0())
				{
					if(negative)return -One;
					return One;
				}
				if(negative)
					return -num_x.Cos();
				return num_x.Cos();
			case 3://135~180°
				num_x = _pi_half2 - num_x;
			default:
				break;
			}
			num_factorial = One;//阶乘
			num_xn = num_x;
			sum = num_x;
			num_1 = num_x;
			num_2 = num_x;
			num_x *= num_x;
			int i;
			for(i=2;;i++)//Sin x = x-x^3/3!+x^5/5!-
			{
				num_factorial = num_factorial*i;
				if(i&1)
				{
					num_xn *= num_x;
					num_factorial.SelfNegative();
					sum += num_xn/num_factorial;
					if(sum.AppEquals(num_1))break;
					num_1 = sum;
				}
			}
			if(negative)return -sum;
			return sum;
		}
		//取正弦(角度制)
		Float256 Float256::Dsin()const
		{
			return ((*this) * _pi_180).Sin();
		}
		//取余弦(弧度制)
		Float256 Float256::Cos()const
		{
			if(IsError())return *this;
			Float256 num_x,num_xn,num_factorial,num_1,num_2,sum;
			num_x = this->Mod(Pi,num_factorial);//除以π以供判断正负
			bool negative = int(num_factorial)&1;//商为奇时negative为true
			num_x = num_x.Mod(_pi_half2,num_factorial);//除以π/4以判断操作方法
			switch(int(num_factorial))
			{
			case 1://45~90°
				if(num_x.Equals0())
				{
					if(negative)return -_sqrt2_half;
					return _sqrt2_half;
				}
				num_x = _pi_half2 - num_x;
				if(negative)return -num_x.Sin();
				return num_x.Sin();
			case 2://90~135°
				if(num_x.Equals0())
				{
					return Zero;
				}
				if(negative)return num_x.Sin();
				return -num_x.Sin();
			case 3:
				negative = !negative;
				num_x = _pi_half2 - num_x;
			default:
				break;
			}
			num_factorial = One;//阶乘
			num_xn = One;
			sum = One;
			num_1 = One;
			num_2 = num_1;
			num_x *= num_x;//变x方
			int i;
			for(i=2;;i++)//Cosx = 1-x^2/2!+x^4/4!-
			{
				num_factorial = num_factorial*i;
				if(i&1)continue;
				num_xn = num_xn*num_x;
				num_factorial.SelfNegative();//变换符号
				sum += num_xn/num_factorial;
				if(num_1.AppEquals(sum))break;
				num_1 = sum;
			}
			if(negative)return -sum;
			return sum;
		}
		//取余弦(角度制)
		Float256 Float256::Dcos()const
		{
			return ((*this)*_pi_180).Cos();
		}
		//取正切(弧度制)
		Float256 Float256::Tan()const
		{
			if(IsError())return *this;
			Float256 num = Cos();
			if(num.Equals0())return num.MakeError(EquationError::Tan);
			return Sin()/num;
		}
		//取正切(角度制)
		Float256 Float256::Dtan()const
		{
			return Dsin()/Dcos();
		}
		//取余切(弧度制)
		Float256 Float256::Cot()const
		{
			if(IsError())return *this;
			Float256 num = Sin();
			if(num.Equals0())return num.MakeError(EquationError::Cot);
			return Cos()/num;
		}
		//取余切(角度制)
		Float256 Float256::Dcot()const
		{
			if(IsError())return *this;
			Float256 num = Dsin();
			if(num.Equals0())return num.MakeError(EquationError::Cot);
			return Dcos()/num;
		}
		//反正弦(弧度制)
		Float256 Float256::Arcsin()const
		{
			if(IsError())return *this;
			Float256 num_x,num_xn;//x、xn
			Float256 num1,num2;//分子、分母
			Float256 num_1,num_2;//前一项、后一项
			num_x = Abs();//取绝对值
			if(Abs()>One)
				return num_x.MakeError(EquationError::Arcsin);//出错
			if(num_x>_sqrt2_half)//大于(根号2)/2
			{//为了加速收敛，转换成π/2－。。。
				if(Sign<0)//(π/2)-arcsin(sqrt(1-x^2))
					return(-_pi_half+(One-num_x*num_x).SelfAbs().Sqrt().Arcsin());
				return(_pi_half-((One-num_x*num_x).SelfAbs().Sqrt().Arcsin()));
			}
			num1 = num2 = One;
			num_xn = num_2 = num_1 = num_x;
			num_x *= num_x;
			int i;
			for(i=2;;i++)//arcsin x = x + 1/2*x^3/3 + 1*3/(2*4)*x^5/5 + ……(|x|<1) 
			{
				if(i&1)num1 = num1*(i-2);//奇数
				else
				{
					num2 = num2*i;//偶数
					continue;
				}
				num_xn = num_xn*num_x;
				num_1 += (num_xn*num1/num2)/i;
				if(num_1.AppEquals(num_2))break;
				num_2 = num_1;
			}
			if(Sign<0)return -num_1;
			return num_1;
		}
		//反正弦(角度制)
		Float256 Float256::Darcsin()const
		{
			return Arcsin()/_pi_180;
		}
		//反余弦(弧度制)
		Float256 Float256::Arccos()const
		{
			if(IsError())return *this;
			if(Abs()>One)
			{
				Float256 num = *this;
				return num.MakeError(EquationError::Arccos);//出错
			}
			if(*this < _sqrt2_half)return _pi_half-Arcsin();//小于根号2/2，这样计算可以在接近1时获得较高的精度
			return (One-*this**this).SelfAbs().Sqrt().Arcsin();//取正值
		}
		//反余弦(角度制)
		Float256 Float256::Darccos()const
		{
			return Arccos()/_pi_180;
		}
		//反正切(弧度制)
		Float256 Float256::Arctan()const
		{
			if(IsError())return *this;
			//配方法：tanx=sinx/cosx，设cosx>0，则sinx = this/sqrt(this平方+1)，转为求arcsin,但此方法在x趋于0时精度大减
			if(Abs()>_sqrt2_half)return (*this/((*this**this+One).SelfAbs().Sqrt())).Arcsin();
			//级数法：arctan x = x - x^3/3 + x^5/5 - ... (x≤1) ，x趋于1时收敛太慢
			Float256 num_x,num_xn;//x、xn
			Float256 num = Three;//分母
			Float256 num_1,num_2;//前一项、后一项
			num_x = -*this**this;
			num_xn = (*this)*num_x;
			num_2 = num_1 = *this;
			int i;
			for(i=3;;i+=2)
			{
				num_1 += num_xn/i;
				if(num_1.AppEquals(num_2))break;
				num_2 = num_1;
				num_xn *= num_x;
			}
			return num_1;
		}
		//反正切(角度制)
		Float256 Float256::Darctan()const
		{
			return Arctan()/_pi_180;
		}
		//比较是否相等
		bool Float256::Equals(const Float256& number)const
		{
			return Exp==number.Exp && Data==number.Data && Sign==number.Sign;
		}
		//约等于,符号不同返回false.忽略位数末count位，比较是否等于
		bool Float256::AppEquals(const Float256& number)const
		{
			if(number.Sign!=Sign)
				return false;
			Float256 num1,num2;
			if(Exp>number.Exp)
			{
				num1 = (*this);
				num2 = number;
			}
			else
			{
				num2 = (*this);
				num1 = number;
			}
			if(num1.Exp-num2.Exp>1)
				return false;
			num2.Data >>= num1.Exp-num2.Exp;
			if(num1.Data>num2.Data)
				num1.Data-=num2.Data;
			else
			{
				num2.Data-=num1.Data;
				num1 = num2;
			}
			if(AppEqual_IgnoreBitsCount>=192)
				return !((num1.Data.ull[3]&0x7fffffffffffffff)>>(AppEqual_IgnoreBitsCount&0x3f));
			if(num1.Data.ull[3])return false;
			if(AppEqual_IgnoreBitsCount>=128)
				return !(num1.Data.ull[2]>>(AppEqual_IgnoreBitsCount&0x3f));
			if(num1.Data.ull[2])return false;
			if(AppEqual_IgnoreBitsCount>=64)
				return !(num1.Data.ull[1]>>(AppEqual_IgnoreBitsCount&0x3f));
			if(num1.Data.ull[1])return false;
			return !(num1.Data.ull[0]>>AppEqual_IgnoreBitsCount);
		}
		//生成[0,1)区间的随机数
		Float256& Float256::Rand()
		{
			if(IsError())return *this;
			static XRandom x1,x2;

			Exp=-1;
			Sign = 1;
			Data.ull[0] = ((Data.ull[0]<<1) | (Data.ull[0]>>63)) + Data.ull[1] + x1.Rand();
			Data.ull[1] = ((Data.ull[1]<<11) | (Data.ull[1]>>53)) + Data.ull[2] + x2.Rand();
			Data.ull[2] = ((Data.ull[2]<<21) | (Data.ull[2]>>43)) + Data.ull[3] + x1.Rand();
			Data.ull[3] = ((Data.ull[3]<<29) | (Data.ull[3]>>35)) + Data.ull[0] + x2.Rand();
			long long bitsCount = Data.BitsZeroCount();
			if(bitsCount==256)
				return *this=Zero;
			Data<<=bitsCount;
			Exp-=bitsCount;
			return *this;
		}
		//返回整数部分
		Float256 Float256::GetIntegerPart()const
		{
			if(IsError() || Exp>=255)return *this;
			if(Exp<0)
				return Zero;
			Float256 num = *this;
			num.Data>>=255-Exp;
			num.Data<<=255-Exp;
			return num;
		}
		//自身取整(小数部分全舍)
		Float256& Float256::SelfGetIntegerPart()
		{
			if(IsError() || Exp>=255)return *this;
			if(Exp<0)
				return *this = Zero;
			Data>>=255-Exp;
			Data<<=255-Exp;
			return *this;
		}
		//返回小数部分
		Float256 Float256::GetDecimalPart()const
		{
			if(IsError() || Exp<0)return *this;
			if(Exp>=255)
				return Zero;
			Float256 num = *this;
			num.Data<<=1+Exp;
			long long mov = num.Data.BitsZeroCount();
			if(256 == mov)
				return Zero;
			num.Data <<= mov;
			num.Exp = -1 -mov;
			return num;
		}
		//自身取小数部分
		Float256& Float256::SelfGetDecimalPart()
		{
			if(IsError() || Exp<0)return *this;
			if(Exp>=255)
				return *this = Zero;
			Data<<=1+Exp;
			long long  mov = Data.BitsZeroCount();
			if(256 == mov) return *this = Zero;
			Data <<= mov;
			Exp = -1 - mov;
			return *this;
		}
		XString Float256::ToString(int length)const
		{
			long long i=0;
			wchar_t* tmpstr = NULL;//临时字符串
			if(Equals0())
				return L"0";
			if(IsError())//错误信息输出
			{
				switch(Sign)
				{
				case EquationError::PlusExpOverflow: return L"运行加法时发生指数溢出";
				case EquationError::MinusExpOverflow: return L"运行减法时发生指数溢出";
				case EquationError::MultiplyExpOverflow:return L"运行乘法时发生指数溢出";
				case EquationError::Divide0: return L"运行除法时发生除以0错误";
				case EquationError::DivideExpOverflow: return L"运行除法时发生指数溢出";
				case EquationError::ModDivide0: return L"运行求余时发生除以0错误";
				case EquationError::ExpEOverflow: return L"求e的x次幂时发生指数溢出";
				case EquationError::Exp2Overflow: return L"求2的x次幂时发生指数溢出";
				case EquationError::Arcsin: return L"求arcsin时发生输入数据错误";
				case EquationError::Arccos:return L"求arccos时发生输入数据错误";
				case EquationError::Tan: return L"求Tan时发生被0除错误";
				case EquationError::Cot:return L"求Cot时发生被0除错误";
				case EquationError::LnLessOrEqual0: return L"求对数时发生真数<=0错误";
				case EquationError::SqrtLessThan0: return L"求开平方时发生被开方数小于0错误";
				case EquationError::PowLessThan0: return L"求x次幂时发生底数小于0错误";
				case EquationError::Pow00: return L"求x次幂时发生0的0次方错误";
				default: return L"未知错误";
				}
			}
			Float256 num= *this;
			unsigned char k;
			long long j,position,exp10;
			i = j = position = 0;
			exp10 = -1; 
			unsigned char number[80];//最长精度为77,80位已经足够了
			if(length<=0 ||length >79)length = 76;
			if(Exp>=0)//加速处理
			{
				unsigned long long texp = 0x10000000000000;
				int exp_mov = 53;
				while(exp_mov-->0)
				{
					if(num.Exp>=_10e2[exp_mov].Exp)
					{
						num/=_10e2[exp_mov];
						exp10+=texp;
					}
					texp>>=1;
				}
				num/=10;
				exp10++;
			}
			if(Exp<=-332)
			{
				unsigned long long texp = 0x10000000000000;
				int exp_mov = 53;
				while(exp_mov-->0)
				{
					if(num.Exp<-_10e2[exp_mov].Exp)
					{
						num*=_10e2[exp_mov];
						exp10-=texp;
					}
					texp>>=1;
				}
			}
			num.SelfAbs();
			if(!num.Equals0())
				for(;;)
				{
					k = (unsigned char)(num.SelfMultiply10()).GetIntegerPart();
					if(k)num.SelfGetDecimalPart();
					if(!k && !position)//确保首位非0
					{
						exp10--;//十进制指数减小
						continue;
					}
					else if(10 == k)//避免0.999999事件
					{
						k = 0;
						for(i=position-1;i>=0;--i)
						{
							if(9>number[i])
							{
								number[i]++;
								break;
							}
							number[i] = 0;
						}
						if(i<0)//进位到开头
						{
							number[position] = 0;
							position++;
							exp10++;
							number[0] = 1;
						}
					}
					number[position] = k;//字符串赋值
					if(position>=length)//进位校正(这里设定精度位数)
					{
						if(number[position]>4)//四舍五入，有进位操作
							number[position-1]++;
						number[position] = 0;
						--position;
						while(position>0)
						{
							if(number[position]>9)//需要进位
							{
								number[position-1]++;
								number[position] = 0;
							}
							else if(number[position])break;//作这个判断是为了多0情况下消除0
							--position;
						}
						if(number[0]>9)//开头要进位
						{
							number[0] = 1;
							exp10++;
						}
						break;
					}
					++position;
				}
				if(exp10>=0 && position>exp10)//小数点夹在其中
				{
					tmpstr = new wchar_t[size_t(position+4)];
					for(i=0;i<=position;++i)
					{
						if(i == 1+exp10)
						{
							tmpstr[i] = L'.';
							++j;
						}
						tmpstr[j] = number[i] + L'0';
						++j;
					}
					tmpstr[j] = 0;
				}
				else if(position==exp10)//无需修改
				{
					tmpstr = new wchar_t[size_t(position+3)];
					for(i=0;i<=position;++i)
						tmpstr[i] = number[i] + L'0';
					tmpstr[i] = 0;
				}
				else if(position<exp10 && position+4>exp10)//末尾补0,+4代表末位最多出现3个0
				{
					tmpstr = new wchar_t[size_t(position+3+exp10-position)];
					for(i=0;i<=position;++i)
						tmpstr[i] = number[i] + L'0';
					for(j=0;j<exp10-position;++j)
						tmpstr[i+j] = L'0';
					tmpstr[i+j] = 0;
				}
				else if(exp10<0 && exp10>-4)//小数，前面0较少，不用科学计数法
				{
					tmpstr = new wchar_t[size_t(position+4-exp10)];
					for(i=0;i<1-exp10;++i)
						tmpstr[i] = L'0';
					tmpstr[1] = L'.';
					for(j=0;j<=position;++j)
						tmpstr[i+j] = number[j]+L'0';
					tmpstr[i+j] = 0;
				}
				else//科学计数法
				{
					tmpstr = new wchar_t[size_t(position+41)];
					for(i=0;i<=position;++i)
					{
						if(i==1)
						{
							tmpstr[j] = L'.';
							++j;
						}
						tmpstr[j] = L'0' + number[i];
						++j;
					}
					tmpstr[j] = L'e';
					++j;
					if(exp10<0)
					{
						tmpstr[j] = L'-';
						++j;
						exp10 = -exp10;
					}
					for(i=0;exp10;++i)
					{
						tmpstr[j+i] = exp10 % 10+L'0';
						exp10/=10;
					}
					tmpstr[j+i] = 0;
					--i;
					while(i>0)
					{
						k = (unsigned char)tmpstr[j];
						tmpstr[j] = tmpstr[j+i];
						tmpstr[j+i] = k;
						i-=2;
						j++;
					}
				}
				i = VString::Strlen(tmpstr);
				if(Sign<0)
				{
					j=++i;
					while(j>0){tmpstr[j]=tmpstr[j-1];--j;}
					*tmpstr = L'-';
				}
				return new VString(int(i),tmpstr,NULL);
		}
		const Float256 Float256::Zero(0);
		const Float256 Float256::One(1);
		const Float256 Float256::Two(2);
		const Float256 Float256::Three(3);
		const Float256 Float256::Four(4);
		const Float256 Float256::Five(5);
		const Float256 Float256::Six(6);
		const Float256 Float256::Seven(7);
		const Float256 Float256::Eight(8);
		const Float256 Float256::Nine(9);
		const Float256 Float256::Ten(10);
		const Float256 Float256::_10e2[53] = {Float256(10.0),_10e2[0].Multiply(_10e2[0]),_10e2[1].Multiply(_10e2[1]),_10e2[2].Multiply(_10e2[2]),_10e2[3].Multiply(_10e2[3]),_10e2[4].Multiply(_10e2[4]),_10e2[5].Multiply(_10e2[5]),_10e2[6].Multiply(_10e2[6]),
			_10e2[7].Multiply(_10e2[7]),_10e2[8].Multiply(_10e2[8]),_10e2[9].Multiply(_10e2[9]),_10e2[10].Multiply(_10e2[10]),_10e2[11].Multiply(_10e2[11]),_10e2[12].Multiply(_10e2[12]),_10e2[13].Multiply(_10e2[13]),_10e2[14].Multiply(_10e2[14]),
			_10e2[15].Multiply(_10e2[15]),_10e2[16].Multiply(_10e2[16]),_10e2[17].Multiply(_10e2[17]),_10e2[18].Multiply(_10e2[18]),_10e2[19].Multiply(_10e2[19]),_10e2[20].Multiply(_10e2[20]),_10e2[21].Multiply(_10e2[21]),_10e2[22].Multiply(_10e2[22]),
			_10e2[23].Multiply(_10e2[23]),_10e2[24].Multiply(_10e2[24]),_10e2[25].Multiply(_10e2[25]),_10e2[26].Multiply(_10e2[26]),_10e2[27].Multiply(_10e2[27]),_10e2[28].Multiply(_10e2[28]),_10e2[29].Multiply(_10e2[29]),_10e2[30].Multiply(_10e2[30]),
			_10e2[31].Multiply(_10e2[31]),_10e2[32].Multiply(_10e2[32]),_10e2[33].Multiply(_10e2[33]),_10e2[34].Multiply(_10e2[34]),_10e2[35].Multiply(_10e2[35]),_10e2[36].Multiply(_10e2[36]),_10e2[37].Multiply(_10e2[37]),_10e2[38].Multiply(_10e2[38]),
			_10e2[39].Multiply(_10e2[39]),_10e2[40].Multiply(_10e2[40]),_10e2[41].Multiply(_10e2[41]),_10e2[42].Multiply(_10e2[42]),_10e2[43].Multiply(_10e2[43]),_10e2[44].Multiply(_10e2[44]),_10e2[45].Multiply(_10e2[45]),_10e2[46].Multiply(_10e2[46]),
			_10e2[47].Multiply(_10e2[47]),_10e2[48].Multiply(_10e2[48]),_10e2[49].Multiply(_10e2[49]),_10e2[50].Multiply(_10e2[50]),_10e2[51].Multiply(_10e2[51])
		};
		const Float256 Float256::Ln2 = Float256(L"ln2");
		const Float256 Float256::Ln10 = Float256(L"ln10");
		//2开根号x次 : 2^(1/(2^x))，x为0~63
		const Float256 Float256::_2sqrt2[32] = {Float256(2.0),_2sqrt2[0].Sqrt(),_2sqrt2[1].Sqrt(),_2sqrt2[2].Sqrt(),_2sqrt2[3].Sqrt(),
			_2sqrt2[4].Sqrt(),_2sqrt2[5].Sqrt(),_2sqrt2[6].Sqrt(),_2sqrt2[7].Sqrt(),_2sqrt2[8].Sqrt(),
			_2sqrt2[9].Sqrt(),_2sqrt2[10].Sqrt(),_2sqrt2[11].Sqrt(),_2sqrt2[12].Sqrt(),_2sqrt2[13].Sqrt(),
			_2sqrt2[14].Sqrt(),_2sqrt2[15].Sqrt(),_2sqrt2[16].Sqrt(),_2sqrt2[17].Sqrt(),_2sqrt2[18].Sqrt(),
			_2sqrt2[19].Sqrt(),_2sqrt2[20].Sqrt(),_2sqrt2[21].Sqrt(),_2sqrt2[22].Sqrt(),_2sqrt2[23].Sqrt(),
			_2sqrt2[24].Sqrt(),_2sqrt2[25].Sqrt(),_2sqrt2[26].Sqrt(),_2sqrt2[27].Sqrt(),_2sqrt2[28].Sqrt(),
			_2sqrt2[29].Sqrt(),_2sqrt2[30].Sqrt()/*,_2sqrt2[31].Sqrt(),_2sqrt2[32].Sqrt(),_2sqrt2[33].Sqrt(),
			_2sqrt2[34].Sqrt(),_2sqrt2[35].Sqrt(),_2sqrt2[36].Sqrt(),_2sqrt2[37].Sqrt(),_2sqrt2[38].Sqrt(),
			_2sqrt2[39].Sqrt(),_2sqrt2[40].Sqrt(),_2sqrt2[41].Sqrt(),_2sqrt2[42].Sqrt(),_2sqrt2[43].Sqrt(),
			_2sqrt2[44].Sqrt(),_2sqrt2[45].Sqrt(),_2sqrt2[46].Sqrt(),_2sqrt2[47].Sqrt(),_2sqrt2[48].Sqrt(),
			_2sqrt2[49].Sqrt(),_2sqrt2[50].Sqrt(),_2sqrt2[51].Sqrt(),_2sqrt2[52].Sqrt(),_2sqrt2[53].Sqrt(),
			_2sqrt2[54].Sqrt(),_2sqrt2[55].Sqrt(),_2sqrt2[56].Sqrt(),_2sqrt2[57].Sqrt(),_2sqrt2[58].Sqrt(),
			_2sqrt2[59].Sqrt(),_2sqrt2[60].Sqrt(),_2sqrt2[61].Sqrt(),_2sqrt2[62].Sqrt(),_2sqrt2[63].Sqrt(),
			_2sqrt2[64].Sqrt(),_2sqrt2[65].Sqrt(),_2sqrt2[66].Sqrt(),_2sqrt2[67].Sqrt(),_2sqrt2[68].Sqrt(),
			_2sqrt2[69].Sqrt(),_2sqrt2[70].Sqrt(),_2sqrt2[71].Sqrt(),_2sqrt2[72].Sqrt(),_2sqrt2[73].Sqrt(),
			_2sqrt2[74].Sqrt(),_2sqrt2[75].Sqrt(),_2sqrt2[76].Sqrt(),_2sqrt2[77].Sqrt(),_2sqrt2[78].Sqrt(),
			_2sqrt2[79].Sqrt(),_2sqrt2[80].Sqrt(),_2sqrt2[81].Sqrt(),_2sqrt2[82].Sqrt(),_2sqrt2[83].Sqrt(),
			_2sqrt2[84].Sqrt(),_2sqrt2[85].Sqrt(),_2sqrt2[86].Sqrt(),_2sqrt2[87].Sqrt(),_2sqrt2[88].Sqrt(),
			_2sqrt2[89].Sqrt(),_2sqrt2[90].Sqrt(),_2sqrt2[91].Sqrt(),_2sqrt2[92].Sqrt(),_2sqrt2[93].Sqrt(),
			_2sqrt2[94].Sqrt(),_2sqrt2[95].Sqrt(),_2sqrt2[96].Sqrt(),_2sqrt2[97].Sqrt(),_2sqrt2[98].Sqrt(),
			_2sqrt2[99].Sqrt(),_2sqrt2[100].Sqrt(),_2sqrt2[101].Sqrt(),_2sqrt2[102].Sqrt(),_2sqrt2[103].Sqrt(),
			_2sqrt2[104].Sqrt(),_2sqrt2[105].Sqrt(),_2sqrt2[106].Sqrt(),_2sqrt2[107].Sqrt(),_2sqrt2[108].Sqrt(),
			_2sqrt2[109].Sqrt(),_2sqrt2[110].Sqrt(),_2sqrt2[111].Sqrt(),_2sqrt2[112].Sqrt(),_2sqrt2[113].Sqrt(),
			_2sqrt2[114].Sqrt(),_2sqrt2[115].Sqrt(),_2sqrt2[116].Sqrt(),_2sqrt2[117].Sqrt(),_2sqrt2[118].Sqrt(),
			_2sqrt2[119].Sqrt(),_2sqrt2[120].Sqrt(),_2sqrt2[121].Sqrt(),_2sqrt2[122].Sqrt(),_2sqrt2[123].Sqrt(),
			_2sqrt2[124].Sqrt(),_2sqrt2[125].Sqrt(),_2sqrt2[126].Sqrt()*/
		};
		//ln(2^(1/(2^x)))=(ln2)/2^x
		const Float256 Float256::_ln2sqrt2[32] = {Float256(L"ln2"),_ln2sqrt2[0].Half(),_ln2sqrt2[1].Half(),_ln2sqrt2[2].Half(),_ln2sqrt2[3].Half(),
			_ln2sqrt2[4].Half(),_ln2sqrt2[5].Half(),_ln2sqrt2[6].Half(),_ln2sqrt2[7].Half(),_ln2sqrt2[8].Half(),
			_ln2sqrt2[9].Half(),_ln2sqrt2[10].Half(),_ln2sqrt2[11].Half(),_ln2sqrt2[12].Half(),_ln2sqrt2[13].Half(),
			_ln2sqrt2[14].Half(),_ln2sqrt2[15].Half(),_ln2sqrt2[16].Half(),_ln2sqrt2[17].Half(),_ln2sqrt2[18].Half(),
			_ln2sqrt2[19].Half(),_ln2sqrt2[20].Half(),_ln2sqrt2[21].Half(),_ln2sqrt2[22].Half(),_ln2sqrt2[23].Half(),
			_ln2sqrt2[24].Half(),_ln2sqrt2[25].Half(),_ln2sqrt2[26].Half(),_ln2sqrt2[27].Half(),_ln2sqrt2[28].Half(),
			_ln2sqrt2[29].Half(),_ln2sqrt2[30].Half()/*,_ln2sqrt2[31].Half(),_ln2sqrt2[32].Half(),_ln2sqrt2[33].Half(),
			_ln2sqrt2[34].Half(),_ln2sqrt2[35].Half(),_ln2sqrt2[36].Half(),_ln2sqrt2[37].Half(),_ln2sqrt2[38].Half(),
			_ln2sqrt2[39].Half(),_ln2sqrt2[40].Half(),_ln2sqrt2[41].Half(),_ln2sqrt2[42].Half(),_ln2sqrt2[43].Half(),
			_ln2sqrt2[44].Half(),_ln2sqrt2[45].Half(),_ln2sqrt2[46].Half(),_ln2sqrt2[47].Half(),_ln2sqrt2[48].Half(),
			_ln2sqrt2[49].Half(),_ln2sqrt2[50].Half(),_ln2sqrt2[51].Half(),_ln2sqrt2[52].Half(),_ln2sqrt2[53].Half(),
			_ln2sqrt2[54].Half(),_ln2sqrt2[55].Half(),_ln2sqrt2[56].Half(),_ln2sqrt2[57].Half(),_ln2sqrt2[58].Half(),
			_ln2sqrt2[59].Half(),_ln2sqrt2[60].Half(),_ln2sqrt2[61].Half(),_ln2sqrt2[62].Half(),_ln2sqrt2[63].Half(),
			_ln2sqrt2[64].Half(),_ln2sqrt2[65].Half(),_ln2sqrt2[66].Half(),_ln2sqrt2[67].Half(),_ln2sqrt2[68].Half(),
			_ln2sqrt2[69].Half(),_ln2sqrt2[70].Half(),_ln2sqrt2[71].Half(),_ln2sqrt2[72].Half(),_ln2sqrt2[73].Half(),
			_ln2sqrt2[74].Half(),_ln2sqrt2[75].Half(),_ln2sqrt2[76].Half(),_ln2sqrt2[77].Half(),_ln2sqrt2[78].Half(),
			_ln2sqrt2[79].Half(),_ln2sqrt2[80].Half(),_ln2sqrt2[81].Half(),_ln2sqrt2[82].Half(),_ln2sqrt2[83].Half(),
			_ln2sqrt2[84].Half(),_ln2sqrt2[85].Half(),_ln2sqrt2[86].Half(),_ln2sqrt2[87].Half(),_ln2sqrt2[88].Half(),
			_ln2sqrt2[89].Half(),_ln2sqrt2[90].Half(),_ln2sqrt2[91].Half(),_ln2sqrt2[92].Half(),_ln2sqrt2[93].Half(),
			_ln2sqrt2[94].Half(),_ln2sqrt2[95].Half(),_ln2sqrt2[96].Half(),_ln2sqrt2[97].Half(),_ln2sqrt2[98].Half(),
			_ln2sqrt2[99].Half(),_ln2sqrt2[100].Half(),_ln2sqrt2[101].Half(),_ln2sqrt2[102].Half(),_ln2sqrt2[103].Half(),
			_ln2sqrt2[104].Half(),_ln2sqrt2[105].Half(),_ln2sqrt2[106].Half(),_ln2sqrt2[107].Half(),_ln2sqrt2[108].Half(),
			_ln2sqrt2[109].Half(),_ln2sqrt2[110].Half(),_ln2sqrt2[111].Half(),_ln2sqrt2[112].Half(),_ln2sqrt2[113].Half(),
			_ln2sqrt2[114].Half(),_ln2sqrt2[115].Half(),_ln2sqrt2[116].Half(),_ln2sqrt2[117].Half(),_ln2sqrt2[118].Half(),
			_ln2sqrt2[119].Half(),_ln2sqrt2[120].Half(),_ln2sqrt2[121].Half(),_ln2sqrt2[122].Half(),_ln2sqrt2[113].Half(),
			_ln2sqrt2[124].Half(),_ln2sqrt2[125].Half(),_ln2sqrt2[126].Half()*/
		};
		const Float256 Float256::MaxValue = Float256(L"Max");
		const Float256 Float256::MinValue = Float256(L"Min");
		const Float256 Float256::E = Float256(L"e");
		const Float256 Float256::Pi = Float256(L"pi");
		const Float256 Float256::_pi_half = Float256(L"pi").Half();
		const Float256 Float256::_pi_half2 = Float256(L"pi").Half().Half();
		const Float256 Float256::Sqrt2 = Float256(2.0).Sqrt();
		const Float256 Float256::_sqrt2_half = Float256(2.0).Sqrt().Half();
		const Float256 Float256::_pi_180 = Float256(L"pi")/Float256(180.0);
	}
}
#endif