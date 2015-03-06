#pragma once
#define XWAVE_

namespace LJ
{
	namespace Sound
	{
		//���������࣬����������Ƶ��ʽ������
		struct VWaveData:public XBase
		{
		private:PROPERTY_OFFSET(VWaveData,Format);
		public:
			//��ʽ��Ϣ
			double Hz;
			short Bits;
			short Channels;
			bool IsFloat;
			//��Ƶ����
			VArray<unsigned char> Data;
			//Ĭ�Ϲ����޸�ʽ
			VWaveData();
			//��ȡ��Ƶ��ʽ
			WAVEFORMATEX GetFormat()const;
			//������Ƶ��ʽ
			void SetFormat(WAVEFORMATEX x){Hz=x.nSamplesPerSec;Bits=x.wBitsPerSample;Channels=x.nChannels;IsFloat=(x.wFormatTag==0xfffe);}
			//��д���ԣ���Ƶ��ʽ
			PROPERTY_GETSET(WAVEFORMATEX,VWaveData,GetFormat,SetFormat,Format);
			//����������
			virtual ~VWaveData(){}
			//���ƹ��캯��
			VWaveData(const VWaveData& x):Hz(x.Hz),Bits(x.Bits),Channels(x.Channels),IsFloat(x.IsFloat),Data(x.Data){}
			//ȡ��ַ
			VWaveData* operator&(){return reinterpret_cast<VWaveData*>(XBase:: operator&());}
			//ȡ��ַ
			const VWaveData* operator&()const{return reinterpret_cast<const VWaveData*>(XBase:: operator&());}
			//��������
			virtual void SwapWith(XBase& x){XBase::SwapWith(x);return SwapWith(reinterpret_cast<VWaveData&>(x));}
			//��������
			void SwapWith(VWaveData& x){Swap(Hz,x.Hz);Swap(Bits,x.Bits);Swap(Channels,x.Channels);Swap(IsFloat,x.IsFloat);Data.SwapWith(x.Data);}
			//��ǰ������
			static const XTypes& CurrentType;
			//��ȡ��ǰ������
			virtual const XTypes& GetType()const{return CurrentType;}
			//��ֵ
			VWaveData& operator=(const VWaveData& x){Format = x.Format;Data=x.Data;return *this;}
		};
		class XWaveData:public XBase
		{
			PROPERTY_OFFSET(XWaveData,Format);
		public:
			XBaseRTypeMethods_H(XWaveData,VWaveData);
			//��ȡ��Ƶ��ʽ
			WAVEFORMATEX GetFormat()const{return Pointer()->Format;}
			//������Ƶ��ʽ
			void SetFormat(WAVEFORMATEX f){Pointer()->Format = f;}
			//��ȡ��Ƶ����
			VArray<unsigned char>& GetData()const{return Pointer()->Data;}
			//������Ƶ����
			void SetData(VArray<unsigned char>& x){Pointer()->Data = x;}
			//��ȡƵ��
			double GetHz()const{return Pointer()->Hz;}
			//����Ƶ��
			void SetHz(double x){Pointer()->Hz = x;}
			//��ȡλ��
			short GetBits()const{return Pointer()->Bits;}
			//����λ��
			void SetBits(short x){Pointer()->Bits = x;}
			//��ȡ������
			short GetChannels()const{return Pointer()->Channels;}
			//����������
			void SetChannels(short x){Pointer()->Channels = x;}
			//��ȡ�Ƿ񸡵�
			bool GetIsFloat()const{return Pointer()->IsFloat;}
			//�����Ƿ񸡵�
			void SetIsFloat(bool x){Pointer()->IsFloat = x;}
			union
			{
				//��д���ԣ���Ƶ��ʽ
				PROPERTY_GETSET(WAVEFORMATEX,XWaveData,GetFormat,SetFormat,Format);
				//��д���ԣ���Ƶ����
				PROPERTY_GETSET(VArray<unsigned char>&,XWaveData,GetData,SetData,Data);
				//��д���ԣ�Ƶ��
				PROPERTY_GETSET(double,XWaveData,GetHz,SetHz,Hz);
				//��д���ԣ�λ��
				PROPERTY_GETSET(short,XWaveData,GetBits,SetBits,Bits);
				//��д���ԣ�������
				PROPERTY_GETSET(short,XWaveData,GetChannels,SetChannels,Channels);
				//��д���ԣ��Ƿ��Ǹ���
				PROPERTY_GETSET(bool,XWaveData,GetIsFloat,SetIsFloat,IsFloat);
			};
		};

