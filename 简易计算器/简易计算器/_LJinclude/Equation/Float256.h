#ifndef FLOAT256_
#define FLOAT256_
namespace LJ
{
	namespace Equation
	{
		class FloatData256//尾数类
		{
		public:
			union
			{
				unsigned long long ull[4];
				unsigned int ui[8];
				unsigned short us[16];
				unsigned char uc[32];
			};
			//自身左移操作(往高位移动mov位)
			void operator<<=(long long mov);
			//自身右移操作(往低位移动mov位)
			void operator>>=(long long mov);
			//自身加上一个尾数，返回进位
			bool operator+=(FloatData256 &data);
			//自身减去一个尾数，返回借位
			bool operator-=(FloatData256 &data);
			//自增运算，返回进位
			bool operator++();
			//自减运算，返回借位
			bool operator--();
			//返回前导0的数量
			long long BitsZeroCount();
			operator bool()const{return ull[3]!=0 || ull[2]!=0 || ull[1]!=0 || ull[0]!=0;}
			bool operator !()const{return ull[3]==0&&ull[2]==0&&ull[1]==0&&ull[0]==0;}
			bool operator>(const FloatData256 &data)const;
			bool operator<(const FloatData256 &data)const;
			bool operator==(const FloatData256 &data)const;
			bool operator!=(const FloatData256 &data)const;
			bool operator>=(const FloatData256 &data)const;
			bool operator<=(const FloatData256 &data)const;
			inline bool GetBit(long long position)const{return Bits::Get(this,position);}
			void Clear(){ull[3] = ull[2] = ull[1] = ull[0] = 0;}
		};
		class Float256
		{
			static void BitsMoveLeft(unsigned long long * pull);
			static void BitsMoveRight(unsigned long long * pull);
			static unsigned long BitsMultiply(FloatData256 &dat,FloatData256 &desdat, unsigned long long& num);
		public:
			const static long long ExpMaxValue;
			const static long long ExpMinValue;
			union
			{
				long long Exp:56;
				struct
				{
					char _exp[7];
					signed char Sign;
				};
			};
			FloatData256 Data;
			//默认构造函数
			Float256(){}
			//析构函数
			~Float256(){}
			//从其他数构造
			Float256(double number);
			Float256(float number);
			Float256(long long number);
			Float256(unsigned long long number);
			Float256(long number);
			Float256(unsigned long number);
			Float256(int number);
			Float256(unsigned int number);
			Float256(short number);
			Float256(unsigned short number);
			Float256(signed char number);
			Float256(unsigned char number);
			Float256(char number);
			Float256(bool number);
			Float256(LPCWSTR number);
			inline Float256(const XString& number){*this=Float256((LPCWSTR)number); }
			inline Float256(LPCSTR number){*this=Float256(XString(number)); }
			//到其他数据的自动转换
			operator double()const;
			operator float()const;
			operator long long()const;
			operator unsigned long long()const;
			operator long()const;
			operator unsigned long()const;
			operator int()const;
			operator unsigned int()const;
			operator short()const;
			operator unsigned short()const;
			operator signed char()const;
			operator unsigned char()const;
			operator char()const;
			operator bool()const;
			//判断是否出错
			inline bool IsError()const{return Sign<-1;}
			//设置为错误状态
			inline Float256& MakeError(char errorcode){Sign = errorcode;return *this;}
			//判断是否等于0
			inline bool Equals0()const{return !Sign;}
			//负号重载
			Float256 operator-()const;
			//自身取相反值
			Float256& SelfNegative();
			//正号重载
			Float256 operator+()const{return *this;}
			//前置运算重载
			Float256 &operator++();
			//前置运算重载
			Float256 &operator--();
			//后置运算重载
			Float256 operator++(int);
			//后置运算重载
			Float256 operator--(int);
			//加法重载
			Float256& operator+=(Float256 number);
			Float256& operator+=(double number);
			Float256& operator+=(float number);
			Float256& operator+=(long long number);
			Float256& operator+=(unsigned long long number);
			Float256& operator+=(long number);
			Float256& operator+=(unsigned long number);
			Float256& operator+=(int number);
			Float256& operator+=(unsigned int number);
			Float256& operator+=(short number);
			Float256& operator+=(unsigned short number);
			Float256& operator+=(signed char number);
			Float256& operator+=(unsigned char number);
			Float256& operator+=(char number);
			Float256& operator+=(bool number);
			Float256& operator+=(const XString& number){return operator+=(Float256(number));}
			Float256& operator+=(LPCWSTR number){return operator+=(Float256(number));}
			Float256& operator+=(LPCSTR number){return operator+=(Float256(number));}
			Float256 operator+(Float256 number)const;
			Float256 operator+(double number)const;
			Float256 operator+(float number)const;
			Float256 operator+(long long number)const;
			Float256 operator+(unsigned long long number)const;
			Float256 operator+(long number)const;
			Float256 operator+(unsigned long number)const;
			Float256 operator+(int number)const;
			Float256 operator+(unsigned int number)const;
			Float256 operator+(short number)const;
			Float256 operator+(unsigned short number)const;
			Float256 operator+(signed char number)const;
			Float256 operator+(unsigned char number)const;
			Float256 operator+(char number)const;
			Float256 operator+(bool number)const;
			inline Float256 operator+(const XString& number)const{return operator+(Float256(number));}
			inline Float256 operator+(LPCWSTR number)const{return operator+(Float256(number));}
			inline Float256 operator+(LPCSTR number)const{return operator+(Float256(number));}
			friend Float256 operator+(double number,const Float256& f){return f+number;}
			friend Float256 operator+(float number,const Float256& f){return f+number;}
			friend Float256 operator+(long long number,const Float256& f){return f+number;}
			friend Float256 operator+(unsigned long long number,const Float256& f){return f+number;}
			friend Float256 operator+(long number,const Float256& f){return f+number;}
			friend Float256 operator+(unsigned long number,const Float256& f){return f+number;}
			friend Float256 operator+(int number,const Float256& f){return f+number;}
			friend Float256 operator+(unsigned int number,const Float256& f){return f+number;}
			friend Float256 operator+(short number,const Float256& f){return f+number;}
			friend Float256 operator+(unsigned short number,const Float256& f){return f+number;}
			friend Float256 operator+(signed char number,const Float256& f){return f+number;}
			friend Float256 operator+(unsigned char number,const Float256& f){return f+number;}
			friend Float256 operator+(char number,const Float256& f){return f+number;}
			friend Float256 operator+(bool number,const Float256& f){return f+number;}
			friend Float256 operator+(const XString& number,const Float256& f){return f+number;}
			friend Float256 operator+(LPCWSTR number,const Float256& f){return f+number;}
			friend Float256 operator+(LPCSTR number,const Float256& f){return f+number;}
			//减法重载
			Float256& operator-=(Float256 number);
			Float256& operator-=(double number);
			Float256& operator-=(float number);
			Float256& operator-=(long long number);
			Float256& operator-=(unsigned long long number);
			Float256& operator-=(long number);
			Float256& operator-=(unsigned long number);
			Float256& operator-=(int number);
			Float256& operator-=(unsigned int number);
			Float256& operator-=(short number);
			Float256& operator-=(unsigned short number);
			Float256& operator-=(signed char number);
			Float256& operator-=(unsigned char number);
			Float256& operator-=(char number);
			Float256& operator-=(bool number);
			inline Float256& operator-=(const XString& number){return operator-=(Float256(number));}
			inline Float256& operator-=(LPCWSTR number){return operator-=(Float256(number));}
			inline Float256& operator-=(LPCSTR number){return operator-=(Float256(number));}
			Float256 operator-(Float256 number)const;
			Float256 operator-(double number)const;
			Float256 operator-(float number)const;
			Float256 operator-(long long number)const;
			Float256 operator-(unsigned long long number)const;
			Float256 operator-(long number)const;
			Float256 operator-(unsigned long number)const;
			Float256 operator-(int number)const;
			Float256 operator-(unsigned int number)const;
			Float256 operator-(short number)const;
			Float256 operator-(unsigned short number)const;
			Float256 operator-(signed char number)const;
			Float256 operator-(unsigned char number)const;
			Float256 operator-(char number)const;
			Float256 operator-(bool number)const;
			inline Float256 operator-(const XString& number)const{return operator-(Float256(number));}
			inline Float256 operator-(LPCWSTR number)const{return operator-(Float256(number));}
			inline Float256 operator-(LPCSTR number)const{return operator-(Float256(number));}
			friend Float256 operator-(double number,const Float256& f){return -f+number;}
			friend Float256 operator-(float number,const Float256& f){return -f+number;}
			friend Float256 operator-(long long number,const Float256& f){return -f+number;}
			friend Float256 operator-(unsigned long long number,const Float256& f){return -f+number;}
			friend Float256 operator-(long number,const Float256& f){return -f+number;}
			friend Float256 operator-(unsigned long number,const Float256& f){return -f+number;}
			friend Float256 operator-(int number,const Float256& f){return -f+number;}
			friend Float256 operator-(unsigned int number,const Float256& f){return -f+number;}
			friend Float256 operator-(short number,const Float256& f){return -f+number;}
			friend Float256 operator-(unsigned short number,const Float256& f){return -f+number;}
			friend Float256 operator-(signed char number,const Float256& f){return -f+number;}
			friend Float256 operator-(unsigned char number,const Float256& f){return -f+number;}
			friend Float256 operator-(char number,const Float256& f){return -f+number;}
			friend Float256 operator-(bool number,const Float256& f){return -f+number;}
			friend Float256 operator-(const XString& number,const Float256& f){return -f+number;}
			friend Float256 operator-(LPCWSTR number,const Float256& f){return -f+number;}
			friend Float256 operator-(LPCSTR number,const Float256& f){return -f+number;}
			//乘法重载

