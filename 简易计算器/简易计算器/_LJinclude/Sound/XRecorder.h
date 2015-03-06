#pragma once
#define XRECORDER_
#include "XWave.h"
namespace LJ
{
	namespace Sound
	{
		//录音机类
		class VRecorder:public XBase
		{
			//线程同步控制
			ThreadControl tc;
			//音频格式转换
			VWave converter;
			//数据缓冲区
			VBuffer buffer;

			//代表指定的设备
			IMMDevice *pDevice;
			//音频会话
			IAudioClient *pAudioClient;
			//音频播放客户端
			IAudioCaptureClient *pCaptureClient;
			//按时间请求音频块大小，10000000分之1秒为单位
			XTime hnsRequestedDuration;
			//设备块总帧数
			UINT32 bufferFrameCount;
			//声音采样率，常见的有8000，16000，22500，44100，48000，96000等
			double hz;
			//声道数，一般为2
			short ch;
			//比特数，一般为16或32
			short bits;
			//是否为浮点
			bool isFloat;
			//是否正在录音
			bool isRecording;
			//是否正在选择设备
			bool isSelecting;
			//是否已Start
			bool started;
			//是否正在关闭
			bool isClosing;

			//不允许复制
			VRecorder(const VRecorder&){}
			//不允许使用赋值语句
			void operator=(const VRecorder){}

			PROPERTY_OFFSET(VRecorder,Volume);
		public:
			//是否始终使用默认设备（默认设备变动时自动改用默认设备）
			bool UsingDefaultDevice;
			//混音格式，（蛋疼）
			WAVEFORMATEX CurrentFormat;
			//初始化
			VRecorder();
			//析构
			~VRecorder();
			//取地址
			VRecorder* operator&(){return reinterpret_cast<VRecorder*>(XBase:: operator&());}
			//取地址
			const VRecorder* operator&()const{return reinterpret_cast<const VRecorder*>(XBase:: operator&());}
			//设置音量大小（vol为放大倍数，一般取0~1，大于1可能会爆破）
			void SetVol(double vol);
			//获取当前音量大小（一般为0~1）
			double GetVol()const;
			//获取当前采样率
			double GetHz()const;
			//获取当前声道数
			short GetChannels()const;
			//获取当前位数
			short GetBits()const;
			//获取是否为浮点
			bool GetIsFloat()const;
			//使用的设备ID
			const XString DeviceID;
			//使用的设备名称
			const XString DeviceName;
			union
			{
				//读写属性：音量大小
				PROPERTY_GETSET(double,VRecorder,GetVol,SetVol,Volume);
				//只读属性，采样率
				PROPERTY_GET(double,VRecorder,GetHz,Hz);
				//只读属性，音频位数
				PROPERTY_GET(short,VRecorder,GetBits,Bits);
				//只读属性，音频声道数
				PROPERTY_GET(short,VRecorder,GetChannels,Channels);
				//只读属性，音频是否为浮点
				PROPERTY_GET(bool,VRecorder,GetIsFloat,IsFloat);
			};

			//启动录音
			void Start();
			//停止录音
			void Stop();
			//暂停录音(与停止录音的区别在于ReaData函数不立即返回)
			void Pause();
			//关闭会话
			void Close();
			//清除缓存数据
			void Clear();
			//设置输出的PCM音频格式
			void SetOutFormat(double hz,short bits,short ch,bool isfloat = false);
			//设置输出的PCM音频格式（使用系统的PCM格式）
			void SetOutFormat(const WAVEFORMATEX& fwx);
			//获取当前输出的PCM音频格式，如果只想获取一个属性，其他参数可以传入NULL
			void GetOutFormat(int* phz,short* pbits,short* pch,bool* pisfloat=NULL);
			//获取当前输出的PCM音频格式，如果只想获取一个属性，其他参数可以传入NULL
			void GetOutFormat(double* phz,short* pbits,short* pch,bool* pisfloat=NULL);
			//获取数出音频格式
			WAVEFORMATEX GetOutFormat();
			//获取源音格式
			WAVEFORMATEX& GetSourceFormat();
			//获取源音格式
			void GetSourceFormat(int* phz,short* pbits,short* pch,bool* pisfloat = NULL);
			//设置缓存时间长度
			void SetBufferTime(const XTime& hms);
			//选择设备
			bool SelectDeviceById(const XString Id);
			//选择设备
			bool SelectDeviceByName(const XString& Name);
			//读取len长的数据，不读够不返回(此函数自动启动录音)
			XArray<unsigned char> Read(int len);
			//读取一个使用源音格式的音频数据包
			XWaveData Read();
			//设备更改时重启
			void Restart();
			//设备添加事件
			void OnDeviceAdded();
			//设备状态改变事件
			void OnDeviceStateChanged();
			//设备移除事件
			void OnDeviceRemoved();
			//默认设备改变事件
			void OnDefaultDeviceChanged();
			//设备属性改变事件
			void OnDevicePropertyValueChanged();
		};