		//�����࣬������Ƶ��ʽ��ת����
		class VWave:public XBase
		{
			//������
			short Channels;
			//λ��
			short Bits;
			//Ƶ��
			double Hz;
			//����
			bool isFloat;
			//������1
			VArray<unsigned char> buffer;
			//������2
			VArray<unsigned char> buffer2;
			//�ϴμ�¼������ֵ��ÿ������һ��ֵ��
			double *lastValue;
			//�ϴμ�¼��ʱ��ֵ
			double lastTime;
			//ʱ��ֵ,Wati����ר��
			XTime time;
			//��sourceData�е���Ƶ���ݰ�toHz��Ƶ�ʺ�toBits��λ���Լ�toFloatת��������
			XArray<unsigned char> HzConvert(const void *sourceData,int length,double toHz,short toBits,bool toFloat=false);
			//Ŀ���ڴ治�ܸ�Դ�ڴ��ص�,����ת�������и����λ��ת��
			XArray<unsigned char> ChConvert(const void *sourceData,int length,double Hz,short Bits,bool isFloat,short toChannels);
			VWave(const VWave&){}
			void operator=(const VWave&){}
		public:
			//��ǰ�������
			static const XTypes& CurrentType;
			//��ȡ����������Ϣ
			virtual const XTypes& GetClassType()const{return CurrentType;}
			//ȡ��ַ
			VWave* operator&(){return static_cast<VWave*>(XBase::operator&());}
			const VWave* operator&()const{return static_cast<const VWave*>(XBase::operator&());}
			//����
			virtual void SwapWith(XBase& x){XBase::SwapWith(x);return SwapWith(reinterpret_cast<VWave&>(x));}
			//����
			void SwapWith(VWave& x)
			{
				Swap(Channels,x.Channels);
				Swap(Bits,x.Bits);
				Swap(Hz,x.Hz);
				Swap(isFloat,isFloat);
				buffer.SwapWith(x.buffer);
				buffer2.SwapWith(x.buffer2);
				Swap(lastValue,x.lastValue);
				Swap(lastTime,x.lastTime);
				time.SwapWith(x.time);
			}
			VWave();
			virtual ~VWave();
			//��д���ԣ�����
			double Volume;
			//������ƵԴ��ʽ
			void SetFormat(double hz,short bits,short channels,bool isfloat = false);
			//������ƵԴ��ʽ
			void SetFormat(const WAVEFORMATEX& wfx);
			//����Ĭ����ƵԴ��ʽ
			void SetFormat();
			//ת����Ƶ��ʽ
			template<typename T>XArray<T> Convert(const XArray<T>&sourceData,double toHz,short toBits, short toChannels,bool toFloat=false);
			//ת����Ƶ��ʽ
			template<typename T>XArray<T> Convert(const XArray<T>&sourceData,const WAVEFORMATEX& deswfx);
			//ȡ��Ƶֵ
			static double GetValue(const void *buffer,short bits,unsigned int sampleIndex,bool isfloat=false);
			//д����Ƶֵ
			static void SetValue(void *buffer,double value,short bits,unsigned int sampleIndex,bool isfloat=false);
			//ȡ��Ƶֵ
			static double GetValue(const void *p,short bits,bool isfloat=false);
			//д����Ƶֵ
			static void SetValue(void *p,double value,short bits,bool isfloat=false);
			//����WAVEFORMATEX��Ƶ��ʽ
			static WAVEFORMATEX MakeFormat(int hz,short bits,short ch,bool isfloat=false);
			//��pData2����Ƶ���ӵ�pData1���У�bitsΪλ����countΪ������֡��
			template<typename T,typename AnyT>static void Mix(XArray<T>& pDest,const XArray<AnyT>& pData,double vol,short bits,bool isfloat=false);
			//��ȡsize�ֽڵ�������block��ֵΪ0~1��С����ָ�����񻯲���
			XArray<unsigned char> GetNoise(unsigned int size,double block=0);
			//��ȡһ��ָ��Ƶ�ʵĲ���
			XArray<unsigned char> GetWaveWithSingleHz(double hz,unsigned int size,double block=0);
			//��ȡָ��ʱ�䳤�ȵ�������block��ֵΪ0~1��С����ָ�����񻯲���
			XWaveData GetNoiseData(const XTime&time,double block=0);
			//��ȡָ��ʱ�䳤�ȵġ�ָ��Ƶ�ʵĲ���
			XWaveData GetWaveDataWithSingleHz(double hz,const XTime&time,double block=0);
			//�ȴ���ָ���ֽ�����ʾ��ʱ��
			void Wait(unsigned int size);
		};
		class XWave:public XBase
		{
			PROPERTY_OFFSET(XWave,Volume);
		public:
			XBaseRTypeMethods_H(XWave,VWave);
			//��ȡ����
			double GetVolume()const{return Pointer()->Volume;}
			//��������
			void SetVolume(double vol){Pointer()->Volume=vol;}
			//��д���ԣ�����
			PROPERTY_GETSET(double,XWave,GetVolume,SetVolume,Volume);
			//������ƵԴ��ʽ
			void SetFormat(double hz,short bits,short channels,bool isfloat = false){return Pointer()->SetFormat(hz,bits,channels,isfloat);}
			//������ƵԴ��ʽ
			void SetFormat(const WAVEFORMATEX& wfx){return Pointer()->SetFormat(wfx);}
			//����Ĭ����ƵԴ��ʽ
			void SetFormat(){return Pointer()->SetFormat();}
			//ת����Ƶ��ʽ
			template<typename T>XArray<T> Convert(const XArray<T>&sourceData,double toHz,short toBits, short toChannels,bool toFloat=false){return Pointer()->Convert(sourceData,toHz,toBits,toChannels,toFloat);}
			//ת����Ƶ��ʽ
			template<typename T>XArray<T> Convert(const XArray<T>&sourceData,const WAVEFORMATEX& w){return Pointer()->Convert(sourceData,w);}
			//ȡ��Ƶֵ
			static inline double GetValue(const void *buffer,short bits,unsigned int sampleIndex,bool isfloat=false){return VWave::GetValue(buffer,bits,sampleIndex,isfloat);}
			//д����Ƶֵ
			static inline void SetValue(void *buffer,double value,short bits,unsigned int sampleIndex,bool isfloat=false){return VWave::SetValue(buffer,value,bits,sampleIndex,isfloat);}
			//ȡ��Ƶֵ
			static inline double GetValue(const void *p,short bits,bool isfloat=false){return VWave::GetValue(p,bits,isfloat);}
			//д����Ƶֵ
			static inline void SetValue(void *p,double value,short bits,bool isfloat=false){return VWave::SetValue(p,value,bits,isfloat);}
			//����WAVEFORMATEX��Ƶ��ʽ
			static inline WAVEFORMATEX MakeFormat(int hz,short bits,short ch,bool isfloat=false){return VWave::MakeFormat(hz,bits,ch,isfloat);}
			//��pData����Ƶ���ӵ�pDest���У�bitsΪλ����countΪ������֡��
			template<typename T,typename AnyT>static inline void Mix(XArray<T>& pDest,const XArray<AnyT>& pData,double vol,short bits,bool isfloat=false){return VWave::Mix(pDest,pData,vol,bits,isfloat);}
			//��ȡsize�ֽڵ�������block��ֵΪ0~1��С����ָ�����񻯲���
			XArray<unsigned char> GetNoise(unsigned int size,double block=0){return Pointer()->GetNoise(size,block);}
			//��ȡһ��ָ��Ƶ�ʵĲ���
			XArray<unsigned char> GetWaveWithSingleHz(double hz,unsigned int size,double block=0){return Pointer()->GetWaveWithSingleHz(hz,size,block);}
			//��ȡָ��ʱ�䳤�ȵ�������block��ֵΪ0~1��С����ָ�����񻯲���
			XWaveData GetNoiseData(const XTime&time,double block=0){return Pointer()->GetNoiseData(time,block);}
			//��ȡָ��ʱ�䳤�ȵġ�ָ��Ƶ�ʵĲ���
			XWaveData GetWaveDataWithSingleHz(double hz,const XTime&time,double block=0){return Pointer()->GetWaveDataWithSingleHz(hz,time,block);}
			//�ȴ���ָ���ֽ�����ʾ��ʱ��
			void Wait(unsigned int size){return Pointer()->Wait(size);}
		};


