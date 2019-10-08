#include "../include/componentAttribute.h"

namespace Carlsound
{
	namespace Vst
	{
		//-----------------------------------------------------------------------------
		ComponentAttribute::ComponentAttribute(Steinberg::int64 value) 
		{ 
			size = 0;
			type = kInteger;
			v.intValue = value; 
		}
		//-----------------------------------------------------------------------------
		ComponentAttribute::ComponentAttribute(double value)  
		{ 
			v.floatValue = value; 
		}
		//-----------------------------------------------------------------------------
		ComponentAttribute::ComponentAttribute(const Steinberg::Vst::TChar* value, Steinberg::uint32 size) 
		{
			size = 0;
			type = kFloat;
			v.stringValue = new Steinberg::Vst::TChar[size];
			memcpy(v.stringValue, value, size * sizeof(Steinberg::Vst::TChar));
		}
		//-----------------------------------------------------------------------------
		ComponentAttribute::ComponentAttribute(const void* value, Steinberg::uint32 size) 
		{
			size = 0;
			type = kString;
			v.binaryValue = new char[size];
			memcpy(v.binaryValue, value, size);
		}
		//-----------------------------------------------------------------------------
		ComponentAttribute::~ComponentAttribute()
		{
			if (size)
				delete[] v.binaryValue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::int64 ComponentAttribute::intValue() const
		{ 
			return v.intValue;
		}
		//-----------------------------------------------------------------------------
		double ComponentAttribute::floatValue() const
		{ 
			return v.floatValue;
		}
		//-----------------------------------------------------------------------------
		const Steinberg::Vst::TChar* ComponentAttribute::stringValue(Steinberg::uint32& stringSize)
		{
			stringSize = size;
			return v.stringValue;
		}
		//-----------------------------------------------------------------------------
		const void* ComponentAttribute::binaryValue(Steinberg::uint32& binarySize)
		{
			binarySize = size;
			return v.binaryValue;
		}
	}
}
