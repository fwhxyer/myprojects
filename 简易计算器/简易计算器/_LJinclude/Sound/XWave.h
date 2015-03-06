#pragma once
#define XWAVE_

namespace LJ
{
	namespace Sound
	{
		//波形数据类，包含各种音频格式的数据
		struct VWaveData:public XBase
		{
		private:PROPERTY_OFFSET(VWaveData,Format);
		public:
			//格式信息
			double Hz;
			short Bits;
			short Channels;
			bool IsFloat;
			//音频数据
			VArray<unsigned char> Data;
			//默认构造无格式
			VWaveData();
			//获取音频格式
			WAVEFORMATEX GetFormat()const;
			//设置音频格式
			void SetFormat(WAVEFORMATEX x){Hz=x.nSamplesPerSec;Bits=x.wBitsPerSample;Channels=x.nChannels;IsFloat=(x.wFormatTag==0xfffe);}
			//读写属性：音频格式
			PROPERTY_GETSET(WAVEFORMATEX,VWaveData,GetFormat,SetFormat,Format);
			//虚析构函数
			virtual ~VWaveData(){}
			//复制构造函数
			VWaveData(const VWaveData& x):Hz(x.Hz),Bits(x.Bits),Channels(x.Channels),IsFloat(x.IsFloat),Data(x.Data){}
			//取地址
			VWaveData* operator&(){return reinterpret_cast<VWaveData*>(XBase:: operator&());}
			//取地址
			const VWaveData* operator&()const{return reinterpret_cast<const VWaveData*>(XBase:: operator&());}
			//交换内容
			virtual void SwapWith(XBase& x){XBase::SwapWith(x);return SwapWith(reinterpret_cast<VWaveData&>(x));}
			//交换内容
			void SwapWith(VWaveData& x){Swap(Hz,x.Hz);Swap(Bits,x.Bits);Swap(Channels,x.Channels);Swap(IsFloat,x.IsFloat);Data.SwapWith(x.Data);}
			//当前类类型
			static const XTypes& CurrentType;
			//获取当前类类型
			virtual const XTypes& GetType()const{return CurrentType;}
			//赋值
			VWaveData& operator=(const VWaveData& x){Format = x.Format;Data=x.Data;return *this;}
		};
		class XWaveData:public XBase
		{
			PROPERTY_OFFSET(XWaveData,Format);
		public:
			XBaseRTypeMethods_H(XWaveData,VWaveData);
			//获取音频格式
			WAVEFORMATEX GetFormat()const{return Pointer()->Format;}
			//设置音频格式
			void SetFormat(WAVEFORMATEX f){Pointer()->Format = f;}
			//获取音频数据
			VArray<unsigned char>& GetData()const{return Pointer()->Data;}
			//设置音频数据
			void SetData(VArray<unsigned char>& x){Pointer()->Data = x;}
			//获取频率
			double GetHz()const{return Pointer()->Hz;}
			//设置频率
			void SetHz(double x){Pointer()->Hz = x;}
			//获取位数
			short GetBits()const{return Pointer()->Bits;}
			//设置位数
			void SetBits(short x){Pointer()->Bits = x;}
			//获取声道数
			short GetChannels()const{return Pointer()->Channels;}
			//设置声道数
			void SetChannels(short x){Pointer()->Channels = x;}
			//获取是否浮点
			bool GetIsFloat()const{return Pointer()->IsFloat;}
			//设置是否浮点
			void SetIsFloat(bool x){Pointer()->IsFloat = x;}
			union
			{
				//读写属性：音频格式
				PROPERTY_GETSET(WAVEFORMATEX,XWaveData,GetFormat,SetFormat,Format);
				//读写属性：音频数据
				PROPERTY_GETSET(VArray<unsigned char>&,XWaveData,GetData,SetData,Data);
				//读写属性：频率
				PROPERTY_GETSET(double,XWaveData,GetHz,SetHz,Hz);
				//读写属性：位数
				PROPERTY_GETSET(short,XWaveData,GetBits,SetBits,Bits);
				//读写属性：声道数
				PROPERTY_GETSET(short,XWaveData,GetChannels,SetChannels,Channels);
				//读写属性：是否是浮点
				PROPERTY_GETSET(bool,XWaveData,GetIsFloat,SetIsFloat,IsFloat);
			};
		};

