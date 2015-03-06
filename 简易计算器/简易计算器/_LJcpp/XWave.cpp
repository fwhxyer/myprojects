#include "stdafx.h"
#ifdef XWAVE_
namespace LJ
{
	namespace Sound
	{
		//VWave类
		const XTypes& VWave::CurrentType = CREATECLASSTYPE(LJ::Sound::VWave,LJ::XBase);
		VWave::VWave()
			:Channels(0),Bits(0),Hz(0),Volume(1.0),isFloat(false),
			lastValue(NULL),
			lastTime(0)
		{
			SetFormat(SoundEnvironment::DefaultHz,SoundEnvironment::DefaultBits,SoundEnvironment::DefaultChannels);//默认音频格式
		}
		VWave::~VWave()
		{
			if(Channels)
				delete []lastValue;
		}
		void VWave::SetFormat(double hz,short bits,short channels,bool isfloat)
		{
			if(channels == Channels && hz==Hz && bits == Bits && isfloat== isFloat)return;
			if(Hz!=hz)
			{
				Hz = hz;
				lastTime = 0;
			}
			Bits = bits;
			isFloat = isfloat;
			if(Channels!=channels)
			{
				if(Channels)delete []lastValue;
				if(channels)
				{
					lastValue = new double[channels];
				}
				else lastValue = NULL;
				for(Channels=0;Channels<channels;++Channels)lastValue[Channels]=0;
			}
		}
		void VWave::SetFormat(const WAVEFORMATEX& wfx)
		{
			SetFormat(wfx.nSamplesPerSec,wfx.wBitsPerSample,wfx.nChannels,wfx.wFormatTag == 0xfffe);
		}
		void VWave::SetFormat()
		{
			SetFormat(SoundEnvironment::DefaultHz,SoundEnvironment::DefaultBits,SoundEnvironment::DefaultChannels);//默认
		}
		XArray<unsigned char> VWave::HzConvert(const void* sourceData,int length,double toHz,short toBits,bool toFloat)
		{
			int sourceSampleCount = length/(Bits/8);
			if(toHz<=0)return XArray<unsigned char>(0);
			double tmp = (double)toHz/Hz*(toBits/8);
			if((double)buffer.Length<tmp*(Channels+sourceSampleCount))//按照初步预算调整缓存大小
				buffer.ResizeAndDestroy((int)(tmp*(Channels+sourceSampleCount)));
			unsigned char* pdat = buffer;//目标内存区
			double prop(Volume);//幅值比例关系
			if(!this->isFloat)//源数据非浮点
				prop/=(unsigned long long(1)<<(Bits-1));
			if(!toFloat)//目标非浮点
				prop*=(unsigned long long(1)<<(toBits-1));
			if(Hz>toHz)//往低频转换
			{
				double value;//瞬时幅值
				int t_low(0);//低频侧帧编号
				for(int t(0);t<sourceSampleCount;t+=Channels)
				{
					lastTime += toHz;//高频时间轴
					for(int c(0);c<Channels;++c)//声道切换
					{
						value = prop*GetValue(sourceData,Bits,c+t,this->isFloat);//获取当前幅值
						if(lastTime>=Hz)
						{
							SetValue(pdat,(lastValue[c]+(Hz-(lastTime-toHz))*value)/Hz,toBits,t_low+c,toFloat);//等值幅度
							lastValue[c] = (lastTime-Hz)*value;//剩余面积
						}
						else lastValue[c]+=value*toHz;//面积增加
					}
					if(lastTime>=Hz)
					{
						t_low+=Channels;//前进
						lastTime-=Hz;//剩余时间
					}
				}
				return XArray<unsigned char>(t_low*toBits/8,pdat,Reference);
			}
			else if(Hz<toHz)//往高频转换
			{
				double value;//瞬时幅值
				int t_high(0);//高频侧帧编号
				for(int t(0);t<sourceSampleCount;t+=Channels)
				{
					lastTime += toHz;//低频时间轴
					tmp = 0;
					for(;;)
					{
						for(int c(0);c<Channels;++c)//声道切换
						{
							value = prop*GetValue(sourceData,Bits,c+t,this->isFloat);//获取当前幅值
							if(lastTime>=Hz)
							{
								SetValue(pdat,(lastValue[c]+(Hz-(lastTime-toHz+tmp))*value)/Hz,toBits,t_high+c,toFloat);//等值幅度
								lastValue[c] = 0;//剩余面积
							}
							else lastValue[c]+=value*lastTime;//最终剩余面积
						}
						if(lastTime>=Hz)
						{
							t_high+=Channels;//前进
							lastTime-=Hz;//剩余时间
							tmp = toHz - lastTime;
						}
						else break;
					}
				}
				return XArray<unsigned char>(t_high*toBits/8,pdat,Reference);
			}
			else//频率无变动
			{

				for(int i=0;i<sourceSampleCount;++i)
				{
					SetValue(pdat,prop*GetValue(sourceData,Bits,i,this->isFloat),toBits,i,toFloat);
				}
			}
			return XArray<unsigned char>(sourceSampleCount*toBits/8,pdat,Reference);
		}
		XArray<unsigned char> VWave::ChConvert(const void* sourceData,int length,double Hz,short Bits,bool isFloat,short toChannels)
		{
			int sourceSampleCount = length/(Bits/8);//源帧数
			if(toChannels==Channels)//无转换
			{
				return XArray<unsigned char>(sourceSampleCount*Bits/8,(unsigned char*)sourceData,Reference);
			}
			if(toChannels>Channels)//声道数少的向声道数高的转换
			{
				unsigned int desCount(sourceSampleCount*toChannels/Channels);//目标单声道帧数
				if((unsigned int)buffer2.Length<desCount*Bits/8)buffer2.ResizeAndDestroy(desCount*Bits/8);
				if(toChannels>Channels)desCount -= desCount%toChannels;//修剪
				for(unsigned int i(0),j(0);i<desCount;i+=toChannels,j+=Channels)
				{
					for(int k(0);k<toChannels;++k)
					{
						SetValue((unsigned char*)buffer2,GetValue(sourceData,Bits,j+k%Channels,isFloat),Bits,i+k,isFloat);
					}
				}
				return XArray<unsigned char>(desCount*Bits/8,buffer2,Reference);
			}
			else//声道数高的混音到声道数低的
			{
				unsigned int desCount(sourceSampleCount*toChannels/Channels);//目标单声道帧数
				if((unsigned int)buffer2.Length<desCount*Bits/8)buffer2.Resize(desCount*Bits/8);
				sourceSampleCount -= sourceSampleCount%Channels;//修剪
				double vol = (double)toChannels/Channels;
				desCount = 0;
				for(int i(0);i<sourceSampleCount;i+=Channels)//顺着写入
				{
					for(int j(0);j<toChannels;++j)//先写入可写入的值
						SetValue(buffer2,GetValue(sourceData,Bits,j+i,isFloat)*vol,Bits,desCount+j,isFloat);
					for(int j(toChannels);j<Channels;++j)//叠加
						SetValue(buffer2,GetValue(sourceData,Bits,i+j,isFloat)*vol+GetValue(buffer2,Bits,desCount+j%toChannels,isFloat),Bits,desCount+j%toChannels,isFloat);
					desCount+=toChannels;
				}
				return XArray<unsigned char>(desCount*Bits/8,buffer2,Reference);
			}
		}
		double VWave::GetValue(const void *buffer,short bits,unsigned int sampleIndex,bool isfloat)
		{
			return GetValue((char*)buffer+sampleIndex*bits/8,bits,isfloat);
		}
		void VWave::SetValue(void *buffer,double value,short bits,unsigned int sampleIndex,bool isfloat)
		{
			SetValue((char*)buffer+sampleIndex*bits/8,value,bits,isfloat);
		}
		double VWave::GetValue(const void *buffer,short bits,bool isfloat)
		{
			double value;
			switch(bits)
			{
			case 64:*((long long*)&value) = *((const long long*)buffer);break;
			case 32:*((int*)&value) = *((const int*)buffer);break;
			case 16:*((short*)&value) = *((const short*)buffer);break;
			default:*((char*)&value) = *((const char*)buffer);break;
			}
			if(isfloat)
			{
				if(64 == bits)return value;
				if(32 == bits)return ((float*)&value)[0];
				if(8 == bits)return ((signed char*)&value)[0];
			}
			if(64 == bits)return double(*((long long*)&value));
			if(32 == bits)return *((int*)&value);
			if(16 == bits)return *((short*)&value);
			return ((unsigned char*)&value)[0] - 128;
		}
		void VWave::SetValue(void *buffer,double value,short bits,bool isfloat)
		{
			if(isfloat)
			{
				if(64 == bits)
				{
					*(double*)buffer = value;
					return;
				}
				else if(32 == bits)
				{
					if(value>1)value=1;
					if(value<-1)value=-1;
					*((float*)buffer) = (float)value;
					return;
				}
				else if(8 == bits)
				{
					if(value>127)value=127;
					if(value<-128)value=-128;
					*((signed char*)buffer) = (char)value;
					return;
				}
			}
			else
			{
				if(64 == bits)
				{
					if(value>(long long)(-1^0x8000000000000000))value=(double)(long long)(-1^0x8000000000000000);
					if(value<(long long)(0x8000000000000000))value=(double)(long long)0x8000000000000000;
					*((long long*)buffer) = (long long)value;
					return;
				}
				else if(32 == bits)
				{
					if(value>2147483647)
						value=2147483647;
					if(value<-2147483648.0)
						value=-2147483648.0;
					*((int*)buffer) =(int)value;
					return;
				}
				else if(16 == bits)
				{
					if(value>=32767.0)value=32767;
					if(value<=-32768.0)value=-32768;
					*((short*)buffer) = (short)value;
					return;
				}
				else
				{
					if(value>127)value=127;
					if(value<-128)value=-128;
					*((unsigned char*)buffer) = (unsigned char)(value + 128);
				}
			}
		}
		WAVEFORMATEX VWave::MakeFormat(int hz,short bits,short ch,bool isfloat)
		{
			WAVEFORMATEX wfx;
			wfx.nSamplesPerSec = hz;
			if(isfloat)
			{
				wfx.wFormatTag = 0xfffe;
			}
			else wfx.wFormatTag = WAVE_FORMAT_PCM;
			wfx.wBitsPerSample = bits;
			wfx.nChannels = ch;
			wfx.nBlockAlign = bits/8*ch;
			wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;
			wfx.cbSize = 0;
			return wfx;
		}
		XArray<unsigned char> VWave::GetNoise(unsigned int size,double block)//获取size字节的噪音
		{
			size -= size%(Bits/8);
			if(!size)return buffer.SubArray(0,0,Reference);
			if(buffer.Length<(int)size)buffer.ResizeAndDestroy(size);
			if(isFloat && Bits==32)//浮点
			{
				for(unsigned int i=0;i<size;i+=4)
				{
					double t = XRandom::Default.NextDouble();//获取一个浮点值
					if(XRandom::Default.Rand()&1)t = -t;
					if(block>1e-10)//网格化
					{
						long long tmp = 0;
						if(t>=block || t<=-block)
							tmp = long long(t/block);//取整
						t = double(tmp)*block;
					}
					SetValue(buffer+i,Volume*t,Bits,true);//写入值
				}
				return buffer.SubArray(0,size,Reference);
			}
			int ub = int(block * (unsigned long long(1)<<(Bits-1)));
			for(unsigned int i=0;i<size;i+=Bits/8)
			{
				int t = XRandom::Default.NextUInt();//获取一个随机值
				t>>= 32-Bits;
				if(ub>0)
				{
					int tmp = 0;
					if(t>=ub || t<=-ub)
						tmp = t/ub;//取整
					t = tmp*ub;
				}
				SetValue(buffer+i,Volume*t,Bits,false);//写入值
			}
			return buffer.SubArray(0,size,Reference);
		}
		XArray<unsigned char> VWave::GetWaveWithSingleHz(double hz,unsigned int size,double block)
		{
			if(buffer.Length<(int)size)buffer.ResizeAndDestroy(size);
			unsigned count = size*8/Bits;
			unsigned long long mov = unsigned long long(1)<<(Bits-1);
			for(unsigned int i=0;i+Channels<=count;i+=Channels)
			{
				for(int j=0;j<Channels;++j)
				{
					if(lastValue[j]>1000 || lastValue[j]<-1000)
						lastValue[j] = 0;//复位，lastvalue数组记录时间的相对位移
					double t = std::sin(lastValue[j]);
					if(block>1e-10)//网格化
					{
						long long tmp = 0;
						if(t>=block || t<=-block)
							tmp = long long(t/block);//取整
						t = double(tmp)*block;
					}
					if(isFloat && Bits==32)SetValue(buffer,t*Volume,32,i+j,true);
					else SetValue(buffer,t*Volume*mov,Bits,i+j,false);
					if(lastValue[j]>2*3.141592653)
						lastValue[j]-=2*3.141592653;
					lastValue[j] += 2*3.141592653/Hz*hz;
				}
			}
			return XArray<unsigned char>(size,(unsigned char*)buffer,Reference);
		}
		XWaveData VWave::GetNoiseData(const XTime& t,double block)//获取time时长的噪音(一个引用)
		{
			if(t<=0)throw XSoundException(E_INVALIDARG);
			XWaveData tdata(new VWaveData);
			tdata.Hz=Hz; tdata.Bits=Bits; tdata.Channels=Channels; tdata.IsFloat=isFloat;
			time +=t;
			int samples = int(time*Hz/XTime::EverySecond - lastTime);
			lastTime+= samples;
			if(time>XTime::EverySecond && lastTime>Hz)
			{
				time.time%=XTime::EverySecond;
				lastTime = (int)lastTime%(int)Hz;
			}
			if(!samples)return tdata;
			samples *= Bits/8;
			if(buffer.Length<samples)buffer.ResizeAndDestroy(samples);
			if(isFloat && Bits==32)//浮点
			{
				for(int i=0;i<samples;i+=4)
				{
					double t = XRandom::Default.NextDouble();//获取一个浮点值
					if(XRandom::Default.Rand()&1)t = -t;
					if(block>1e-10)//网格化
					{
						long long tmp = 0;
						if(t>=block || t<=-block)
							tmp = long long(t/block);//取整
						t = double(tmp)*block;
					}
					SetValue(buffer+i,Volume*t,Bits,true);//写入值
				}
				tdata.GetData().SwapWith(VArray<unsigned char>(samples,buffer,Reference));
				return tdata;
			}
			int ub = int(block * (unsigned long long(1)<<(Bits-1)));
			for(int i=0;i<samples;i+=Bits/8)
			{
				int t = XRandom::Default.NextUInt();//获取一个随机值
				t>>= 32-Bits;
				if(ub>0)
				{
					int tmp = 0;
					if(t>=ub || t<=-ub)
						tmp = t/ub;//取整
					t = tmp*ub;
				}
				SetValue(buffer+i,Volume*t,Bits,false);//写入值
			}
			tdata.GetData().SwapWith(VArray<unsigned char>(samples,buffer,Reference));
			return tdata;
		}
		XWaveData VWave::GetWaveDataWithSingleHz(double hz,const XTime& t,double block)
		{
			if(t<=0)throw XSoundException(E_INVALIDARG);
			XWaveData tdata(new VWaveData);
			tdata.Hz=Hz; tdata.Bits=Bits; tdata.Channels=Channels; tdata.IsFloat=isFloat;
			time +=t;
			int samples = int(time*Hz/XTime::EverySecond - lastTime);
			lastTime+= samples;
			if(time>XTime::EverySecond && lastTime>Hz)
			{
				time.time%=XTime::EverySecond;
				lastTime = (int)lastTime%(int)Hz;
			}
			if(!samples)return tdata;
			samples *= Bits/8;
			if(buffer.Length<samples)buffer.ResizeAndDestroy(samples);
			unsigned count = samples*8/Bits;
			unsigned long long mov = unsigned long long(1)<<(Bits-1);
			for(unsigned int i=0;i+Channels<=count;i+=Channels)
			{
				for(int j=0;j<Channels;++j)
				{
					if(lastValue[j]>1000 || lastValue[j]<-1000)
						lastValue[j] = 0;//复位，lastvalue数组记录时间的相对位移
					double t = std::sin(lastValue[j]);
					if(block>1e-10)//网格化
					{
						long long tmp = 0;
						if(t>=block || t<=-block)
							tmp = long long(t/block);//取整
						t = double(tmp)*block;
					}
					if(isFloat && Bits==32)SetValue(buffer,t*Volume,32,i+j,true);
					else SetValue(buffer,t*Volume*mov,Bits,i+j,false);
					if(lastValue[j]>2*3.141592653)
						lastValue[j]-=2*3.141592653;
					lastValue[j] += 2*3.141592653/Hz*hz;
				}
			}
			tdata.GetData().SwapWith(VArray<unsigned char>(samples,buffer,Reference));
			return tdata;
		}
		void VWave::Wait(unsigned int size)
		{
			if(!size)return;
			XTime tmp = long long(size/(Hz*Bits/8*Channels)*XTime::EverySecond);//应该等待的时间
			XTime span = XTime::Now-time;//获取时间间隔
			if(span>tmp*10)//时间间隔过长，通常是由于卡机或初次等待导致
			{
				time = XTime::Now;
				return;
			}
			while(span<tmp)
			{
				Sleep(10);
				span = XTime::Now-time;
			}
			time+=tmp;
			return;
		}


		//XWave类
		const XTypes& XWave::CurrentType=CREATECLASSTYPE(LJ::Sound::XWave,LJ::XBase);
		//VWaveData类
		const XTypes& VWaveData::CurrentType=CREATECLASSTYPE(LJ::Sound::VWaveData,LJ::XBase);
		WAVEFORMATEX VWaveData::GetFormat()const{return VWave::MakeFormat((int)Hz,Bits,Channels,IsFloat);}
		VWaveData::VWaveData():Hz(SoundEnvironment::DefaultHz),Bits(SoundEnvironment::DefaultBits),Channels(SoundEnvironment::DefaultChannels),IsFloat(false){}
		//XWaveData类
		const XTypes& XWaveData::CurrentType=CREATECLASSTYPE(LJ::Sound::XWaveData,LJ::XBase);

	}
}
#endif