		template<typename T>XArray<T> VWave::Convert(const XArray<T>&sourceData,double toHz,short toBits, short toChannels,bool toFloat)
		{
			//���ת��������ڴ�͵�����֡����
			XArray<unsigned char> pdata =HzConvert(sourceData,sourceData.LengthOfBytes,toHz,toBits,toFloat);
			//ת��������
			XArray<unsigned char> pdata2 = ChConvert(pdata,pdata.Length,toHz,toBits,toFloat,toChannels);
			//����һ������
			return XArray<T>((pdata2.Length/sizeof(T)),(T*)(void*)pdata2,Reference);
		}
		template<typename T>XArray<T> VWave::Convert(const XArray<T>&sourceData,const WAVEFORMATEX& deswfx)
		{
			return Convert(sourceData,deswfx.nSamplesPerSec,deswfx.wBitsPerSample,deswfx.nChannels,deswfx.wFormatTag==0xfffe);
		}
		template<typename T,typename AnyT>void VWave::Mix(XArray<T>& pData1,const XArray<AnyT>& pData2,double vol,short bits,bool isfloat)
		{
			int tmp = pData1.LengthOfBytes>pData2.LengthOfBytes?pData2.LengthOfBytes:pData1.LengthOfBytes;
			tmp /= bits/8;//��֡��
			if(isfloat)//32λ���и���
			{
				float* pdes = (float*)(T*)pData1;
				float* pend = pdes+tmp;
				float* pstart = (float*)const_cast<AnyT*>((const AnyT*)pData2);
				while(pdes<pend)
				{
					*pdes += float(*pstart * vol);
					++pdes;
					++pstart;
				}
				return;
			}
			if(bits==32)
			{
				int* pdes = (int*)(T*)pData1;
				int* pend = pdes+tmp;
				int* pstart = (int*)const_cast<AnyT*>((const AnyT*)pData2);
				while(pdes<pend)
				{
					*pdes += int(*pstart * vol);
					++pdes;
					++pstart;
				}
				return;
			}
			if(bits==16)
			{
				short* pdes = (short*)(T*)pData1;
				short* pend = pdes+tmp;
				short* pstart = (short*)const_cast<AnyT*>((const AnyT*)pData2);
				while(pdes<pend)
				{
					*pdes += short(*pstart * vol);
					++pdes;
					++pstart;
				}
				return;
			}
			unsigned char* pdes = (unsigned char*)(T*)pData1;
			unsigned char* pend = pdes+tmp;
			unsigned char* pstart = (unsigned char*)const_cast<AnyT*>((const AnyT*)pData2);
			while(pdes<pend)
			{
				*pdes = *pdes-128 + unsigned char((int(*pstart)-128) * vol+128);
				++pdes;
				++pstart;
			}
			return;
		}
	}
}