		class XRecorder:public XBase
		{
			PROPERTY_OFFSET(XRecorder,Volume);
		public:
			XBaseRTypeMethods_H(XRecorder,VRecorder);
			//使用输出音量放大倍数来创建一个新的录音机对象
			XRecorder(double vol):XBase(new VRecorder()){SetVol(vol);}
			//使用输出音量放大倍数、输出采样率、输出采样位数、输出声道数、是否浮点创建新的录音机对象
			XRecorder(double vol,double hz,short bits,short channels,bool isFloat=false):XBase(new VRecorder())
			{SetVol(vol);SetOutFormat(hz,bits,channels,isFloat);}
			//设置音量大小（vol为放大倍数，一般取0~1，大于1可能会爆破）
			void SetVol(double vol){Pointer()->SetVol(vol);}
			//获取当前音量大小（一般为0~1）
			double GetVol()const{return Pointer()->GetVol();}
			//获取当前采样率
			double GetHz()const{return Pointer()->GetHz();}
			//获取当前声道数
			short GetChannels()const{return Pointer()->GetChannels();}
			//获取当前位数
			short GetBits()const{return Pointer()->GetBits();}
			//获取是否为浮点
			bool GetIsFloat()const{return Pointer()->GetIsFloat();}
			//获取一个bool值，指示是否在默认设备更改时自动切换到新的默认设备
			bool GetUsingDefaultDevice()const{return Pointer()->UsingDefaultDevice;}
			//设置一个bool值，指示是否在默认设备更改时自动切换到新的默认设备
			void SetUsingDefaultDevice(bool b){Pointer()->UsingDefaultDevice = b;}
			//获取当前使用的音频格式
			WAVEFORMATEX GetCurrentFormat()const{return Pointer()->CurrentFormat;}
			//使用的设备ID
			XString GetDeviceID()const{return Pointer()->DeviceID;}
			//使用的设备名称
			XString GetDeviceName()const{return Pointer()->DeviceName;}
			union
			{
				//读写属性：音量大小
				PROPERTY_GETSET(double,XRecorder,GetVol,SetVol,Volume);
				//只读属性，采样率
				PROPERTY_GET(double,XRecorder,GetHz,Hz);
				//只读属性，音频位数
				PROPERTY_GET(short,XRecorder,GetBits,Bits);
				//只读属性，音频声道数
				PROPERTY_GET(short,XRecorder,GetChannels,Channels);
				//只读属性，音频是否为浮点
				PROPERTY_GET(bool,XRecorder,GetIsFloat,IsFloat);
				//读写属性，一个bool值指示是否在默认设备更改时自动切换到新的默认设备
				PROPERTY_GETSET(bool,XRecorder,GetUsingDefaultDevice,SetUsingDefaultDevice,UsingDefaultDevice);
				//只读属性：混音格式
				PROPERTY_GET(WAVEFORMATEX,XRecorder,GetCurrentFormat,CurrentFormat);
				//只读属性：使用的设备ID
				PROPERTY_GET(XString,XRecorder,GetDeviceID,DeviceID);
				//只读属性：使用的设备名称
				PROPERTY_GET(XString,XRecorder,GetDeviceName,DeviceName);
			};

			//启动录音
			void Start(){return Pointer()->Start();}
			//停止录音
			void Stop(){return Pointer()->Stop();}
			//暂停录音(与停止录音的区别在于ReaData函数不立即返回)
			void Pause(){return Pointer()->Pause();}
			//关闭会话
			void Close(){return Pointer()->Close();}
			//清除缓存数据
			void Clear(){return Pointer()->Clear();}
			//设置输出的PCM音频格式
			void SetOutFormat(double hz,short bits,short ch,bool isfloat = false){return Pointer()->SetOutFormat(hz,bits,ch,isfloat);}
			//设置输出的PCM音频格式（使用系统的PCM格式）
			void SetOutFormat(const WAVEFORMATEX& fwx){return Pointer()->SetOutFormat(fwx);}
			//获取当前输出的PCM音频格式，如果只想获取一个属性，其他参数可以传入NULL
			void GetOutFormat(int* phz,short* pbits,short* pch,bool* pisfloat=NULL){return Pointer()->GetOutFormat(phz,pbits,pch,pisfloat);}
			//获取当前输出的PCM音频格式，如果只想获取一个属性，其他参数可以传入NULL
			void GetOutFormat(double* phz,short* pbits,short* pch,bool* pisfloat=NULL){return Pointer()->GetOutFormat(phz, pbits, pch, pisfloat);}
			//获取数出音频格式
			WAVEFORMATEX GetOutFormat(){return Pointer()->GetOutFormat();}
			//获取源音格式
			WAVEFORMATEX& GetSourceFormat(){return Pointer()->GetSourceFormat();}
			//获取源音格式
			void GetSourceFormat(int* phz,short* pbits,short* pch,bool* pisfloat = NULL){return Pointer()->GetSourceFormat(phz, pbits, pch, pisfloat);}
			//设置缓存时间长度
			void SetBufferTime(const XTime& hms){return Pointer()->SetBufferTime(hms);}
			//选择设备
			bool SelectDeviceById(const XString id){return Pointer()->SelectDeviceById(id);}
			//选择设备
			bool SelectDeviceByName(const XString& name){return Pointer()->SelectDeviceByName(name);}
			//读取len长的数据，不读够不返回(此函数自动启动录音)
			XArray<unsigned char> Read(int len){return Pointer()->Read(len);}
			//读取一个使用源音格式的音频数据包
			XWaveData Read(){return Pointer()->Read();}
			//设备更改时重启
			void Restart(){return Pointer()->Restart();}
		};
	}
}