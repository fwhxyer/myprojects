#pragma once
#define XSPEAKER_
#include "XWave.h"
namespace LJ
{
	namespace Sound
	{
		//扬声器类，每个类关联一个音频会话
		class VSpeaker:public XBase
		{
			PROPERTY_OFFSET(VSpeaker,Volume);
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
			IAudioRenderClient *pRenderClient;
			//按时间请求音频块大小，10000000分之1秒为单位
			XTime hnsRequestedDuration;
			//设备块总帧数
			UINT32 bufferFrameCount;
			//声音频率，常见的有8000，16000，22500，44100，48000，96000等
			double hz;
			//调用的线程数
			int threadCount;
			//声道数，一般为2
			short ch;
			//比特数，一般为16或32
			short bits;
			//是否正在写入
			bool isWriting;
			//是否为浮点
			bool isFloat;
			//是否正在播放
			bool isPlaying;
			//是否已Start
			bool started;
			//是否正在选择设备
			bool isSelecting;
			//是否正在关闭
			bool isClosing;

			//不允许使用赋值语句
			void operator=(const VSpeaker&){}
			//禁止复制构造
			VSpeaker(const VSpeaker&){}
		public:
			//是否使用默认类型
			bool UsingDefaultDevice;
			//当前类的类型
			static const XTypes& CurrentType;
			//获取对象类型信息
			virtual const XTypes& GetClassType()const{return CurrentType;}
			//取地址
			VSpeaker* operator&(){return static_cast<VSpeaker*>(XBase::operator&());}
			const VSpeaker* operator&()const{return static_cast<const VSpeaker*>(XBase::operator&());}
			//混音格式，（蛋疼）
			WAVEFORMATEX SpeakingFormat;
			//构造函数
			VSpeaker();
			//析构函数
			virtual ~VSpeaker();
			//设置音量大小（vol为放大倍数，一般取0~1，大于1可能会爆破）
			void SetVol(double vol);
			//获取当前音量大小（一般为0~1）
			double GetVol()const;
			//读写属性：音量放大倍数
			PROPERTY_GETSET(double,VSpeaker,GetVol,SetVol,Volume);
			//使用的设备ID
			XString DeviceID;
			//使用的设备名称
			XString DeviceName;
			//开始或继续播放缓冲的数据，该方法应属于异步操作
			void Start();
			//停止播放,清空缓冲数据，该方法应属于异步操作
			void Stop();
			//暂停播放，不清除缓存，该方法应属于异步操作
			void Pause();
			//关闭会话
			void Close();
			//清空缓存内容
			void Clear();
			//写入PCM音频数据,不完成不返回。该操作方法属同步操作
			template<typename T>void Write(const XArray<T>&xArray,int startIndex,int length);
			//写入PCM音频数据,不完成不返回。该操作方法属同步操作
			template<typename T>void Write(const XArray<T>&xArray,int startIndex=0){return Write(xArray,startIndex,xArray.Length-startIndex);}
			//写入PCM音频数据,不完成不返回。该操作方法属同步操作
			template<typename T>void Write(const VArray<T>&xArray,int startIndex,int length){return Write(XArray<T>(xArray.Length,xArray,Reference),startIndex,length);}
			//写入PCM音频数据,不完成不返回。该操作方法属同步操作
			template<typename T>void Write(const VArray<T>&xArray,int startIndex=0){return Write(XArray<T>(xArray.Length,xArray,Reference),startIndex);}
			//写入一个波形数据，不完成不返回,注意该操作将改变输入音频格式设置
			void Write(const VWaveData& data){SetFormat(data.Hz,data.Bits,data.Channels,data.IsFloat);Write(XArray<unsigned char>(data.Data.Length,data.Data,Reference));}
			//写入一个波形数据，不完成不返回,注意该操作将改变输入音频格式设置
			void Write(const XWaveData& data){if(data.IsNull())return;SetFormat(data.Hz,data.Bits,data.Channels,data.IsFloat);Write(XArray<unsigned char>(data.GetData().Length,data.GetData(),Reference));}
			//设置缓存时间长度，以100ns为单位
			void SetBufferTime(const XTime& hms);
			//设置播放的PCM音频格式，isfloat指示是否为浮点
			void SetFormat(double hz,short bits,short ch,bool isFloat = false);
			//设置播放的PCM音频格式（使用系统的PCM格式）
			void SetFormat(const WAVEFORMATEX& fwx);
			//设置默认的PCM音频格式
			void SetToDefaultFormat();
			//获取当前的PCM音频格式，如果只想获取一个属性，其他参数可以传入NULL
			void GetFormat(int* phz,short* pbits,short* pch,bool *isFloat=NULL);
			//获取当前的PCM音频格式
			WAVEFORMATEX GetFormat();
			//获取播放设备的Id列表
			static XArray<XString> GetIdList();
			//获取播放设备的名称列表
			static XArray<XString> GetNameList();
			//按设备Id重新选择设备，成功返回true
			bool SelectDeviceById(const XString& Id);
			//按设备名重新选择设备，成功返回true
			bool SelectDeviceByName(const XString& name);
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
		class XSpeaker:public XBase
		{
			PROPERTY_OFFSET(XSpeaker,Volume);
		public:
			XBaseRTypeMethods_H(XSpeaker,VSpeaker);
			//使用音量大小来创建一个新扬声器
			XSpeaker(double vol):XBase(new VSpeaker()){SetVol(vol);}
			//使用音量值、采样率、声道数、采样位数来创建新的扬声器
			XSpeaker(double vol,double hz,short bits,short ch,bool isFloat=false):XBase(new VSpeaker())
			{SetVol(vol);SetFormat(hz,bits,ch,isFloat);}
			//设置音量大小（vol为放大倍数，一般取0~1，大于1可能会爆破）
			void SetVol(double vol){return Pointer()->SetVol(vol);}
			//获取当前音量大小（一般为0~1）
			double GetVol()const{return Pointer()->GetVol();}
			//获取一个bool值，指示是否使用默认设备
			bool GetUsingDefaultDevice()const{return Pointer()->UsingDefaultDevice;}
			//设置一个bool值，指示是否使用默认设备
			void SetUsingDefaultDevice(bool b){Pointer()->UsingDefaultDevice = b;}
			//获取当前格式
			WAVEFORMATEX GetSpeakingFormat()const{return Pointer()->SpeakingFormat;}
			//设置当前格式
			void SetSpeakingFormat(WAVEFORMATEX x){Pointer()->SpeakingFormat = x;}
			//获取当前设备ID
			XString GetCurrentDeviceID()const{return Pointer()->DeviceID;}
			//获取当前设备名
			XString GetCurrentDeviceName()const{return Pointer()->DeviceName;}
			union
			{
				//读写属性：是否使用默认设备
				PROPERTY_GETSET(bool,XSpeaker,GetUsingDefaultDevice,SetUsingDefaultDevice,UsingDefaultDevice);
				//读写属性：音量放大倍数
				PROPERTY_GETSET(double,XSpeaker,GetVol,SetVol,Volume);
				//读写属性：当前格式
				PROPERTY_GETSET(WAVEFORMATEX,XSpeaker,GetSpeakingFormat,SetSpeakingFormat,SpeakingFormat);
				//只读属性：当前设备ID
				PROPERTY_GET(XString,XSpeaker,GetCurrentDeviceID,DeviceID);
				//只读属性：当前设备名
				PROPERTY_GET(XString,XSpeaker,GetCurrentDeviceName,DeviceName);
			};
			//开始或继续播放缓冲的数据，该方法应属于异步操作
			void Start(){return Pointer()->Start();}
			//停止播放,清空缓冲数据，该方法应属于异步操作
			void Stop(){return Pointer()->Stop();}
			//暂停播放，不清除缓存，该方法应属于异步操作
			void Pause(){return Pointer()->Pause();}
			//关闭会话
			void Close(){return Pointer()->Close();}
			//清空缓存内容
			void Clear(){return Pointer()->Clear();}
			//写入PCM音频数据,不完成不返回。该操作方法属同步操作
			template<typename T>void Write(const XArray<T>&xArray,int startIndex=0){return Pointer()->Write(xArray,startIndex,xArray.Length-startIndex);}
			//写入PCM音频数据,不完成不返回。该操作方法属同步操作
			template<typename T>void Write(const XArray<T>&xArray,int startIndex,int length){return Pointer()->Write(xArray,startIndex,length);}
			//写入一个波形数据，不完成不返回,注意该操作将改变输入音频格式设置
			void Write(const VWaveData& data){return Pointer()->Write(data);}
			//写入一个波形数据，不完成不返回,注意该操作将改变输入音频格式设置
			void Write(const XWaveData& data){return Pointer()->Write(data);}
			//设置缓存时间长度，以100ns为单位
			void SetBufferTime(const XTime& hms){return Pointer()->SetBufferTime(hms);}
			//设置数据的PCM音频格式，isfloat指示是否为浮点
			void SetFormat(double hz,short bits,short ch,bool isFloat = false){return Pointer()->SetFormat(hz, bits, ch, isFloat);}
			//设置数据的PCM音频格式
			void SetFormat(const WAVEFORMATEX& pwfx){return Pointer()->SetFormat(pwfx);}
			//设置默认的PCM音频格式
			void SetToDefaultFormat(){return Pointer()->SetToDefaultFormat();}
			//获取当前设置的数据PCM音频格式，如果只想获取一个属性，其他参数可以传入NULL
			void GetFormat(int* phz,short* pbits,short* pch,bool *isFloat=NULL){return Pointer()->GetFormat(phz, pbits, pch,isFloat);}
			//获取当前的PCM音频格式
			WAVEFORMATEX GetFormat(){return Pointer()->GetFormat();}
			//获取播放设备的Id列表
			static XArray<XString> GetIdList(){return VSpeaker::GetIdList();}
			//获取播放设备的名称列表
			static XArray<XString> GetNameList(){return VSpeaker::GetNameList();}
			//按设备Id重新选择设备，成功返回true
			bool SelectDeviceById(const XString& Id){return Pointer()->SelectDeviceById(Id);}
			//按设备名重新选择设备，成功返回true
			bool SelectDeviceByName(const XString& name){return Pointer()->SelectDeviceByName(name);}
			//设备更改时重启
			void Restart(){return Pointer()->Restart();}
		};

