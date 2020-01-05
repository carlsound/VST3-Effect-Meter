#pragma once
//
#include "../../../Cpp/include/stdafx.h"
//
//#include "LoadMissingDll.h"
//
#include "base/source/fobject.h"
//
//#include "pluginterfaces/gui/iplugview.h"
//#include "public.sdk/source/vst/vsteditcontroller.h"
#include "public.sdk/source/common/pluginview.h"
//
#include <string.h>
#include <msclr\auto_gcroot.h>
//#include <vcclr.h>
#include <windows.h>
#include <WinUser.h>
//
//#using <PresentationCore.dll>
//#using <PresentationFramework.dll>
//#using <WindowsBase.dll>
//
//#include "nativeInterface.h"
//extern void* moduleHandle;
//
#include <pluginterfaces\vst\vsttypes.h>
//
#include "../../../Cpp/include/IMeterPluginView.h"
//#using "C:/Program Files/Common Files/VST3/Meter_WPF_UI_CS_XAML_AnyCPU.dll"
#import "./Meter_WPF_UI_CS_XAML_AnyCPU.tlb" raw_interfaces_only