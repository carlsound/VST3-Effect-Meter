#pragma once
//
#include "base/source/fstring.h"
#include "pluginterfaces/base/ftypes.h"
#include "pluginterfaces/vst/vsttypes.h"
//
#include <cstring>
#include <map>
//
namespace Carlsound
{
	namespace Vst
	{
		//-----------------------------------------------------------------------------
		class ComponentAttribute
		{
		public:
			//-----------------------------------------------------------------------------
			enum Type
			{
				kInteger,
				kFloat,
				kString,
				kBinary
			};
			//-----------------------------------------------------------------------------
			ComponentAttribute(Steinberg::int64 value);
			//-----------------------------------------------------------------------------
			ComponentAttribute(double value);
			//-----------------------------------------------------------------------------
			ComponentAttribute(const Steinberg::Vst::TChar* value, Steinberg::uint32 size);
			//-----------------------------------------------------------------------------
			ComponentAttribute(const void* value, Steinberg::uint32 size);
			//-----------------------------------------------------------------------------
			~ComponentAttribute();
			//-----------------------------------------------------------------------------
			Steinberg::int64 intValue() const;
			//-----------------------------------------------------------------------------
			double floatValue() const;
			//-----------------------------------------------------------------------------
			const Steinberg::Vst::TChar* stringValue(Steinberg::uint32& stringSize);
			//-----------------------------------------------------------------------------
			const void* binaryValue(Steinberg::uint32& binarySize);
			//-----------------------------------------------------------------------------
			Type getType() const { return type; };
			//-----------------------------------------------------------------------------
		protected:
			union v
			{
				Steinberg::int64 intValue;
				double floatValue;
				Steinberg::Vst::TChar* stringValue;
				char* binaryValue;
			} v;
			Steinberg::uint32 size;
			Type type;
		};
		//-----------------------------------------------------------------------------
		typedef std::map<Steinberg::String, ComponentAttribute*>::iterator mapIterator;
	}
}