#pragma once

#include "api.h"

using namespace System;
using namespace System::Diagnostics;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;

namespace Blend2D
{
	[StructLayout(LayoutKind::Explicit)]
	public value struct BLRgba32 sealed
	{
	internal:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		[FieldOffset(0)]
		uint32_t value;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		[FieldOffset(0)]
		Byte b;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		[FieldOffset(1)]
		Byte g;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		[FieldOffset(2)]
		Byte r;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		[FieldOffset(3)]
		Byte a;

	public:

		BLRgba32(uint32_t value)
			: value(value)
		{
		}

		BLRgba32(Byte r, Byte g, Byte b)
			: r(r), g(g), b(b), a(0xFFu)
		{
		}

		BLRgba32(Byte r, Byte g, Byte b, Byte a)
			: r(r), g(g), b(b), a(a)
		{
		}

		BLRgba32(Color color)
		{
			Reset(color.R, color.G, color.B, color.A);
		}

	public:

		String^ ToString() override
		{
			return String::Format("A=0x{0:X2}, R=0x{1:X2}, G=0x{2:X2}, B=0x{3:X2}", a, r, g, b);
		}

	public:

		void Reset()
		{
			value = 0u;
		}

		void Reset(Byte r, Byte g, Byte b, Byte a)
		{
			*this = BLRgba32(r, g, b, a);
		}

		void Reset(BLRgba32 rgba32)
		{
			value = rgba32.value;
		}

		void Reset(BLRgba64 rgba64)
		{
			uint32_t hi = uint32_t(rgba64.value >> 32);
			uint32_t lo = uint32_t(rgba64.value & 0xFFFFFFFFu);

			value = ((hi & 0xFF000000)) + ((lo & 0xFF000000) >> 16) + ((hi & 0x0000FF00) << 8) + ((lo & 0x0000FF00) >> 8);
		}

	public:

		property uint32_t Value
		{
			uint32_t get()
			{
				return value;
			}
			void set(uint32_t value)
			{
				value = value;
			}
		}

		property Byte A
		{
			Byte get()
			{
				return a;
			}
			void set(Byte value)
			{
				a = value;
			}
		}

		property Byte R
		{
			Byte get()
			{
				return r;
			}
			void set(Byte value)
			{
				r = value;
			}
		}

		property Byte G
		{
			Byte get()
			{
				return g;
			}
			void set(Byte value)
			{
				g = value;
			}
		}

		property Byte B
		{
			Byte get()
			{
				return b;
			}
			void set(Byte value)
			{
				b = value;
			}
		}
	};

	[StructLayout(LayoutKind::Explicit)]
	public value struct BLRgba64 sealed
	{
	internal:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		[FieldOffset(0)]
		uint64_t value;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		[FieldOffset(0)]
		UInt16 b;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		[FieldOffset(2)]
		UInt16 g;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		[FieldOffset(4)]
		UInt16 r;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		[FieldOffset(6)]
		UInt16 a;

	public:

		BLRgba64(uint64_t value)
			: value(value)
		{
		}

		BLRgba64(UInt16 r, UInt16 g, UInt16 b)
			: r(r), g(g), b(b), a(0xFFFFu)
		{
		}

		BLRgba64(UInt16 r, UInt16 g, UInt16 b, UInt16 a)
			: r(r), g(g), b(b), a(a)
		{
		}

	public:

		String^ ToString() override
		{
			return String::Format("A=0x{0:X4}, R=0x{1:X4}, G=0x{2:X4}, B=0x{3:X4}", a, r, g, b);
		}

	public:

		void Reset()
		{
			value = 0u;
		}

		void Reset(UInt16 r, UInt16 g, UInt16 b, UInt16 a)
		{
			*this = BLRgba64(r, g, b, a);
		}

		void Reset(BLRgba32 rgba32)
		{
			Reset(rgba32.r | (uint32_t(rgba32.r) << 8u), rgba32.g | (uint32_t(rgba32.g) << 8u), rgba32.b | (uint32_t(rgba32.b) << 8u), rgba32.a | (uint32_t(rgba32.a) << 8u));
		}

		void Reset(BLRgba64 rgba64)
		{
			value = rgba64.value;
		}

	public:

		property uint64_t Value
		{
			uint64_t get()
			{
				return value;
			}
			void set(uint64_t value)
			{
				value = value;
			}
		}

		property UInt16 A
		{
			UInt16 get()
			{
				return a;
			}
			void set(UInt16 value)
			{
				a = value;
			}
		}

		property UInt16 R
		{
			UInt16 get()
			{
				return r;
			}
			void set(UInt16 value)
			{
				r = value;
			}
		}

		property UInt16 G
		{
			UInt16 get()
			{
				return g;
			}
			void set(UInt16 value)
			{
				g = value;
			}
		}

		property UInt16 B
		{
			UInt16 get()
			{
				return b;
			}
			void set(UInt16 value)
			{
				b = value;
			}
		}
	};
}