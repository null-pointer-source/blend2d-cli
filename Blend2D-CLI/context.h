#pragma once

#include "api.h"
#include "object.h"
#include "geometry.h"
#include "matrix.h"
#include "rgba.h"
#include "gradient.h"
#include "pattern.h"
#include "style.h"
#include "image.h"
#include "path.h"
#include "font.h"
#include "control.h"

using namespace System;
using namespace System::Diagnostics;

#define ContextCreateInfo(source) (::BLContextCreateInfo*)(source)
#define ContextCookie(source) (::BLContextCookie*)(source)

namespace Blend2D
{
	//! Clip mode.
	public enum class BLClipMode : UInt32
	{
		//! Clipping to a rectangle that is aligned to the pixel grid.
		AlignedRect = BL_CLIP_MODE_ALIGNED_RECT,
		//! Clipping to a rectangle that is not aligned to pixel grid.
		UnalignedRect = BL_CLIP_MODE_UNALIGNED_RECT,
		//! Clipping to a non-rectangular area that is defined by using mask.
		Mask = BL_CLIP_MODE_MASK,
	};

	//! Composition & blending operator.
	public enum class BLCompOp : UInt32
	{
		//! Source-over [default].
		SourceOver = BL_COMP_OP_SRC_OVER,
		//! Source-copy.
		SourceCopy = BL_COMP_OP_SRC_COPY,
		//! Source-in.
		SourceIn = BL_COMP_OP_SRC_IN,
		//! Source-out.
		SourceOut = BL_COMP_OP_SRC_OUT,
		//! Source-atop.
		SourceAtop = BL_COMP_OP_SRC_ATOP,
		//! Destination-over.
		DestinationOver = BL_COMP_OP_DST_OVER,
		//! Destination-copy [nop].
		DestinationCopy = BL_COMP_OP_DST_COPY,
		//! Destination-in.
		DestinationIn = BL_COMP_OP_DST_IN,
		//! Destination-out.
		DestinationOut = BL_COMP_OP_DST_OUT,
		//! Destination-atop.
		DestinationAtop = BL_COMP_OP_DST_ATOP,
		//! Xor.
		Xor = BL_COMP_OP_XOR,
		//! Clear.
		Clear = BL_COMP_OP_CLEAR,
		//! Plus.
		Plus = BL_COMP_OP_PLUS,
		//! Minus.
		Minus = BL_COMP_OP_MINUS,
		//! Modulate.
		Modulate = BL_COMP_OP_MODULATE,
		//! Multiply.
		MULTIPLY = BL_COMP_OP_MULTIPLY,
		//! Screen.
		Screen = BL_COMP_OP_SCREEN,
		//! Overlay.
		Overlay = BL_COMP_OP_OVERLAY,
		//! Darken.
		Darken = BL_COMP_OP_DARKEN,
		//! Lighten.
		Lighten = BL_COMP_OP_LIGHTEN,
		//! Color dodge.
		ColorDodge = BL_COMP_OP_COLOR_DODGE,
		//! Color burn.
		ColorBurn = BL_COMP_OP_COLOR_BURN,
		//! Linear burn.
		LinearBurn = BL_COMP_OP_LINEAR_BURN,
		//! Linear light.
		LinearLight = BL_COMP_OP_LINEAR_LIGHT,
		//! Pin light.
		PinLight = BL_COMP_OP_PIN_LIGHT,
		//! Hard-light.
		HardLight = BL_COMP_OP_HARD_LIGHT,
		//! Soft-light.
		SoftLight = BL_COMP_OP_SOFT_LIGHT,
		//! Difference.
		Difference = BL_COMP_OP_DIFFERENCE,
		//! Exclusion.
		Exclusion = BL_COMP_OP_EXCLUSION,
	};

	public value struct BLContextCreateInfo sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint32_t flags;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint32_t threadCount;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint32_t cpuFeatures;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint32_t commandQueueLimit;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint32_t reserved0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint32_t reserved1;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint32_t reserved2;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint32_t reserved3;

	public:

		BLContextCreateInfo(int count)
		{
			flags = 0;
			threadCount = count;
			cpuFeatures = 0;
			commandQueueLimit = 0;
			reserved0 = 0;
			reserved1 = 0;
			reserved2 = 0;
			reserved3 = 0;
		}

	public:

		property int ThreadCount
		{
			int get()
			{
				return threadCount;
			}
			void set(int value)
			{
				threadCount = value;
			}
		}
	};

	public value struct BLContextCookie sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint64_t data0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint64_t data1;

	public:

		property uint64_t Data0
		{
			uint64_t get()
			{
				return data0;
			}
		}

		property uint64_t Data1
		{
			uint64_t get()
			{
				return data1;
			}
		}
	};

	public ref class BLContext sealed : public BLObject
	{
	private:

		typedef ::BLContext ImplType;

	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLObjectPointer<ImplType> impl;
		
		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLImage^ targetImage = nullptr;


	public:

		BLContext()
			:BLObject()
		{
		}

		BLContext(BLImage^ image)
			:BLObject()
		{
			targetImage = image;

			CheckResult(blContextInitAs(this, image, nullptr));
		}

		BLContext(BLImage^ image, BLContextCreateInfo createInfo)
			:BLObject()
		{			
			targetImage = image;
	
			Pin(BLContextCreateInfo, pCreateInfo, createInfo);

			CheckResult(blContextInitAs(this, image, ContextCreateInfo(pCreateInfo)));
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

	protected:

		void Destroy() override
		{
			targetImage = nullptr;
		}

	public:

		// Context Lifetime and Others

		void Begin(BLImage^ image)
		{
			targetImage = image;
	
			CheckResult(blContextBegin(this, image, nullptr));
		}

		void Begin(BLImage^ image, BLContextCreateInfo createInfo)
		{
			targetImage = image;

			Pin(BLContextCreateInfo, pCreateInfo, createInfo);

			CheckResult(blContextBegin(this, image, ContextCreateInfo(pCreateInfo)));
		}

		void End()
		{
			CheckResult(blContextEnd(this));

			targetImage = nullptr;
		}

	public:

		// State Management
		
		void Save()
		{
			CheckResult(blContextSave(this, nullptr));
		}

		void Save(BLContextCookie% cookie)
		{
			Pin(BLContextCookie, pCookie, cookie);

			CheckResult(blContextSave(this, ContextCookie(pCookie)));
		}	
		
		void Restore()
		{
			CheckResult(blContextRestore(this, nullptr));
		}

		void Restore(BLContextCookie cookie)
		{
			Pin(BLContextCookie, pCookie, cookie);

			CheckResult(blContextRestore(this, ContextCookie(pCookie)));
		}

	public:

		// Clip Operations

		void RestoreClipping()
		{
			CheckResult(blContextRestoreClipping(this));
		}

		void ClipToRect(BLRectI rect)
		{
			Pin(BLRectI, pRect, rect);

			CheckResult(blContextClipToRectI(this, RectI(pRect)));
		}

		void ClipToRect(BLRect rect)
		{
			Pin(BLRect, pRect, rect);

			CheckResult(blContextClipToRectD(this, Rect(pRect)));
		}

		void ClipToRect(double x, double y, double w, double h)
		{
			ClipToRect(BLRect(x, y, w, h));
		}

	public:

		// Clear Operations

		void ClearAll()
		{
			CheckResult(blContextClearAll(this));
		}

		void ClearRect(BLRectI rect)
		{
			Pin(BLRectI, pRect, rect);

			CheckResult(blContextClearRectI(this, RectI(pRect)));
		}

		void ClearRect(BLRect rect)
		{
			Pin(BLRect, pRect, rect);

			CheckResult(blContextClearRectD(this, Rect(pRect)));
		}

		void ClearRect(double x, double y, double w, double h)
		{
			ClipToRect(BLRect(x, y, w, h));
		}

	public:

		// Fill Style & Options

		void SetFillStyle(BLRgba32 rgba32)
		{
			CheckResult(blContextSetFillStyleRgba32(this, rgba32.value));
		}

		void SetFillStyle(BLRgba64 rgba64)
		{
			CheckResult(blContextSetFillStyleRgba64(this, rgba64.value));
		}

		void SetFillStyle(BLGradient^ gradient)
		{
			CheckResult(blContextSetFillStyleObject(this, gradient));
		}

		void SetFillStyle(BLPattern^ pattern)
		{
			CheckResult(blContextSetFillStyleObject(this, pattern));
		}

		void SetFillStyle(BLStyle^ style)
		{
			CheckResult(blContextSetFillStyle(this, style));
		}

	public:

		// Stroke Style & Options

		void SetStrokeStyle(BLRgba32 rgba32)
		{
			CheckResult(blContextSetStrokeStyleRgba32(this, rgba32.Value));
		}

		void SetStrokeStyle(BLRgba64 rgba64)
		{
			CheckResult(blContextSetStrokeStyleRgba64(this, rgba64.Value));
		}

		void SetStrokeStyle(BLGradient^ gradient)
		{
			CheckResult(blContextSetStrokeStyleObject(this, gradient));
		}

		void SetStrokeStyle(BLPattern^ pattern)
		{
			CheckResult(blContextSetStrokeStyleObject(this, pattern));
		}

		void SetStrokeStyle(BLStyle^ style)
		{
			CheckResult(blContextSetStrokeStyle(this, style));
		}

	public:

		// Fill Operations

		void FillAll()
		{
			CheckResult(blContextFillAll(this));
		}

		void FillBox(BLBoxI box)
		{
			Pin(BLBoxI, pBox, box);

			FillGeometry(BLGeometryType::BoxI, pBox);
		}

		void FillBox(BLBox box)
		{
			Pin(BLBox, pBox, box);

			FillGeometry(BLGeometryType::Box, pBox);
		}

		void FillBox(double x0, double y0, double x1, double y1)
		{
			FillBox(BLBox(x0, y0, x1, y1));
		}

		void FillRect(BLRectI rect)
		{
			Pin(BLRectI, pRect, rect);

			CheckResult(blContextFillRectI(this, RectI(pRect)));
		}

		void FillRect(BLRect rect)
		{
			Pin(BLRect, pRect, rect);

			CheckResult(blContextFillRectD(this, Rect(pRect)));
		}

		void FillRect(double x, double y, double w, double h)
		{
			FillRect(BLRect(x, y, w, h));
		}

		void FillCircle(BLCircle circle)
		{
			Pin(BLCircle, pCircle, circle);

			FillGeometry(BLGeometryType::Circle, pCircle);
		}

		void FillCircle(double cx, double cy, double r)
		{
			FillCircle(BLCircle(cx, cy, r));
		}

		void FillEllipse(BLEllipse ellipse)
		{
			Pin(BLEllipse, pEllipse, ellipse);

			FillGeometry(BLGeometryType::Ellipse, pEllipse);
		}

		void FillEllipse(double cx, double cy, double rx, double ry)
		{
			FillEllipse(BLEllipse(cx, cy, rx, ry));
		}

		void FillRoundRect(BLRoundRect roundRect)
		{
			Pin(BLRoundRect, pRoundRect, roundRect);

			FillGeometry(BLGeometryType::RoundRect, pRoundRect);
		}

		void FillRoundRect(BLRect rect, double r)
		{
			FillRoundRect(BLRoundRect(rect.X, rect.Y, rect.Width, rect.Height, r));
		}

		void FillRoundRect(BLRect rect, double rx, double ry)
		{
			FillRoundRect(BLRoundRect(rect.X, rect.Y, rect.Width, rect.Height, rx, ry));
		}

		void FillRoundRect(double x, double y, double w, double h, double r)
		{
			FillRoundRect(BLRoundRect(x, y, w, h, r));
		}

		void FillRoundRect(double x, double y, double w, double h, double rx, double ry)
		{
			FillRoundRect(BLRoundRect(x, y, w, h, rx, ry));
		}

		void FillChord(BLArc chord)
		{
			Pin(BLArc, pChord, chord);

			FillGeometry(BLGeometryType::Chord, pChord);
		}

		void FillChord(double cx, double cy, double r, double start, double sweep)
		{
			FillChord(BLArc(cx, cy, r, r, start, sweep));
		}

		void FillChord(double cx, double cy, double rx, double ry, double start, double sweep)
		{
			FillChord(BLArc(cx, cy, rx, ry, start, sweep));
		}

		void FillPie(BLArc pie)
		{
			Pin(BLArc, pPie, pie);

			FillGeometry(BLGeometryType::Pie, pPie);
		}

		void FillPie(double cx, double cy, double r, double start, double sweep)
		{
			FillPie(BLArc(cx, cy, r, r, start, sweep));
		}

		void FillPie(double cx, double cy, double rx, double ry, double start, double sweep)
		{
			FillPie(BLArc(cx, cy, rx, ry, start, sweep));
		}

		void FillTriangle(BLTriangle triangle)
		{
			Pin(BLTriangle, pTriangle, triangle);

			FillGeometry(BLGeometryType::Triangle, pTriangle);
		}

		void FillTriangle(double x0, double y0, double x1, double y1, double x2, double y2)
		{
			FillTriangle(BLTriangle(x0, y0, x1, y1, x2, y2));
		}

		void FillPolygon(array<BLPointI>^ poly)
		{
			if (poly->Length > 0)
			{
				Pin(BLPointI, pPoly, poly[0]);

				FillGeometry(BLGeometryType::PolygonI, pPoly);
			}
		}

		void FillPolygon(array<BLPoint>^ poly)
		{
			if (poly->Length > 0)
			{
				Pin(BLPoint, pPoly, poly[0]);

				FillGeometry(BLGeometryType::Polygon, pPoly);
			}
		}

		void FillBoxArray(array<BLBoxI>^ array)
		{
			if (array->Length > 0)
			{
				Pin(BLBoxI, pArray, array[0]);

				FillGeometry(BLGeometryType::BoxIArray, pArray);
			}
		}

		void FillBoxArray(array<BLBox>^ array)
		{
			if (array->Length > 0)
			{
				Pin(BLBox, pArray, array[0]);

				FillGeometry(BLGeometryType::BoxArray, pArray);
			}
		}

		void FillRectArray(array<BLRectI>^ array)
		{
			if (array->Length > 0)
			{
				Pin(BLRectI, pArray, array[0]);

				FillGeometry(BLGeometryType::RectIArray, pArray);
			}
		}

		void FillRectArray(array<BLRect>^ array)
		{
			if (array->Length > 0)
			{
				Pin(BLRect, pArray, array[0]);

				FillGeometry(BLGeometryType::RectArray, pArray);
			}
		}

		void FillPath(BLPath^ path)
		{
			CheckResult(blContextFillPathD(this, path));
		}

		void FillText(BLPointI dst, BLFont^ font, String^ text)
		{
			Pin(BLPointI, pDst, dst);
			ConvertWchar(str, text);

			CheckResult(blContextFillTextI(this, PointI(pDst), font, str, text->Length, (uint32_t)BLTextEncoding::UTF16));
		}

		void FillText(BLPoint dst, BLFont^ font, String^ text)
		{
			Pin(BLPoint, pDst, dst);
			ConvertWchar(str, text);

			CheckResult(blContextFillTextD(this, Point(pDst), font, str, text->Length, (uint32_t)BLTextEncoding::UTF16));
		}

		void FillGlyphRun(BLPointI dst, BLFont^ font, BLGlyphRun glyphRun)
		{
			Pin(BLPointI, pDst, dst);
			Pin(BLGlyphRun, pGlyphRun, glyphRun);

			CheckResult(blContextFillGlyphRunI(this, PointI(pDst), font, GlyphRun(pGlyphRun)));
		}

		void FillGlyphRun(BLPoint dst, BLFont^ font, BLGlyphRun glyphRun)
		{
			Pin(BLPoint, pDst, dst);
			Pin(BLGlyphRun, pGlyphRun, glyphRun);

			CheckResult(blContextFillGlyphRunD(this, Point(pDst), font, GlyphRun(pGlyphRun)));
		}

	public:

		// Stroke Operations

		void StrokeBox(BLBoxI box)
		{
			Pin(BLBoxI, pBox, box);

			StrokeGeometry(BLGeometryType::BoxI, pBox);
		}

		void StrokeBox(BLBox box)
		{
			Pin(BLBox, pBox, box);

			StrokeGeometry(BLGeometryType::Box, pBox);
		}

		void StrokeBox(double x0, double y0, double x1, double y1)
		{
			StrokeBox(BLBox(x0, y0, x1, y1));
		}

		void StrokeRect(BLRectI rect)
		{
			Pin(BLRectI, pRect, rect);

			CheckResult(blContextStrokeRectI(this, RectI(pRect)));
		}

		void StrokeRect(BLRect rect)
		{
			Pin(BLRect, pRect, rect);

			CheckResult(blContextStrokeRectD(this, Rect(pRect)));
		}

		void StrokeRect(double x, double y, double w, double h)
		{
			StrokeRect(BLRect(x, y, w, h));
		}

		void StrokeLine(BLLine line)
		{
			Pin(BLLine, pLine, line);

			StrokeGeometry(BLGeometryType::Line, pLine);
		}

		void StrokeLine(BLPoint p0, BLPoint p1)
		{
			StrokeLine(BLLine(p0.X, p0.Y, p1.X, p1.Y));
		}

		void StrokeLine(double x0, double y0, double x1, double y1)
		{
			StrokeLine(BLLine(BLLine(x0, y0, x1, y1)));
		}

		void StrokeCircle(BLCircle circle)
		{
			Pin(BLCircle, pCircle, circle);

			StrokeGeometry(BLGeometryType::Circle, pCircle);
		}

		void StrokeCircle(double cx, double cy, double r)
		{
			StrokeCircle(BLCircle(cx, cy, r));
		}

		void StrokeEllipse(BLEllipse ellipse)
		{
			Pin(BLEllipse, pEllipse, ellipse);

			StrokeGeometry(BLGeometryType::Ellipse, pEllipse);
		}

		void StrokeEllipse(double cx, double cy, double rx, double ry)
		{
			StrokeEllipse(BLEllipse(cx, cy, rx, ry));
		}

		void StrokeRoundRect(BLRoundRect roundRect)
		{
			Pin(BLRoundRect, pRoundRect, roundRect);

			StrokeGeometry(BLGeometryType::RoundRect, pRoundRect);
		}

		void StrokeRoundRect(BLRect rect, double r)
		{
			StrokeRoundRect(BLRoundRect(rect.X, rect.Y, rect.Width, rect.Height, r));
		}

		void StrokeRoundRect(BLRect rect, double rx, double ry)
		{
			StrokeRoundRect(BLRoundRect(rect.X, rect.Y, rect.Width, rect.Height, rx, ry));
		}

		void StrokeRoundRect(double x, double y, double w, double h, double r)
		{
			StrokeRoundRect(BLRoundRect(x, y, w, h, r));
		}

		void StrokeRoundRect(double x, double y, double w, double h, double rx, double ry)
		{
			StrokeRoundRect(BLRoundRect(x, y, w, h, rx, ry));
		}

		void StrokeChord(BLArc chord)
		{
			Pin(BLArc, pChord, chord);

			StrokeGeometry(BLGeometryType::Chord, pChord);
		}

		void StrokeChord(double cx, double cy, double r, double start, double sweep)
		{
			StrokeChord(BLArc(cx, cy, r, r, start, sweep));
		}

		void StrokeChord(double cx, double cy, double rx, double ry, double start, double sweep)
		{
			StrokeChord(BLArc(cx, cy, rx, ry, start, sweep));
		}

		void StrokePie(BLArc pie)
		{
			Pin(BLArc, pPie, pie);

			StrokeGeometry(BLGeometryType::Pie, pPie);
		}

		void StrokePie(double cx, double cy, double r, double start, double sweep)
		{
			StrokePie(BLArc(cx, cy, r, r, start, sweep));
		}

		void StrokePie(double cx, double cy, double rx, double ry, double start, double sweep)
		{
			StrokePie(BLArc(cx, cy, rx, ry, start, sweep));
		}

		void StrokeTriangle(BLTriangle triangle)
		{
			Pin(BLTriangle, pTriangle, triangle);

			StrokeGeometry(BLGeometryType::Triangle, pTriangle);
		}

		void StrokeTriangle(double x0, double y0, double x1, double y1, double x2, double y2)
		{
			StrokeTriangle(BLTriangle(x0, y0, x1, y1, x2, y2));
		}

		void StrokePolyline(array<BLPointI>^ poly)
		{
			if (poly->Length > 0)
			{
				Pin(BLPointI, pPoly, poly[0]);

				StrokeGeometry(BLGeometryType::PolyLineI, pPoly);
			}
		}

		void StrokePolyline(array<BLPoint>^ poly)
		{
			if (poly->Length > 0)
			{
				Pin(BLPoint, pPoly, poly[0]);

				StrokeGeometry(BLGeometryType::PolyLine, pPoly);
			}
		}

		void StrokePolygon(array<BLPointI>^ poly)
		{
			if (poly->Length > 0)
			{
				Pin(BLPointI, pPoly, poly[0]);

				StrokeGeometry(BLGeometryType::PolygonI, pPoly);
			}
		}

		void StrokePolygon(array<BLPoint>^ poly)
		{
			if (poly->Length > 0)
			{
				Pin(BLPoint, pPoly, poly[0]);

				StrokeGeometry(BLGeometryType::Polygon, pPoly);
			}
		}

		void StrokeBoxArray(array<BLBoxI>^ array)
		{
			if (array->Length > 0)
			{
				Pin(BLBoxI, pArray, array[0]);

				StrokeGeometry(BLGeometryType::BoxIArray, pArray);
			}
		}

		void StrokeBoxArray(array<BLBox>^ array)
		{
			if (array->Length > 0)
			{
				Pin(BLBox, pArray, array[0]);

				StrokeGeometry(BLGeometryType::BoxArray, pArray);
			}
		}

		void StrokeRectArray(array<BLRectI>^ array)
		{
			if (array->Length > 0)
			{
				Pin(BLRectI, pArray, array[0]);

				StrokeGeometry(BLGeometryType::RectIArray, pArray);
			}
		}

		void StrokeRectArray(array<BLRect>^ array)
		{
			if (array->Length > 0)
			{
				Pin(BLRect, pArray, array[0]);

				StrokeGeometry(BLGeometryType::RectArray, pArray);
			}
		}

		void StrokePath(BLPath^ path)
		{
			CheckResult(blContextStrokePathD(this, path));
		}

		void StrokeText(BLPointI dst, BLFont^ font, String^ text)
		{
			Pin(BLPointI, pDst, dst);
			ConvertWchar(str, text);

			CheckResult(blContextStrokeTextI(this, PointI(pDst), font, str, text->Length, (uint32_t)BLTextEncoding::UTF16));
		}

		void StrokeText(BLPoint dst, BLFont^ font, String^ text)
		{
			Pin(BLPoint, pDst, dst);
			ConvertWchar(str, text);

			CheckResult(blContextStrokeTextD(this, Point(pDst), font, str, text->Length, (uint32_t)BLTextEncoding::UTF16));
		}

		void StrokeGlyphRun(BLPointI dst, BLFont^ font, BLGlyphRun glyphRun)
		{
			Pin(BLPointI, pDst, dst);
			Pin(BLGlyphRun, pGlyphRun, glyphRun);

			CheckResult(blContextStrokeGlyphRunI(this, PointI(pDst), font, GlyphRun(pGlyphRun)));
		}

		void StrokeGlyphRun(BLPoint dst, BLFont^ font, BLGlyphRun glyphRun)
		{
			Pin(BLPoint, pDst, dst);
			Pin(BLGlyphRun, pGlyphRun, glyphRun);

			CheckResult(blContextStrokeGlyphRunD(this, Point(pDst), font, GlyphRun(pGlyphRun)));
		}

	public:

		void BlitImage(BLPointI dst, BLImage^ image)
		{
			Pin(BLPointI, pDst, dst);

			CheckResult(blContextBlitImageI(this, PointI(pDst), image, nullptr));
		}

		void BlitImage(BLPointI dst, BLImage^ image, BLRectI area)
		{
			Pin(BLPointI, pDst, dst);
			Pin(BLRectI, pArea, area);

			CheckResult(blContextBlitImageI(this, PointI(pDst), image, RectI(pArea)));
		}

		void BlitImage(BLPoint dst, BLImage^ image)
		{
			Pin(BLPoint, pDst, dst);

			CheckResult(blContextBlitImageD(this, Point(pDst), image, nullptr));
		}

		void BlitImage(BLPoint dst, BLImage^ image, BLRectI area)
		{
			Pin(BLPoint, pDst, dst);
			Pin(BLRectI, pArea, area);

			CheckResult(blContextBlitImageD(this, Point(pDst), image, RectI(pArea)));
		}

		void BlitImage(BLRectI dst, BLImage^ image)
		{
			Pin(BLRectI, pDst, dst);

			CheckResult(blContextBlitScaledImageI(this, RectI(pDst), image, nullptr));
		}

		void BlitImage(BLRectI dst, BLImage^ image, BLRectI area)
		{
			Pin(BLRectI, pDst, dst);
			Pin(BLRectI, pArea, area);

			CheckResult(blContextBlitScaledImageI(this, RectI(pDst), image, RectI(pArea)));
		}

		void BlitImage(BLRect dst, BLImage^ image)
		{
			Pin(BLRect, pDst, dst);

			CheckResult(blContextBlitScaledImageD(this, Rect(pDst), image, nullptr));
		}

		void BlitImage(BLRect dst, BLImage^ image, BLRectI area)
		{
			Pin(BLRect, pDst, dst);
			Pin(BLRectI, pArea, area);

			CheckResult(blContextBlitScaledImageD(this, Rect(pDst), image, RectI(pArea)));
		}
	public:

		// Transformations

			
		void UserToMeta()
		{
			impl->userToMeta();
		}

		void ResetMatrix()
		{
			ApplyMatrixOp(BLMatrix2DOp::Reset, nullptr);
		}

		void Translate(double x, double y)
		{
			ApplyMatrixOpV(BLMatrix2DOp::Translate, x, y);
		}

		void Translate(BLPointI p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::Translate, p.X, p.Y);
		}

		void Translate(BLPoint p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::Translate, p.X, p.Y);
		}

		void Scale(double xy)
		{
			ApplyMatrixOpV(BLMatrix2DOp::Scale, xy, xy);
		}

		void Scale(double x, double y)
		{
			ApplyMatrixOpV(BLMatrix2DOp::Scale, x, y);
		}

		void Scale(BLPointI p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::Scale, p.X, p.Y);
		}

		void Scale(BLPoint p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::Scale, p.X, p.Y);
		}

		void Skew(double x, double y)
		{
			ApplyMatrixOpV(BLMatrix2DOp::Skew, x, y);
		}

		void Skew(BLPoint p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::Skew, p.X, p.Y);
		}

		void Rotate(double angle)
		{
			ApplyMatrixOp(BLMatrix2DOp::Rotate, &angle);
		}

		void Rotate(double angle, double x, double y)
		{
			ApplyMatrixOpV(BLMatrix2DOp::RotatePoint, angle, x, y);
		}

		void Rotate(double angle, BLPoint p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::RotatePoint, angle, p.X, p.Y);
		}

		void Rotate(double angle, BLPointI p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::RotatePoint, angle, p.X, p.Y);
		}

		void Transform(BLMatrix2D m)
		{
			Pin(BLMatrix2D, pM, m);

			ApplyMatrixOp(BLMatrix2DOp::Transform, pM);
		}

		void PostTranslate(double x, double y)
		{
			ApplyMatrixOpV(BLMatrix2DOp::PostTranslate, x, y);
		}

		void PostTranslate(BLPointI p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::PostTranslate, p.X, p.Y);
		}

		void PostTranslate(BLPoint p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::PostTranslate, p.X, p.Y);
		}

		void PostScale(double xy)
		{
			ApplyMatrixOpV(BLMatrix2DOp::PostScale, xy, xy);
		}

		void PostScale(double x, double y)
		{
			ApplyMatrixOpV(BLMatrix2DOp::PostScale, x, y);
		}

		void PostScale(BLPointI p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::PostScale, p.X, p.Y);
		}

		void PostScale(BLPoint p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::PostScale, p.X, p.Y);
		}

		void PostSkew(double x, double y)
		{
			ApplyMatrixOpV(BLMatrix2DOp::PostSkew, x, y);
		}

		void PostSkew(BLPoint p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::PostSkew, p.X, p.Y);
		}

		void PostRotate(double angle)
		{
			ApplyMatrixOp(BLMatrix2DOp::PostRotate, &angle);
		}

		void PostRotate(double angle, double x, double y)
		{
			ApplyMatrixOpV(BLMatrix2DOp::PostRotatePoint, angle, x, y);
		}

		void PostRotate(double angle, BLPoint p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::PostRotatePoint, angle, p.X, p.Y);
		}

		void PostRotate(double angle, BLPointI p)
		{
			ApplyMatrixOpV(BLMatrix2DOp::PostRotatePoint, angle, p.X, p.Y);
		}

		void PostTransform(BLMatrix2D m)
		{
			Pin(BLMatrix2D, pM, m);

			ApplyMatrixOp(BLMatrix2DOp::PostTransform, pM);
		}

	private:

		void FillGeometry(BLGeometryType geometryType, const void* geometryData)
		{
			CheckResult(blContextFillGeometry(this, (uint32_t)geometryType, geometryData));
		}

		void StrokeGeometry(BLGeometryType geometryType, const void* geometryData)
		{
			CheckResult(blContextStrokeGeometry(this, (uint32_t)geometryType, geometryData));
		}

		void ApplyMatrixOp(BLMatrix2DOp opType, const void* opData)
		{
			CheckResult(blContextMatrixOp(this, (uint32_t)opType, opData));
		}

		void ApplyMatrixOpV(BLMatrix2DOp opType, double v1, double v2)
		{
			double opData[] = { v1, v2 };

			CheckResult(blContextMatrixOp(this, (uint32_t)opType, opData));
		}

		void ApplyMatrixOpV(BLMatrix2DOp opType, double v1, double v2, double v3)
		{
			double opData[] = { v1, v2, v3 };

			CheckResult(blContextMatrixOp(this, (uint32_t)opType, opData));
		}

	public:

		property BLImage^ TargetImage
		{
			BLImage^ get()
			{
				return targetImage;
			}
		}

		property size_t SavedStateCount
		{
			size_t get()
			{
				return impl->savedStateCount();
			}
		}

		property BLCompOp CompOp
		{
			BLCompOp get()
			{
				return (BLCompOp)impl->compOp();
			}
			void set(BLCompOp value)
			{
				CheckResult(impl->setCompOp((uint32_t)value));
			}
		}

		property BLApproximationOptions ApproximationOptions
		{
			BLApproximationOptions get()
			{
				return BLApproximationOptions(impl->approximationOptions());
			}
		}

		property BLFlattenMode FlattenMode
		{
			BLFlattenMode get()
			{
				return  (BLFlattenMode)impl->flattenMode();
			}
			void set(BLFlattenMode value)
			{
				CheckResult(impl->setFlattenMode((uint32_t)value));
			}
		}

		property double FlattenTolerance
		{
			double get()
			{
				return impl->flattenTolerance();
			}
			void set(double value)
			{
				CheckResult(impl->setFlattenTolerance(value));
			}
		}

		property double GlobalAlpha
		{
			double get()
			{
				return impl->globalAlpha();
			}
			void set(double value)
			{
				CheckResult(impl->setGlobalAlpha(value));
			}
		}

		property double FillAlpha
		{
			double get()
			{
				return impl->fillAlpha();
			}
			void set(double value)
			{
				CheckResult(impl->setFillAlpha(value));
			}
		}

		property double StrokeAlpha
		{
			double get()
			{
				return impl->strokeAlpha();
			}
			void set(double value)
			{
				CheckResult(impl->setStrokeAlpha(value));
			}
		}

		property double StrokeWidth
		{
			double get()
			{
				return impl->strokeWidth();
			}
			void set(double value)
			{
				CheckResult(impl->setStrokeWidth(value));
			}
		}

		property double StrokeMiterLimit
		{
			double get()
			{
				return impl->strokeMiterLimit();
			}
			void set(double value)
			{
				CheckResult(impl->setStrokeMiterLimit(value));
			}
		}

		property double StrokeDashOffset
		{
			double get()
			{
				return impl->strokeDashOffset();
			}
			void set(double value)
			{
				CheckResult(impl->setStrokeDashOffset(value));
			}
		}

		property BLStrokeJoin StrokeJoin
		{
			BLStrokeJoin get()
			{
				return (BLStrokeJoin)impl->strokeJoin();
			}
			void set(BLStrokeJoin value)
			{
				CheckResult(impl->setStrokeJoin((uint32_t)value));
			}
		}

		property BLStrokeCap StrokeStartCap
		{
			BLStrokeCap get()
			{
				return (BLStrokeCap)impl->strokeStartCap();
			}
			void set(BLStrokeCap value)
			{
				CheckResult(impl->setStrokeStartCap((uint32_t)value));
			}
		}

		property BLStrokeCap StrokeEndCap
		{
			BLStrokeCap get()
			{
				return (BLStrokeCap)impl->strokeEndCap();
			}
			void set(BLStrokeCap value)
			{
				CheckResult(impl->setStrokeEndCap((uint32_t)value));
			}
		}

		property BLStrokeTransformOrder StrokeTransformOrder
		{
			BLStrokeTransformOrder get()
			{
				return (BLStrokeTransformOrder)impl->strokeTransformOrder();
			}
			void set(BLStrokeTransformOrder value)
			{
				CheckResult(impl->setStrokeTransformOrder((uint32_t)value));
			}
		}

		property BLFillRule FillRule
		{
			BLFillRule get()
			{
				return (BLFillRule)impl->fillRule();
			}
			void set(BLFillRule value)
			{
				impl->setFillRule((uint32_t)value);
			}
		}

		property BLStyle^ FillStyle
		{
			BLStyle^ get()
			{
				auto fillStyle = gcnew BLStyle();
				CheckResult(blContextGetFillStyle(this, fillStyle));
				return fillStyle;
			}
			void set(BLStyle^ value)
			{
				CheckResult(blContextSetFillStyle(this, value));
			}
		}

		property BLStyle^ StrokeStyle
		{
			BLStyle^ get()
			{
				auto strokeStyle = gcnew BLStyle();
				CheckResult(blContextGetStrokeStyle(this, strokeStyle));
				return strokeStyle;
			}
			void set(BLStyle^ value)
			{
				CheckResult(blContextSetStrokeStyle(this, value));
			}
		}

		property BLMatrix2D MetaMatrix
		{
			BLMatrix2D get()
			{
				return BLMatrix2D(impl->metaMatrix());
			}
		}

		property BLMatrix2D UserMatrix
		{
			BLMatrix2D get()
			{
				return BLMatrix2D(impl->userMatrix());
			}
			void set(BLMatrix2D value)
			{
				Pin(BLMatrix2D, pMatrix, value);

				ApplyMatrixOp(BLMatrix2DOp::Assign, pMatrix);
			}
		}
	};
}