		//波形类，处理音频格式的转换等
		class VWave:public XBase
		{
			//声道数
			short Channels;
			//位数
			short Bits;
			//频率
			double Hz;
			//浮点
			bool isFloat;
			//缓冲区1
			VArray<unsigned char> buffer;
			//缓冲区2
			VArray<unsigned char> buffer2;
			//上次记录的音量值（每个声道一个值）
			double *lastValue;
			//上次记录的时间值
			double lastTime;
			//时间值,Wati函数专用
			XTime time;
			//将sourceData中的音频数据按toHz的频率和toBits的位数以及toFloat转换并返回
			XArray<unsigned char> HzConvert(const void *sourceData,int length,double toHz,short toBits,bool toFloat=false);
			//目标内存不能跟源内存重叠,声道转换不进行浮点和位数转换
			XArray<unsigned char> ChConvert(const void *sourceData,int length,double Hz,short Bits,bool isFloat,short toChannels);
			VWave(const VWave&){}
			void operator=(const VWave&){}
		public:
			//当前类的类型
			static const XTypes& CurrentType;
			//获取对象类型信息
			virtual const XTypes& GetClassType()const{return CurrentType;}
			//取地址
			VWave* operator&(){return static_cast<VWave*>(XBase::operator&());}
			const VWave* operator&()const{return static_cast<const VWave*>(XBase::operator&());}
			//交换
			virtual void SwapWith(XBase& x){XBase::SwapWith(x);return SwapWith(reinterpret_cast<VWave&>(x));}
			//交换
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
			//读写属性：音量
			double Volume;
			//设置音频源格式
			void SetFormat(double hz,short bits,short channels,bool isfloat = false);
			//设置音频源格式
			void SetFormat(const WAVEFORMATEX& wfx);
			//设置默认音频源格式
			void SetFormat();
			//转换音频格式
			template<typename T>XArray<T> Convert(const XArray<T>&sourceData,double toHz,short toBits, short toChannels,bool toFloat=false);
			//转换音频格式
			template<typename T>XArray<T> Convert(const XArray<T>&sourceData,const WAVEFORMATEX& deswfx);
			//取音频值
			static double GetValue(const void *buffer,short bits,unsigned int sampleIndex,bool isfloat=false);
			//写入音频值
			static void SetValue(void *buffer,double value,short bits,unsigned int sampleIndex,bool isfloat=false);
			//取音频值
			static double GetValue(const void *p,short bits,bool isfloat=false);
			//写入音频值
			static void SetValue(void *p,double value,short bits,bool isfloat=false);
			//生成WAVEFORMATEX音频格式
			static WAVEFORMATEX MakeFormat(int hz,short bits,short ch,bool isfloat=false);
			//将pData2的音频叠加到pData1当中，bits为位数，count为单声道帧数
			template<typename T,typename AnyT>static void Mix(XArray<T>& pDest,const XArray<AnyT>& pData,double vol,short bits,bool isfloat=false);
			//获取size字节的噪音，block的值为0~1的小数，指定网格化参数
			XArray<unsigned char> GetNoise(unsigned int size,double block=0);
			//获取一个指定频率的波形
			XArray<unsigned char> GetWaveWithSingleHz(double hz,unsigned int size,double block=0);
			//获取指定时间长度的噪音，block的值为0~1的小数，指定网格化参数
			XWaveData GetNoiseData(const XTime&time,double block=0);
			//获取指定时间长度的、指定频率的波形
			XWaveData GetWaveDataWithSingleHz(double hz,const XTime&time,double block=0);
			//等待由指定字节数表示的时间
			void Wait(unsigned int size);
		};
		class XWave:public XBase
		{
			PROPERTY_OFFSET(XWave,Volume);
		public:
			XBaseRTypeMethods_H(XWave,VWave);
			//获取音量
			double GetVolume()const{return Pointer()->Volume;}
			//设置音量
			void SetVolume(double vol){Pointer()->Volume=vol;}
			//读写属性：音量
			PROPERTY_GETSET(double,XWave,GetVolume,SetVolume,Volume);
			//设置音频源格式
			void SetFormat(double hz,short bits,short channels,bool isfloat = false){return Pointer()->SetFormat(hz,bits,channels,isfloat);}
			//设置音频源格式
			void SetFormat(const WAVEFORMATEX& wfx){return Pointer()->SetFormat(wfx);}
			//设置默认音频源格式
			void SetFormat(){return Pointer()->SetFormat();}
			//转换音频格式
			template<typename T>XArray<T> Convert(const XArray<T>&sourceData,double toHz,short toBits, short toChannels,bool toFloat=false){return Pointer()->Convert(sourceData,toHz,toBits,toChannels,toFloat);}
			//转换音频格式
			template<typename T>XArray<T> Convert(const XArray<T>&sourceData,const WAVEFORMATEX& w){return Pointer()->Convert(sourceData,w);}
			//取音频值
			static inline double GetValue(const void *buffer,short bits,unsigned int sampleIndex,bool isfloat=false){return VWave::GetValue(buffer,bits,sampleIndex,isfloat);}
			//写入音频值
			static inline void SetValue(void *buffer,double value,short bits,unsigned int sampleIndex,bool isfloat=false){return VWave::SetValue(buffer,value,bits,sampleIndex,isfloat);}
			//取音频值
			static inline double GetValue(const void *p,short bits,bool isfloat=false){return VWave::GetValue(p,bits,isfloat);}
			//写入音频值
			static inline void SetValue(void *p,double value,short bits,bool isfloat=false){return VWave::SetValue(p,value,bits,isfloat);}
			//生成WAVEFORMATEX音频格式
			static inline WAVEFORMATEX MakeFormat(int hz,short bits,short ch,bool isfloat=false){return VWave::MakeFormat(hz,bits,ch,isfloat);}
			//将pData的音频叠加到pDest当中，bits为位数，count为单声道帧数
			template<typename T,typename AnyT>static inline void Mix(XArray<T>& pDest,const XArray<AnyT>& pData,double vol,short bits,bool isfloat=false){return VWave::Mix(pDest,pData,vol,bits,isfloat);}
			//获取size字节的噪音，block的值为0~1的小数，指定网格化参数
			XArray<unsigned char> GetNoise(unsigned int size,double block=0){return Pointer()->GetNoise(size,block);}
			//获取一个指定频率的波形
			XArray<unsigned char> GetWaveWithSingleHz(double hz,unsigned int size,double block=0){return Pointer()->GetWaveWithSingleHz(hz,size,block);}
			//获取指定时间长度的噪音，block的值为0~1的小数，指定网格化参数
			XWaveData GetNoiseData(const XTime&time,double block=0){return Pointer()->GetNoiseData(time,block);}
			//获取指定时间长度的、指定频率的波形
			XWaveData GetWaveDataWithSingleHz(double hz,const XTime&time,double block=0){return Pointer()->GetWaveDataWithSingleHz(hz,time,block);}
			//等待由指定字节数表示的时间
			void Wait(unsigned int size){return Pointer()->Wait(size);}
		};


