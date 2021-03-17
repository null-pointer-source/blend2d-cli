#pragma once

#include "api.h"
#include "object.h"

using namespace System;
using namespace System::Diagnostics;

#define TextMetrics(source) (::BLTextMetrics*)(source)
#define GlyphRun(source) (::BLGlyphRun*)(source)

namespace Blend2D
{
	//! Placement of glyphs stored in a `BLGlyphRun`.
	public enum class BLGlyphPlacementType : UInt32
	{
		//! No placement (custom handling by `BLPathSinkFunc`).
		None = BL_GLYPH_PLACEMENT_TYPE_NONE,
		//! Each glyph has a BLGlyphPlacement (advance + offset).
		AdvanceOffset = BL_GLYPH_PLACEMENT_TYPE_ADVANCE_OFFSET,
		//! Each glyph has a BLPoint offset in design-space units.
		DesignUnits = BL_GLYPH_PLACEMENT_TYPE_DESIGN_UNITS,
		//! Each glyph has a BLPoint offset in user-space units.
		UserUnits = BL_GLYPH_PLACEMENT_TYPE_USER_UNITS,
		//! Each glyph has a BLPoint offset in absolute units.
		AbsoluteUnits = BL_GLYPH_PLACEMENT_TYPE_ABSOLUTE_UNITS
	};

	public value struct BLGlyphMetrics sealed
	{
	internal:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint32_t glyphId;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint32_t cluster;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double advance;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double leadingBearing;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double trailingBearing;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLBox boundingBox;
	};

	public value struct BLGlyphPlacement sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLPointI placement;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLPointI advance;

	public:

		property BLPointI Placement
		{
			BLPointI get()
			{
				return placement;
			}
		}

