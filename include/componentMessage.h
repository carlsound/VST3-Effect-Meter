#pragma once

#include "componentAttributeList.h"

#include "pluginterfaces/vst/ivstattributes.h"
#include "pluginterfaces/vst/ivstmessage.h"

namespace Carlsound
{
	namespace Vst
	{
		/** Implementation's example of IMessage.
		\in group hostingBase
		*/
		class ComponentMessage : public Steinberg::Vst::IMessage
		{
		public:
			ComponentMessage();
			virtual ~ComponentMessage();

			const char* PLUGIN_API getMessageID() SMTG_OVERRIDE;
			void PLUGIN_API setMessageID(const char* messageID) SMTG_OVERRIDE;
			Steinberg::Vst::IAttributeList* PLUGIN_API getAttributes() SMTG_OVERRIDE;

			DECLARE_FUNKNOWN_METHODS
		protected:
			char* messageId;
			ComponentAttributeList* attributeList;
		};
	}
}