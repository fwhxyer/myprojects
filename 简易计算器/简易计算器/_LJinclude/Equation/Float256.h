#ifndef FLOAT256_
#define FLOAT256_
namespace LJ
{
	namespace Equation
	{
		class FloatData256//β����
		{
		public:
			union
			{
				unsigned long long ull[4];
				unsigned int ui[8];
				unsigned short us[16];
				unsigned char uc[32];
			};
			//�������Ʋ���(����λ�ƶ�movλ)
			void operator<<=(long long mov);
			//�������Ʋ���(����λ�ƶ�movλ)
			void operator>>=(long long mov);
			//�������һ��β�������ؽ�λ
			bool operator+=(FloatData256 &data);
			//�����ȥһ��β�������ؽ�λ
			bool operator-=(FloatData256 &data);
			//�������㣬���ؽ�λ
			bool operator++();
			//�Լ����㣬���ؽ�λ
			bool operator--();
			//����ǰ��0������
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
			//Ĭ�Ϲ��캯��
			Float256(){}
			//��������
			~Float256(){}
			//������������
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
			//���������ݵ��Զ�ת��
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
			//�ж��Ƿ����
			inline bool IsError()const{return Sign<-1;}
			//����Ϊ����״̬
			inline Float256& MakeError(char errorcode){Sign = errorcode;return *this;}
			//�ж��Ƿ����0
			inline bool Equals0()const{return !Sign;}
			//��������
			Float256 operator-()const;
			//����ȡ�෴ֵ
			Float256& SelfNegative();
			//��������
			Float256 operator+()const{return *this;}
			//ǰ����������
			Float256 &operator++();
			//ǰ����������
			Float256 &operator--();
			//������������
			Float256 operator++(int);
			//������������
			Float256 operator--(int);
			//�ӷ�����
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
			//��������
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
			//�˷�����

			//��׼�˷�
			Float256 Multiply(Float256 number)const;
			//���ٳ�10
			Float256 Multiply10()const;
			//��������Գ�10
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
			//��������
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

			//�߼������
			bool operator !()const;
			//�Ƚ������
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
			//��ƽ��
			Float256 Sqrt()const;
			//ȡ����ֵ
			Float256 Abs()const;
			//����ȡ����ֵ
			Float256& SelfAbs();
			//����(>=0),�̱��浽quotient�������numberͬ�ţ�number<0ʱ����ȡ����number>0ʱ����ȡ��
			Float256 Mod(Float256 number,Float256 &quotient)const;
			//����
			Float256 Mod(Float256 number)const;
			//���ظ�����numberΪ�׵Ķ���
			Float256 Log(Float256 number)const;
			//���ظ�����10Ϊ�׵Ķ���
			Float256 Lg()const;
			//���ظ�����eΪ�׵Ķ���
			Float256 Ln()const;
			//���ظ�����2Ϊ�׵Ķ���
			Float256 Log2()const;
			//����e�ĸ�������
			Float256 Expe()const;
			//����2�ĸ�������
			Float256 Exp2()const;
			//���ظ�����number����
			Float256 Pow(Float256 number)const;
			//ȡ����(������)
			Float256 Sin()const;
			//ȡ����(�Ƕ���)
			Float256 Dsin()const;
			//ȡ����(������)
			Float256 Cos()const;
			//ȡ����(�Ƕ���)
			Float256 Dcos()const;
			//ȡ����(������)
			Float256 Tan()const;
			//ȡ����(�Ƕ���)
			Float256 Dtan()const;
			//ȡ����(������)
			Float256 Cot()const;
			//ȡ����(�Ƕ���)
			Float256 Dcot()const;
			//������(������)
			Float256 Arcsin()const;
			//������(�Ƕ���)
			Float256 Darcsin()const;
			//������(������)
			Float256 Arccos()const;
			//������(�Ƕ���)
			Float256 Darccos()const;
			//������(������)
			Float256 Arctan()const;
			//������(�Ƕ���)
			Float256 Darctan()const;
			//�Ƚ��Ƿ����
			bool Equals(const Float256& number)const;
			//Լ����,���Ų�ͬ����false.����λ��ĩcountλ���Ƚ��Ƿ����
			bool AppEquals(const Float256& number)const;
			//����һ��[0,1)�������
			Float256& Rand();
			//������������
			Float256 GetIntegerPart()const;
			//����ȡ��(С������ȫ��)
			Float256& SelfGetIntegerPart();
			//����С������
			Float256 GetDecimalPart()const;
			//����ȡС������
			Float256& SelfGetDecimalPart();
			//ת��Ϊ�ַ�������
			XString ToString(int length=0)const;
			//����0
			const static Float256 Zero;
			//����1
			const static Float256 One;
			//����2
			const static Float256 Two;
			//����3
			const static Float256 Three;
			//����4
			const static Float256 Four;
			//����5
			const static Float256 Five;
			//����6
			const static Float256 Six;
			//����7
			const static Float256 Seven;
			//����8
			const static Float256 Eight;
			//����9
			const static Float256 Nine;
			//����10
			const static Float256 Ten;
			//10^(2^(x))������xΪ0~52
			const static Float256 _10e2[53];
			//��2ȡ��Ȼ��eΪ�׵Ķ���
			const static Float256 Ln2;
			//��10ȡ��Ȼ��eΪ�׵Ķ���
			const static Float256 Ln10;
			//2������x�� : 2^(1/(2^x))
			const static Float256 _2sqrt2[32];
			//ln(2^(1/(2^x)))=(ln2)/2^x
			const static Float256 _ln2sqrt2[32];
			//���ֵ
			const static Float256 MaxValue;
			//��Сֵ
			const static Float256 MinValue;
			//��Ȼ��e
			const static Float256 E;
			//Բ���ʦ�
			const static Float256 Pi;
			//����֮��
			const static Float256 _pi_half;
			//�ķ�֮��
			const static Float256 _pi_half2;
			//����2
			const static Float256 Sqrt2;
			//����֮����2
			const static Float256 _sqrt2_half;
			//һ�ٰ�ʮ��֮��
			const static Float256 _pi_180;
		};
	}
}
#endif