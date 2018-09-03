#pragma once

namespace Carlsound
{
	namespace Vst
	{
		class ComponentAttribute
		{
		public:
			enum Type
			{
				kInteger,
				kFloat,
				kString,
				kBinary
			};

			ComponentAttribute(int64 value) : size(0), type(kInteger) { v.intValue = value; }
			ComponentAttribute(double value) : size(0), type(kFloat) { v.floatValue = value; }
			ComponentAttribute(const TChar* value, uint32 size) : size(size), type(kString)
			{
				v.stringValue = new TChar[size];
				memcpy(v.stringValue, value, size * sizeof(TChar));
			}
			ComponentAttribute(const void* value, uint32 size) : size(size), type(kBinary)
			{
				v.binaryValue = new char[size];
				memcpy(v.binaryValue, value, size);
			}
			~ComponentAttribute()
			{
				if (size)
					delete[] v.binaryValue;
			}

			int64 intValue() const { return v.intValue; }
			double floatValue() const { return v.floatValue; }
			const TChar* stringValue(uint32& stringSize)
			{
				stringSize = size;
				return v.stringValue;
			}
			const void* binaryValue(uint32& binarySize)
			{
				binarySize = size;
				return v.binaryValue;
			}

			Type getType() const { return type; }

		protected:
			union v
			{
				int64 intValue;
				double floatValue;
				TChar* stringValue;
				char* binaryValue;
			} v;
			uint32 size;
			Type type;
		};

		typedef std::map<String, ComponentAttribute*>::iterator mapIterator;
}