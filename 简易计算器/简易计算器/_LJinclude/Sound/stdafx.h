#pragma once
#include "..\\XString.h"
#include "..\\XTime.h"
#include "..\\ThreadControl.h"
#include "..\\VBuffer.h"
#include "SoundClasses.h"

#include "Mmdeviceapi.h"
#include "Functiondiscoverykeys_devpkey.h"//PKEY_Device_FriendlyName
#include "Objbase.h"
#include "Audioclient.h"
#pragma comment(lib,"Ole32.lib")

#include "XSoundException.h"
#include "XWave.h"
#include "XSpeaker.h"
#include "XRecorder.h"
#include "SoundEnvironment.h"
#include "DeviceChangeCallback.h"
