//------------------------------------------------------------------------
#include "public.sdk/source/main/pluginfactoryvst3.h"
//
#include "../include/meterController.h"	// for createInstance
#include "../include/meterProcessor.h"	// for createInstance
#include "../include/meterUIDs.h"			// for uids
#include "../include/meterVersion.h"			// for version and naming
//
#define stringSubCategory	"Fx|Analyzer"	// Subcategory for this Plug-in (to be changed if needed, see PlugType in ivstaudioprocessor.h)
//
BEGIN_FACTORY_DEF
(
	stringCompanyName, 
	stringCompanyWeb,	
	stringCompanyEmail
)
	DEF_CLASS2 
	(
		INLINE_UID_FROM_FUID(Carlsound::Meter::MeterProcessorUID),
		Steinberg::PClassInfo::kManyInstances,	// cardinality  
		kVstAudioEffectClass,	// the component category (do not changed this)
		stringPluginName,		// here the Plug-in name (to be changed)
		Vst::kDistributable,	// means that component and controller could be distributed on different computers
		Steinberg::Vst::PlugType::kFxAnalyzer,		// Subcategory for this Plug-in (to be changed) see PlugType in ivstaudioprocessor.h
		FULL_VERSION_STR,		// Plug-in version (to be changed)
		kVstVersionString,		// the VST 3 SDK version (do not changed this, use always this define)
		Carlsound::Meter::MeterProcessor::createInstance // function pointer called when this component should be instantiated
	)	
	//
	DEF_CLASS2 
	(
		INLINE_UID_FROM_FUID(Carlsound::Meter::MeterControllerUID),
		Steinberg::PClassInfo::kManyInstances,  // cardinality   
		kVstComponentControllerClass,// the Controller category (do not changed this)
		stringPluginName "Controller",	// controller name (could be the same than component name)
		0,						// not used here
		"",						// not used here
		FULL_VERSION_STR,		// Plug-in version (to be changed)
		kVstVersionString,		// the VST 3 SDK version (do not changed this, use always this define)
		Carlsound::Meter::MeterController::createInstance // function pointer called when this component should be instantiated
	)
END_FACTORY

//------------------------------------------------------------------------
//  Module init/exit
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// called after library was loaded
bool InitModule ()
{
	return true;
}

//------------------------------------------------------------------------
// called after library is unloaded
bool DeinitModule ()
{
	return true;
}
