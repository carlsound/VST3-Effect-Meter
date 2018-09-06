#pragma once
//
#include "componentMessage.h"
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
//#include "public.sdk/source/vst/hosting/hostclasses.h"
#include "public.sdk/source/vst/hosting/stringconvert.h"
#include "public.sdk/source/vst/vstaudioeffect.h"
//#include "vstgui4/vstgui/plugin-bindings/vst3editor.h"
//
#include <string>
//
#if SMTG_OS_WINDOWS
#include <atlconv.h>
#include <tchar.h>
#endif
//
#include <codecvt>
#include <memory>
#include <string>