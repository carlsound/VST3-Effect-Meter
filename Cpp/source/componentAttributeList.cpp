#include "../include/componentAttributeList.h"

namespace Carlsound
{
	namespace Vst
	{
		IMPLEMENT_FUNKNOWN_METHODS(ComponentAttributeList, IAttributeList, IAttributeList::iid)
		//-----------------------------------------------------------------------------
		ComponentAttributeList::ComponentAttributeList()
		{
			FUNKNOWN_CTOR
		}
		//-----------------------------------------------------------------------------
		ComponentAttributeList::~ComponentAttributeList()
		{
			std::map<Steinberg::String, ComponentAttribute*>::reverse_iterator it = list.rbegin();
			while (it != list.rend())
			{
				delete it->second;
				it++;
			}
			FUNKNOWN_DTOR
		}
		//-----------------------------------------------------------------------------
		void ComponentAttributeList::removeAttrID(AttrID aid)
		{
			mapIterator it = list.find(aid);
			if (it != list.end())
			{
				delete it->second;
				list.erase(it);
			}
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API ComponentAttributeList::setInt(AttrID aid, Steinberg::int64 value)
		{
			removeAttrID(aid);
			list[aid] = new ComponentAttribute(value);
			return Steinberg::kResultTrue;
		}

		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API ComponentAttributeList::getInt(AttrID aid, Steinberg::int64& value)
		{
			mapIterator it = list.find(aid);
			if (it != list.end() && it->second)
			{
				value = it->second->intValue();
				return Steinberg::kResultTrue;
			}
			return Steinberg::kResultFalse;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API ComponentAttributeList::setFloat(AttrID aid, double value)
		{
			removeAttrID(aid);
			list[aid] = new ComponentAttribute(value);
			return Steinberg::kResultTrue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API ComponentAttributeList::getFloat(AttrID aid, double& value)
		{
			mapIterator it = list.find(aid);
			if (it != list.end() && it->second)
			{
				value = it->second->floatValue();
				return Steinberg::kResultTrue;
			}
			return Steinberg::kResultFalse;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API ComponentAttributeList::setString(AttrID aid, const Steinberg::Vst::TChar* string)
		{
			removeAttrID(aid);
			list[aid] = new ComponentAttribute(string, Steinberg::String(const_cast<Steinberg::Vst::TChar*> (string)).length());
			return Steinberg::kResultTrue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API ComponentAttributeList::getString(AttrID aid, Steinberg::Vst::TChar* string, Steinberg::uint32 size)
		{
			mapIterator it = list.find(aid);
			if (it != list.end() && it->second)
			{
				Steinberg::uint32 stringSize = 0;
				const Steinberg::Vst::TChar* _string = it->second->stringValue(stringSize);
				memcpy(string, _string, std::min<Steinberg::uint32>(stringSize, size) * sizeof(Steinberg::Vst::TChar));
				return Steinberg::kResultTrue;
			}
			return Steinberg::kResultFalse;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API ComponentAttributeList::setBinary(AttrID aid, const void* data, Steinberg::uint32 size)
		{
			removeAttrID(aid);
			list[aid] = new ComponentAttribute(data, size);
			return Steinberg::kResultTrue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API ComponentAttributeList::getBinary(AttrID aid, const void*& data, Steinberg::uint32& size)
		{
			mapIterator it = list.find(aid);
			if (it != list.end() && it->second)
			{
				data = it->second->binaryValue(size);
				return Steinberg::kResultTrue;
			}
			size = 0;
			return Steinberg::kResultFalse;
		}
	}
}