		template<typename T>void VSpeaker::Write(const XArray<T>&xArray,int startIndex,int length)
        {
			HRESULT hr=0;
            if(!pRenderClient)return;
			while(!tc.ThreadTry()){if(isClosing)return;Sleep(1);}
			isWriting = true;
			XArray<T> pdata;
            if(!pRenderClient)goto End;
            UINT32 frames;
            unsigned char *pdes;
			//转换数据格式
			pdata = converter.Convert(xArray.SubArray(startIndex,length,Reference),SpeakingFormat);//获得转换后的新内存和单声道帧数量
			if(buffer.Length<pdata.GetLengthOfBytes()+(int)buffer.GetReadable())buffer.Resize(pdata.GetLengthOfBytes()+buffer.GetReadable());//调整大小
			if((unsigned int)buffer.Length<bufferFrameCount*SpeakingFormat.nBlockAlign)buffer.Resize(bufferFrameCount*SpeakingFormat.nBlockAlign);
            //可填充数据先聚集到buffer中
			buffer.PutAfter(pdata);

			//buffer中可填充数据少于总可填充空间的一半时将直接返回
            if(buffer.GetReadable()<bufferFrameCount*(SpeakingFormat.nBlockAlign/2))
				goto End;

            while(pAudioClient)
            {
                //获取已填充帧数
				if(FAILED(hr=pAudioClient->GetCurrentPadding(&frames)))goto End;
                frames = bufferFrameCount-frames;//获取可写入空间
                if(frames<(bufferFrameCount/2))//可填充空间过少，则需要播放以消耗空间中数据
                {
					tc.ThreadDone();
					Sleep(5);
                    if(!started)//自动开始播放
                        Start();
					while(!tc.ThreadTry()){if(isClosing)return;}
                    continue;
                }
                frames = bufferFrameCount/2;
                if(buffer.GetReadable()>=frames*SpeakingFormat.nBlockAlign && SUCCEEDED(hr=pRenderClient->GetBuffer(frames,&pdes)))//获取内存以填充
                {	
                    XArray<unsigned char>tmp = buffer.GetAfter(frames*SpeakingFormat.nBlockAlign);//从缓存读取数据到指定区域
					Memory::Copy(pdes,tmp,frames*SpeakingFormat.nBlockAlign);
                    if(FAILED(hr=pRenderClient->ReleaseBuffer(frames,NULL)))goto End;
                }
                else
                {
                    goto End;
                }
                if(buffer.GetReadable()<frames*SpeakingFormat.nBlockAlign)break;
            }
End:;
			isWriting = false;
            tc.ThreadDone();
			if(FAILED(hr))throw XSoundException(hr);
        }
	}
}