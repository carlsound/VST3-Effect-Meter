//------------------------------------------------------------------------
#pragma once
//
#include "pluginterfaces/base/fplatform.h"
//
#define MAJOR_VERSION_STR "1"
#define MAJOR_VERSION_INT 1
//
#define SUB_VERSION_STR "0"
#define SUB_VERSION_INT 0
//
#define RELEASE_NUMBER_STR "0"
#define RELEASE_NUMBER_INT 0
//
#define BUILD_NUMBER_STR "1" // Build number to be sure that each result could identified.
#define BUILD_NUMBER_INT 1
//
// Version with build number (example "1.0.3.342")
#define FULL_VERSION_STR MAJOR_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR "." BUILD_NUMBER_STR
//
// Version without build number (example "1.0.3")
#define VERSION_STR MAJOR_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR
//
// HERE you have to define your plug-in, company name, email and web
//
#if SMTG_PLATFORM_64
#define stringPluginName		"Meter_x64"
#define stringOriginalFilename	"Meter_x64.vst3"
#define stringFileDescription	stringPluginName" VST3-SDK (64Bit)"
#else
#define stringPluginName		"Meter_x86"
#define stringOriginalFilename	"Meter_x86.vst3"
#define stringFileDescription	stringPluginName" VST3-SDK"
#endif
#define stringCompanyName		"Carlsound\0"
#define stringCompanyWeb		"http://www.carlsound.net"
#define stringCompanyEmail		"mailto:john.carlson@carlsound.net"
//
#define stringLegalCopyright	"� 2019 John Carlson"
#define stringLegalTrademarks	"VST is a trademark of Steinberg Media Technologies GmbH"
