#pragma once
//
#include "componentMessage.h"
#include "meterController.h"
#include "meterParameters.h"
#include "meterUIDs.h"
//
#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/vst/vsttypes.h"
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "public.sdk/source/vst/vstparameters.h"
#include "public.sdk/source/vst/hosting/hostclasses.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h"
//
#define _USE_MATH_DEFINES 
#include <cmath>