#include "pch.h"
#include "api.h"
#include "context.h"

using namespace System;

namespace Blend2D
{
	BLResultCode CheckResult(BLResult result)
	{
		auto value = (BLResultCode)result;

		if (value != BLResultCode::BL_SUCCESS)
		{
			throw gcnew InvalidOperationException(String::Format("{0}", value));
		}

		return value;
	}

	template<typename T>
	array<T>^ ConvertToArray(const void* data, size_t count)
	{
		if (count > 0 && data != nullptr)
		{
			array<T>^ items = gcnew array<T>((long)count);
			pin_ptr<T> ptr = &items[0];
			memcpy(ptr, data, count * sizeof(T));
			return items;
		}

		return nullptr;
	}
}