#pragma once
//
#include <codecvt>
#include <memory>
#include <string>
#include <iostream>
//
#include "componentMessage.h"
#include "ideConsoleWriteLine.h"
#include "meterParameters.h"
#include "meterUIDs.h"
//
#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/base/ustring.h"
#include "pluginterfaces/vst/ivstattributes.h"
#include "pluginterfaces/vst/ivstmidicontrollers.h"
#include "pluginterfaces/vst/vsttypes.h"
#include "public.sdk/source/vst/hosting/stringconvert.h"
#include "public.sdk/source/vst/vsteditcontroller.h"
#include "public.sdk/source/vst/hosting/hostclasses.h"
#include "public.sdk/source/vst/hosting/stringconvert.h"
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "public.sdk/source/vst/vsteditcontroller.h"
//
//#include "vstgui4/vstgui/plugin-bindings/vst3editor.h"
//#include "vstgui4/vstgui/vstgui.h"
//#include "vstgui4/vstgui/vstgui_uidescription.h"
//
#if SMTG_OS_WINDOWS
#include <atlconv.h>
#include <tchar.h>
#include "../../Win_Ultralight/include/meterPlugViewUltralightWin32.h"
//#include "../../Win_WPF/Cpp_CLI/include/WpfPlugView.h"
//#include "vstgui4/vstgui/vstgui_win32.cpp"
//#include "vstgui4/vstgui/vstgui_uidescription_win32.cpp"
#endif
//
#if SMTG_OS_MACOS || SMTG_OS_OSX
//#include <Cocoa/Cocoa.h>
//#include "../../Mac_Cocoa/include/meterPlugViewCocoa.h"
//#include "vstgui4/vstgui/vstgui_mac.mm"
//#include "vstgui4/vstgui/vstgui_uidescription_mac.mm"
#endif
