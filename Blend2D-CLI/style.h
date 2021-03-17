#pragma once

#include "api.h"
#include "object.h"
#include "rgba.h"
#include "gradient.h"
#include "pattern.h"

using namespace System;
using namespace System::Diagnostics;

#define GradientStop(source) (::BLGradientStop*)(source)

namespace Blend2D
{
	//! Style type.
	public enum class BLStyleType : UInt32
	{
		//! No style, nothing will be paint.
		None = BL_STYLE_TYPE_NONE,
		//! Solid color style.
		Solid = BL_STYLE_TYPE_SOLID,
		//! Pattern style.
		Pattern = BL_STYLE_TYPE_PATTERN,
		//! Gradient style.
		Gradient = BL_STYLE_TYPE_GRADIENT,
	};

	public ref class BLStyle : public BLObject
	{
	private:

		typedef ::BLStyle ImplType;

	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLObjectPointer<ImplType> impl;

	public:

		BLStyle()
			: BLObject()
		{
		}

		BLStyle(BLRgba32 rgba32)
			: BLObject()
		{
			CheckResult(blStyleAssignRgba32(this, rgba32.value));
		}

		BLStyle(BLRgba64 rgba64)
			: BLObject()
		{
			CheckResult(blStyleAssignRgba64(this, rgba64.value));
		}

		BLStyle(BLGradient^ gradient)
			: BLObject()
		{
			CheckResult(blStyleAssignObject(this, gradient));
		}

		BLStyle(BLPattern^ pattern)
			: BLObject()
		{
			CheckResult(blStyleAssignObject(this, pattern));
		}

	internal:

		operator ImplType* ()
		{
			if (Object::ReferenceEquals(this, nullptr))
			{
				return nullptr;
			}

			return impl;
		}

	public:

		static operator BLStyle ^ (BLRgba32 rgba32)
		{
			return gcnew BLStyle(rgba32);
		}

		static operator BLStyle ^ (BLRgba64 rgba64)
		{
			return gcnew BLStyle(rgba64);
		}

		static operator BLStyle ^ (BLGradient^ gradient)
		{
			return gcnew BLStyle(gradient);
		}

		static operator BLStyle ^ (BLPattern^ pattern)
		{
			return gcnew BLStyle(pattern);
		}

	public:

		// Common Functionality

		void Reset()
		{
			CheckResult(blStyleReset(this));
		}

		void Assign(BLRgba32 rgba32)
		{
			CheckResult(blStyleAssignRgba32(this, rgba32.value));
		}

		void Assign(BLRgba64 rgba64)
		{
			CheckResult(blStyleAssignRgba64(this, rgba64.value));
		}

		void Assign(BLGradient^ gradient)
		{
			CheckResult(blStyleAssignObject(this, gradient));
		}

		void Assign(BLPattern^ pattern)
		{
			CheckResult(blStyleAssignObject(this, pattern));
		}

	public:

		property bool IsNone
		{
			bool get()
			{
				return impl->isNone();
			}
		}

		property bool isSolid
		{
			bool get()
			{
				return impl->isSolid();
			}
		}

		property bool IsObject
		{
			bool get()
			{
				return impl->isObject();
			}
		}

		property bool IsPattern
		{
			bool get()
			{
				return impl->isPattern();
			}
		}

		property bool IsGradient
		{
			bool get()
			{
				return impl->isGradient();
			}
		}

		property BLStyleType Type
		{
			BLStyleType get()
			{
				return (BLStyleType)impl->type();
			}
		}

		property BLRgba64 Rgba
		{
			BLRgba64 get()
			{
				uint64_t value = 0;

				if (Type == BLStyleType::Solid)
				{
					CheckResult(blStyleGetRgba64(this, &value));
				}

				return BLRgba64(value);
			}
		}

		property BLPattern^ Pattern
		{
			BLPattern^ get()
			{
				if (Type == BLStyleType::Pattern)
				{
					auto value = gcnew BLPattern();
					CheckResult(blStyleGetObject(this, value));
					return value;
				}

				return nullptr;
			}
		}

		property BLGradient^ Gradient
		{
			BLGradient^ get()
			{
				if (Type == BLStyleType::Gradient)
				{
					auto value = gcnew BLGradient();
					CheckResult(blStyleGetObject(this, value));
					return value;
				}

				return nullptr;
			}
		}
	};
}