			//标准乘法
			Float256 Multiply(Float256 number)const;
			//快速乘10
			Float256 Multiply10()const;
			//自身快速自乘10
			Float256& SelfMultiply10();
			Float256& operator*=(Float256 number);
			Float256& operator*=(double number);
			Float256& operator*=(float number);
			Float256& operator*=(long long number);
			Float256& operator*=(unsigned long long number);
			Float256& operator*=(long number);
			Float256& operator*=(unsigned long number);
			Float256& operator*=(int number);
			Float256& operator*=(unsigned int number);
			Float256& operator*=(short number);
			Float256& operator*=(unsigned short number);
			Float256& operator*=(signed char number);
			Float256& operator*=(unsigned char number);
			Float256& operator*=(char number);
			Float256& operator*=(bool number);
			inline Float256& operator*=(const XString& number){return operator*=(Float256(number));}
			inline Float256& operator*=(LPCWSTR number){return operator*=(Float256(number));}
			inline Float256& operator*=(LPCSTR number){return operator*=(Float256(number));}
			Float256 operator*(Float256 number)const;
			Float256 operator*(double number)const;
			Float256 operator*(float number)const;
			Float256 operator*(long long number)const;
			Float256 operator*(unsigned long long number)const;
			Float256 operator*(long number)const;
			Float256 operator*(unsigned long number)const;
			Float256 operator*(int number)const;
			Float256 operator*(unsigned int number)const;
			Float256 operator*(short number)const;
			Float256 operator*(unsigned short number)const;
			Float256 operator*(signed char number)const;
			Float256 operator*(unsigned char number)const;
			Float256 operator*(char number)const;
			Float256 operator*(bool number)const;
			inline Float256 operator*(const XString& number)const{return operator*(Float256(number));}
			inline Float256 operator*(LPCWSTR number)const{return operator*(Float256(number));}
			inline Float256 operator*(LPCSTR number)const{return operator*(Float256(number));}
			friend Float256 operator*(double number,const Float256& f){return f*number;}
			friend Float256 operator*(float number,const Float256& f){return f*number;}
			friend Float256 operator*(long long number,const Float256& f){return f*number;}
			friend Float256 operator*(unsigned long long number,const Float256& f){return f*number;}
			friend Float256 operator*(long number,const Float256& f){return f*number;}
			friend Float256 operator*(unsigned long number,const Float256& f){return f*number;}
			friend Float256 operator*(int number,const Float256& f){return f*number;}
			friend Float256 operator*(unsigned int number,const Float256& f){return f*number;}
			friend Float256 operator*(short number,const Float256& f){return f*number;}
			friend Float256 operator*(unsigned short number,const Float256& f){return f*number;}
			friend Float256 operator*(signed char number,const Float256& f){return f*number;}
			friend Float256 operator*(unsigned char number,const Float256& f){return f*number;}
			friend Float256 operator*(char number,const Float256& f){return f*number;}
			friend Float256 operator*(bool number,const Float256& f){return f*number;}
			friend Float256 operator*(const XString& number,const Float256& f){return f*number;}
			friend Float256 operator*(LPCWSTR number,const Float256& f){return f*number;}
			friend Float256 operator*(LPCSTR number,const Float256& f){return f*number;}
			//除法重载
			Float256 Divide(Float256 number)const;
			Float256 Half()const;
			Float256& SelfHalf();
			Float256& operator/=(Float256 number);
			Float256& operator/=(double number);
			Float256& operator/=(float number);
			Float256& operator/=(long long number);
			Float256& operator/=(unsigned long long number);
			Float256& operator/=(long number);
			Float256& operator/=(unsigned long number);
			Float256& operator/=(int number);
			Float256& operator/=(unsigned int number);
			Float256& operator/=(short number);
			Float256& operator/=(unsigned short number);
			Float256& operator/=(signed char number);
			Float256& operator/=(unsigned char number);
			Float256& operator/=(char number);
			Float256& operator/=(bool number);
			inline Float256& operator/=(const XString& number){return operator/=(Float256(number));}
			inline Float256& operator/=(LPCWSTR number){return operator/=(Float256(number));}
			inline Float256& operator/=(LPCSTR number){return operator/=(Float256(number));}
			Float256 operator/(Float256 number)const;
			Float256 operator/(double number)const;
			Float256 operator/(float number)const;
			Float256 operator/(long long number)const;
			Float256 operator/(unsigned long long number)const;
			Float256 operator/(long number)const;
			Float256 operator/(unsigned long number)const;
			Float256 operator/(int number)const;
			Float256 operator/(unsigned int number)const;
			Float256 operator/(short number)const;
			Float256 operator/(unsigned short number)const;
			Float256 operator/(signed char number)const;
			Float256 operator/(unsigned char number)const;
			Float256 operator/(char number)const;
			Float256 operator/(bool number)const;
			inline Float256 operator/(const XString& number)const{return operator/(Float256(number));}
			inline Float256 operator/(LPCWSTR number)const{return operator/(Float256(number));}
			inline Float256 operator/(LPCSTR number)const{return operator/(Float256(number));}
			friend Float256 operator/(double number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(float number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(long long number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(unsigned long long number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(long number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(unsigned long number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(int number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(unsigned int number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(short number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(unsigned short number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(signed char number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(unsigned char number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(char number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(bool number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(const XString& number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(LPCWSTR number,const Float256& f){return Float256(number)/f;}
			friend Float256 operator/(LPCSTR number,const Float256& f){return Float256(number)/f;}

			//逻辑运算符
			bool operator !()const;
			//比较运算符
			bool operator>(const Float256& number)const;
			bool operator>(double number)const;
			bool operator>(float number)const;
			bool operator>(unsigned long long number)const;
			bool operator>(long long number)const;
			bool operator>(unsigned long number)const;
			bool operator>(long number)const;
			bool operator>(unsigned int number)const;
			bool operator>(int number)const;
			bool operator>(unsigned short number)const;
			bool operator>(short number)const;
			bool operator>(unsigned char number)const;
			bool operator>(signed char number)const;
			bool operator>(char number)const;
			bool operator>(bool number)const;
			inline bool operator>(const XString& number)const{return operator>(Float256(number));}
			inline bool operator>(LPCWSTR number)const{return operator>(Float256(number));}
			inline bool operator>(LPCSTR number)const{return operator>(Float256(number));}

			bool operator<(const Float256& number)const;
			bool operator<(double number)const;
			bool operator<(float number)const;
			bool operator<(unsigned long long number)const;
			bool operator<(long long number)const;
			bool operator<(unsigned long number)const;
			bool operator<(long number)const;
			bool operator<(unsigned int number)const;
			bool operator<(int number)const;
			bool operator<(unsigned short number)const;
			bool operator<(short number)const;
			bool operator<(unsigned char number)const;
			bool operator<(signed char number)const;
			bool operator<(char number)const;
			bool operator<(bool number)const;
			inline bool operator<(const XString& number)const{return operator<(Float256(number));}
			inline bool operator<(LPCWSTR number)const{return operator<(Float256(number));}
			inline bool operator<(LPCSTR number)const{return operator<(Float256(number));}

			bool operator==(const Float256& number)const;
			bool operator==(double number)const;
			bool operator==(float number)const;
			bool operator==(unsigned long long number)const;
			bool operator==(long long number)const;
			bool operator==(unsigned long number)const;
			bool operator==(long number)const;
			bool operator==(unsigned int number)const;
			bool operator==(int number)const;
			bool operator==(unsigned short number)const;
			bool operator==(short number)const;
			bool operator==(unsigned char number)const;
			bool operator==(signed char number)const;
			bool operator==(char number)const;
			bool operator==(bool number)const;
			inline bool operator==(const XString& number)const{return operator==(Float256(number));}
			inline bool operator==(LPCWSTR number)const{return operator==(Float256(number));}
			inline bool operator==(LPCSTR number)const{return operator==(Float256(number));}

			bool operator>=(const Float256& number)const;
			bool operator>=(double number)const;
			bool operator>=(float number)const;
			bool operator>=(unsigned long long number)const;
			bool operator>=(long long number)const;
			bool operator>=(unsigned long number)const;
			bool operator>=(long number)const;
			bool operator>=(unsigned int number)const;
			bool operator>=(int number)const;
			bool operator>=(unsigned short number)const;
			bool operator>=(short number)const;
			bool operator>=(unsigned char number)const;
			bool operator>=(signed char number)const;
			bool operator>=(char number)const;
			bool operator>=(bool number)const;
			inline bool operator>=(const XString& number)const{return operator>=(Float256(number));}
			inline bool operator>=(LPCWSTR number)const{return operator>=(Float256(number));}
			inline bool operator>=(LPCSTR number)const{return operator>=(Float256(number));}

			bool operator<=(const Float256& number)const;
			bool operator<=(double number)const;
			bool operator<=(float number)const;
			bool operator<=(unsigned long long number)const;
			bool operator<=(long long number)const;
			bool operator<=(unsigned long number)const;
			bool operator<=(long number)const;
			bool operator<=(unsigned int number)const;
			bool operator<=(int number)const;
			bool operator<=(unsigned short number)const;
			bool operator<=(short number)const;
			bool operator<=(unsigned char number)const;
			bool operator<=(signed char number)const;
			bool operator<=(char number)const;
			bool operator<=(bool number)const;
			inline bool operator<=(const XString& number)const{return operator<=(Float256(number));}
			inline bool operator<=(LPCWSTR number)const{return operator<=(Float256(number));}
			inline bool operator<=(LPCSTR number)const{return operator<=(Float256(number));}

			bool operator!=(const Float256& number)const;
			bool operator!=(double number)const;
			bool operator!=(float number)const;
			bool operator!=(unsigned long long number)const;
			bool operator!=(long long number)const;
			bool operator!=(unsigned long number)const;
			bool operator!=(long number)const;
			bool operator!=(unsigned int number)const;
			bool operator!=(int number)const;
			bool operator!=(unsigned short number)const;
			bool operator!=(short number)const;
			bool operator!=(unsigned char number)const;
			bool operator!=(signed char number)const;
			bool operator!=(char number)const;
			bool operator!=(bool number)const;
			inline bool operator!=(const XString& number)const{return operator!=(Float256(number));}
			inline bool operator!=(LPCWSTR number)const{return operator!=(Float256(number));}
			inline bool operator!=(LPCSTR number)const{return operator!=(Float256(number));}
			//开平方
			Float256 Sqrt()const;
			//取绝对值
			Float256 Abs()const;
			//自身取绝对值
			Float256& SelfAbs();
			//求余(>=0),商保存到quotient里，余数与number同号；number<0时向上取整，number>0时向下取整
			Float256 Mod(Float256 number,Float256 &quotient)const;
			//求余
			Float256 Mod(Float256 number)const;
			//返回该数以number为底的对数
			Float256 Log(Float256 number)const;
			//返回该数以10为底的对数
			Float256 Lg()const;
			//返回该数以e为底的对数
			Float256 Ln()const;
			//返回该数以2为底的对数
			Float256 Log2()const;
			//返回e的该数次幂
			Float256 Expe()const;
			//返回2的该数次幂
			Float256 Exp2()const;
			//返回该数的number次幂
			Float256 Pow(Float256 number)const;
			//取正弦(弧度制)
			Float256 Sin()const;
			//取正弦(角度制)
			Float256 Dsin()const;
			//取余弦(弧度制)
			Float256 Cos()const;
			//取余弦(角度制)
			Float256 Dcos()const;
			//取正切(弧度制)
			Float256 Tan()const;
			//取正切(角度制)
			Float256 Dtan()const;
			//取余切(弧度制)
			Float256 Cot()const;
			//取余切(角度制)
			Float256 Dcot()const;
			//反正弦(弧度制)
			Float256 Arcsin()const;
			//反正弦(角度制)
			Float256 Darcsin()const;
			//反余弦(弧度制)
			Float256 Arccos()const;
			//反余弦(角度制)
			Float256 Darccos()const;
			//反正切(弧度制)
			Float256 Arctan()const;
			//反正切(角度制)
			Float256 Darctan()const;
			//比较是否相等
			bool Equals(const Float256& number)const;
			//约等于,符号不同返回false.忽略位数末count位，比较是否等于
			bool AppEquals(const Float256& number)const;
			//声成一个[0,1)的随机数
			Float256& Rand();
			//返回整数部分
			Float256 GetIntegerPart()const;
			//自身取整(小数部分全舍)
			Float256& SelfGetIntegerPart();
			//返回小数部分
			Float256 GetDecimalPart()const;
			//自身取小数部分
			Float256& SelfGetDecimalPart();
			//转换为字符串描述
			XString ToString(int length=0)const;
			//常量0
			const static Float256 Zero;
			//常量1
			const static Float256 One;
			//常量2
			const static Float256 Two;
			//常量3
			const static Float256 Three;
			//常量4
			const static Float256 Four;
			//常量5
			const static Float256 Five;
			//常量6
			const static Float256 Six;
			//常量7
			const static Float256 Seven;
			//常量8
			const static Float256 Eight;
			//常量9
			const static Float256 Nine;
			//常量10
			const static Float256 Ten;
			//10^(2^(x))，其中x为0~52
			const static Float256 _10e2[53];
			//对2取自然数e为底的对数
			const static Float256 Ln2;
			//对10取自然数e为底的对数
			const static Float256 Ln10;
			//2开根号x次 : 2^(1/(2^x))
			const static Float256 _2sqrt2[32];
			//ln(2^(1/(2^x)))=(ln2)/2^x
			const static Float256 _ln2sqrt2[32];
			//最大值
			const static Float256 MaxValue;
			//最小值
			const static Float256 MinValue;
			//自然数e
			const static Float256 E;
			//圆周率π
			const static Float256 Pi;
			//二分之π
			const static Float256 _pi_half;
			//四分之π
			const static Float256 _pi_half2;
			//根号2
			const static Float256 Sqrt2;
			//二分之根号2
			const static Float256 _sqrt2_half;
			//一百八十分之π
			const static Float256 _pi_180;
		};
	}
}
#endif