		template<typename T>XArray<T> VWave::Convert(const XArray<T>&sourceData,double toHz,short toBits, short toChannels,bool toFloat)
		{
			//获得转换后的新内存和单声道帧数量
			XArray<unsigned char> pdata =HzConvert(sourceData,sourceData.LengthOfBytes,toHz,toBits,toFloat);
			//转换声道数
			XArray<unsigned char> pdata2 = ChConvert(pdata,pdata.Length,toHz,toBits,toFloat,toChannels);
			//返回一个引用
			return XArray<T>((pdata2.Length/sizeof(T)),(T*)(void*)pdata2,Reference);
		}
		template<typename T>XArray<T> VWave::Convert(const XArray<T>&sourceData,const WAVEFORMATEX& deswfx)
		{
			return Convert(sourceData,deswfx.nSamplesPerSec,deswfx.wBitsPerSample,deswfx.nChannels,deswfx.wFormatTag==0xfffe);
		}
		template<typename T,typename AnyT>void VWave::Mix(XArray<T>& pData1,const XArray<AnyT>& pData2,double vol,short bits,bool isfloat)
		{
			int tmp = pData1.LengthOfBytes>pData2.LengthOfBytes?pData2.LengthOfBytes:pData1.LengthOfBytes;
			tmp /= bits/8;//总帧数
			if(isfloat)//32位才有浮点
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