		property BLPointI Advance
		{
			BLPointI get()
			{
				return advance;
			}
		}
	};

	public value struct BLGlyphRun sealed
	{
	internal:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		void* glyphData;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		void* placementData;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		size_t size;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint8_t glyphSize;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint8_t placementType;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int8_t glyphAdvance;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int8_t placementAdvance;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint32_t flags;

	internal:

		BLGlyphRun(const ::BLGlyphRun& other)
		{
			glyphData = other.glyphData;
			placementData = other.placementData;
			size = other.size;
			glyphSize = other.glyphSize;
			placementType = other.placementType;
			glyphAdvance = other.glyphAdvance;
			placementAdvance = other.placementAdvance;
			flags = other.flags;
		}

	public:

		property size_t Size
		{
			size_t get()
			{
				return size;
			}
		}

		property BLGlyphPlacementType PlacementType
		{
			BLGlyphPlacementType get()
			{
				return (BLGlyphPlacementType)placementType;
			}
		}
	};

	public ref class BLGlyphBuffer sealed : public BLObject
	{
	private:

		typedef ::BLGlyphBuffer ImplType;

	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLObjectPointer<ImplType> impl;

	public:

		BLGlyphBuffer()
			: BLObject()
		{
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

		void SetText(String^ text)
		{
			ConvertWchar(str, text);

			CheckResult(blGlyphBufferSetText(this, str, text->Length, (uint32_t)BLTextEncoding::UTF16));
		}

		void SetGlyphRun(BLGlyphRun% glyphRun, BLGlyphPlacementType placementType, size_t index, size_t size)
		{
			if (index + size > impl->size())
			{
				throw gcnew IndexOutOfRangeException();
			}

			const auto content = impl->content();
			const auto placementData = impl->placementData();

			glyphRun.glyphSize = 4;
			glyphRun.placementType = (uint8_t)placementType;
			glyphRun.glyphAdvance = 4;
			glyphRun.placementAdvance = int8_t(sizeof(BLGlyphPlacement));
			glyphRun.flags = 0;
			glyphRun.glyphData = (void*)(content + index);
			glyphRun.placementData = (void*)(placementData + index);
			glyphRun.size = size;
		}

	public:

		property size_t Size
		{
			size_t get()
			{
				return impl->size();
			}
		}

		property BLGlyphRun GlyphRun
		{
			BLGlyphRun get()
			{
				return  BLGlyphRun(impl->glyphRun());
			}
		}

		property array<uint32_t>^ Content
		{
			array<uint32_t>^ get()
			{
				return  ConvertToArray<uint32_t>(impl->content(), impl->size());
			}
		}

		property array<BLGlyphPlacement>^ PlacementData
		{
			array<BLGlyphPlacement>^ get()
			{
				return ConvertToArray<BLGlyphPlacement>(impl->placementData(), impl->size());
			}
		}
	};

	public value struct BLFontMetrics sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float size;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float ascent;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float vAscent;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float descent;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float vDescent;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float lineGap;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float xHeight;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float capHeight;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float xMin;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float yMin;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float xMax;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float yMax;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float underlinePosition;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float underlineThickness;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float strikethroughPosition;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		float strikethroughThickness;

	internal:

		BLFontMetrics(const ::BLFontMetrics& metrics)
		{
			size = metrics.size;
			ascent = metrics.ascent;
			vAscent = metrics.vAscent;
			descent = metrics.descent;
			vDescent = metrics.vDescent;
			lineGap = metrics.lineGap;
			xHeight = metrics.xHeight;
			capHeight = metrics.capHeight;
			xMin = metrics.xMin;
			yMin = metrics.yMin;
			xMax = metrics.xMax;
			yMax = metrics.yMax;
			underlinePosition = metrics.underlinePosition;
			underlineThickness = metrics.underlineThickness;
			strikethroughPosition = metrics.strikethroughPosition;
			strikethroughThickness = metrics.strikethroughThickness;
		}

	public:

		property float Size
		{
			float get()
			{
				return size;
			}
		}

		property float Ascent
		{
			float get()
			{
				return ascent;
			}
		}

		property float VAscent
		{
			float get()
			{
				return vAscent;
			}
		}

		property float Descent
		{
			float get()
			{
				return descent;
			}
		}

		property float VDescent
		{
			float get()
			{
				return vDescent;
			}
		}

		property float LineGap
		{
			float get()
			{
				return lineGap;
			}
		}

		property float XHeight
		{
			float get()
			{
				return xHeight;
			}
		}

		property float CapHeight
		{
			float get()
			{
				return capHeight;
			}
		}

		property float XMin
		{
			float get()
			{
				return xMin;
			}
		}

		property float YMin
		{
			float get()
			{
				return yMin;
			}
		}

		property float XMax
		{
			float get()
			{
				return xMax;
			}
		}

		property float YMax
		{
			float get()
			{
				return yMax;
			}
		}

		property float UnderlinePosition
		{
			float get()
			{
				return underlinePosition;
			}
		}

		property float UnderlineThickness
		{
			float get()
			{
				return underlineThickness;
			}
		}

		property float StrikethroughPosition
		{
			float get()
			{
				return strikethroughPosition;
			}
		}

		property float StrikethroughThickness
		{
			float get()
			{
				return strikethroughThickness;
			}
		}
	};

	public value struct BLTextMetrics sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLPoint advance;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLPoint leadingBearing;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLPoint trailingBearing;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLBox boundingBox;

	public:

		property BLPoint Advance
		{
			BLPoint get()
			{
				return advance;
			}
		}

		property BLPoint LeadingBearing
		{
			BLPoint get()
			{
				return leadingBearing;
			}
		}

		property BLPoint TrailingBearing
		{
			BLPoint get()
			{
				return trailingBearing;
			}
		}

		property BLBox BoundingBox
		{
			BLBox get()
			{
				return boundingBox;
			}
		}
	};

	public value struct BLFontMatrix sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double m00;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double m01;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double m10;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double m11;

	internal:

		BLFontMatrix(const ::BLFontMatrix& other)
		{
			m00 = other.m00;
			m01 = other.m01;
			m10 = other.m10;
			m11 = other.m11;
		}

	public:

		String^ ToString() override
		{
			return String::Format("M00={0:0.00}, M01={1:0.00}, M10={2:0.00}, M11={3:0.00}", m00, m01, m10, m11);
		}

	public:

		property double M00
		{
			double get()
			{
				return m00;
			}
		}

		property double M01
		{
			double get()
			{
				return m01;
			}
		}

		property double M10
		{
			double get()
			{
				return m10;
			}
		}

		property double M11
		{
			double get()
			{
				return m11;
			}
		}
	};

	public ref class BLFontFace sealed : public BLObject
	{
	private:

		typedef ::BLFontFace ImplType;

	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLObjectPointer<ImplType> impl;

	public:

		BLFontFace()
			: BLObject()
		{
		}

		BLFontFace(String^ fileName)
			: BLObject()
		{
			CreateFromFile(fileName);
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

		void CreateFromFile(String^ fileName)
		{
			ConvertChar(str, fileName);

			CheckResult(blFontFaceCreateFromFile(this, str, 0));
		}

	public:

		property String^ FullName
		{
			String^ get()
			{
				return gcnew String(impl->fullName());
			}
		}

		property String^ FamilyName
		{
			String^ get()
			{
				return gcnew String(impl->familyName());
			}
		}

		property String^ SubFamilyName
		{
			String^ get()
			{
				return gcnew String(impl->subfamilyName());
			}
		}

		property String^ PostScriptName
		{
			String^ get()
			{
				return gcnew String(impl->postScriptName());
			}
		}
	};

	public ref class BLFont sealed : public BLObject
	{
	private:

		typedef ::BLFont ImplType;

	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLObjectPointer<ImplType> impl;

	public:

		BLFont()
			: BLObject()
		{
		}

		BLFont(BLFontFace^ face, float size)
			: BLObject()
		{
			CreateFromFace(face, size);
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

		void CreateFromFace(BLFontFace^ face, float size)
		{
			CheckResult(blFontCreateFromFace(this, face, size));
		}

		void Shape(BLGlyphBuffer^ glyphBuffer)
		{
			CheckResult(blFontShape(this, glyphBuffer));
		}

		void ApplyKerning(BLGlyphBuffer^ glyphBuffer)
		{
			CheckResult(blFontApplyKerning(this, glyphBuffer));
		}

		void GetTextMetrics(BLGlyphBuffer^ glyphBuffer, BLTextMetrics% textMetrics)
		{
			Pin(BLTextMetrics, pTextMetrics, textMetrics);

			CheckResult(blFontGetTextMetrics(this, glyphBuffer, TextMetrics(pTextMetrics)));
		}

		void GetGlyphBounds(BLGlyphBuffer^ glyphBuffer, array<uint32_t>^ glyphData, array<BLBoxI>^% glyphBounds, size_t count)
		{
			if (count > 0 && glyphData->Length > 0)
			{
				glyphBounds = gcnew array<BLBoxI>((long)count);

				Pin(uint32_t, pGlyphData, glyphData[0]);
				Pin(BLBoxI, pGlyphBounds, glyphBounds[0]);

				CheckResult(blFontGetGlyphBounds(this, pGlyphData, sizeof(uint32_t), BoxI(pGlyphBounds), count));
			}
		}

		void GetGlyphMetrics(BLGlyphBuffer^ glyphBuffer, array<BLGlyphMetrics>^% glyphMetrics)
		{
			auto mx = Matrix.M00;
			auto my = Matrix.M11;
			auto size = glyphBuffer->Size;
			auto glyphData = glyphBuffer->Content;
			auto placementData = glyphBuffer->PlacementData;

			array<BLBoxI>^ glyphBounds;

			GetGlyphBounds(glyphBuffer, glyphData, glyphBounds, size);

			glyphMetrics = gcnew array<BLGlyphMetrics>((long)size);

			Pin(BLGlyphMetrics, pGlyphMetrics, glyphMetrics[0]);

			for (long i = 0; i < (long)size; i++)
			{
				pGlyphMetrics[i].glyphId = glyphData[i];
				pGlyphMetrics[i].advance = placementData[i].Advance.X * mx;
				pGlyphMetrics[i].leadingBearing = glyphBounds[0].X0 * mx;
				pGlyphMetrics[i].trailingBearing = (placementData[i].Advance.X - glyphBounds[0].X1) * mx;
				pGlyphMetrics[i].boundingBox.X0 = glyphBounds[i].X0 * mx;
				pGlyphMetrics[i].boundingBox.X1 = glyphBounds[i].X1 * mx;
				pGlyphMetrics[i].boundingBox.Y0 = -(glyphBounds[i].Y0 * my);
				pGlyphMetrics[i].boundingBox.Y1 = -(glyphBounds[i].Y1 * my);
			}
		}

	public:

		property BLFontMetrics Metrics
		{
			BLFontMetrics get()
			{
				return BLFontMetrics(impl->metrics());
			}
		}

		property BLFontMatrix Matrix
		{
			BLFontMatrix get()
			{
				return BLFontMatrix(impl->matrix());
			}
		}
	};
}