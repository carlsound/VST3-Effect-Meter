#pragma once

#include "pluginterfaces/vst/ivstattributes.h"

namespace Carlsound
{
	namespace Vst
	{
		class ComponentAttribute;

		//------------------------------------------------------------------------
		/** Implementation's example of IAttributeList.
		\in group hostingBase
		*/
		class ComponentAttributeList : public Steinberg::Vst::IAttributeList
		{
		public:
			ComponentAttributeList();
			virtual ~ComponentAttributeList();

			Steinberg::tresult PLUGIN_API setInt(AttrID aid, Steinberg::int64 value) SMTG_OVERRIDE;
			Steinberg::tresult PLUGIN_API getInt(AttrID aid, Steinberg::int64& value) SMTG_OVERRIDE;
			Steinberg::tresult PLUGIN_API setFloat(AttrID aid, double value) SMTG_OVERRIDE;
			Steinberg::tresult PLUGIN_API getFloat(AttrID aid, double& value) SMTG_OVERRIDE;
			Steinberg::tresult PLUGIN_API setString(AttrID aid, const Steinberg::Vst::TChar* string) SMTG_OVERRIDE;
			Steinberg::tresult PLUGIN_API getString(AttrID aid, Steinberg::Vst::TChar* string, Steinberg::uint32 size) SMTG_OVERRIDE;
			Steinberg::tresult PLUGIN_API setBinary(AttrID aid, const void* data, Steinberg::uint32 size) SMTG_OVERRIDE;
			Steinberg::tresult PLUGIN_API getBinary(AttrID aid, const void*& data, Steinberg::uint32& size) SMTG_OVERRIDE;

			DECLARE_FUNKNOWN_METHODS
		protected:
			void removeAttrID(AttrID aid);
			std::map<String, ComponentAttribute*> list;
		};
	}
}