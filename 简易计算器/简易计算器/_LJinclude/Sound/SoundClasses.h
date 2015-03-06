#pragma once
#include "..\\classes.h"
namespace LJ
{
	namespace Sound
	{
		//音频环境，这里设置和获取底层信息
		class SoundEnvironment;
		//处理音频信息变化的回调类
		class DeviceChangeCallback;
		//扬声类
		class XSpeaker;
		//录音类
		class XRecorder;
		//管理波形的取值和转换
		class XWave;
		//异常
		class XSoundException;
	}
}