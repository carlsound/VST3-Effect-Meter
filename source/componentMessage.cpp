#include "../include/componentMessage.h"

namespace Carlsound
{
	namespace Vst
	{
		IMPLEMENT_FUNKNOWN_METHODS(ComponentMessage, IMessage, IMessage::iid)
			//-----------------------------------------------------------------------------
			ComponentMessage::ComponentMessage() : messageId(0), attributeList(0)
		{
			FUNKNOWN_CTOR
		}

		//-----------------------------------------------------------------------------
		ComponentMessage::~ComponentMessage()
		{
			setMessageID(0);
			if (attributeList)
				attributeList->release();
			FUNKNOWN_DTOR
		}

		//-----------------------------------------------------------------------------
		const char* PLUGIN_API ComponentMessage::getMessageID()
		{
			return messageId;
		}

		//-----------------------------------------------------------------------------
		void PLUGIN_API ComponentMessage::setMessageID(const char* mid)
		{
			if (messageId)
				delete[] messageId;
			messageId = 0;
			if (mid)
			{
				size_t len = strlen(mid) + 1;
				messageId = new char[len];
				strcpy(messageId, mid);
			}
		}

		//-----------------------------------------------------------------------------
		Steinberg::Vst::IAttributeList* PLUGIN_API ComponentMessage::getAttributes()
		{
			if (!attributeList)
				attributeList = new ComponentAttributeList;
			return attributeList;
		}
	}
}
