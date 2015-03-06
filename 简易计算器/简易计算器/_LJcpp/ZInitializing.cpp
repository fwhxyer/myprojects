#include "stdafx.h"//这个文件专门用来进行静态变量初始化
namespace LJ
{
#ifdef THREADCONTROL_
	//ThreadControl
	ThreadControl ThreadControl::Default;
#endif
#ifdef XRANDOM_
	//XRandom
	XRandom XRandom::Default = XRandom::MakeDefaultXRandom();
#endif
	//VString
	const VString VString::Empty;
	//XString
	const XString XString::Empty = new VString();
	//XException
	const XException XException::None;
#ifdef XTIME_
	//XTime
	StaticProperty<XTime> XTime::Now = StaticProperty<XTime>(XTime::GetLocal,XTime::SetLocal);
#endif
}