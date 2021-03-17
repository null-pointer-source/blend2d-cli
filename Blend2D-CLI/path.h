#pragma once

#include "api.h"
#include "object.h"
#include "geometry.h"
#include "matrix.h"

using namespace System;
using namespace System::Diagnostics;

#define ApproximationOptions(source) (::BLApproximationOptions*)(source)

namespace Blend2D
{
	//! Path command.
	public enum class BLPathCommand : Byte
	{
		//! Move-to command (starts a new figure).
		Move = BL_PATH_CMD_MOVE,
		//! On-path command (interpreted as line-to or the end of a curve).
		On = BL_PATH_CMD_ON,
		//! Quad-to control point.
		Quad = BL_PATH_CMD_QUAD,
		//! Cubic-to control point (always used as a pair of commands).
		Cubic = BL_PATH_CMD_CUBIC,
		//! Close path.
		Close = BL_PATH_CMD_CLOSE,
	};

	//! Path flags.
	[FlagsAttribute]
	public enum class BLPathFlags : UInt32
	{
		//! Path is empty (no commands or close commands only).
		Empty = BL_PATH_FLAG_EMPTY,
		//! Path contains multiple figures.
		Multiple = BL_PATH_FLAG_MULTIPLE,
		//! Path contains quad curves (at least one).
		Quads = BL_PATH_FLAG_QUADS,
		//! Path contains cubic curves (at least one).
		Cubics = BL_PATH_FLAG_CUBICS,
		//! Path is invalid.
		Invalid = BL_PATH_FLAG_INVALID,
		//! Flags are dirty (not reflecting the current status).
		Dirty = BL_PATH_FLAG_DIRTY
	};

	//! Path reversal mode.
	public enum class BLPathReverseMode : UInt32
	{
		//! Reverse each figure and their order as well (default).
		Complete = BL_PATH_REVERSE_MODE_COMPLETE,
		//! Reverse each figure separately (keeps their order).
		Separate = BL_PATH_REVERSE_MODE_SEPARATE,
	};

	//! Stroke join type.
	public enum class BLStrokeJoin : UInt32
	{
		//! Miter-join possibly clipped at `miterLimit` [default].
		MiterClip = BL_STROKE_JOIN_MITER_CLIP,
		//! Miter-join or bevel-join depending on miterLimit condition.
		MiterBevel = BL_STROKE_JOIN_MITER_BEVEL,
		//! Miter-join or round-join depending on miterLimit condition.
		MiterRound = BL_STROKE_JOIN_MITER_ROUND,
		//! Bevel-join.
		Bevel = BL_STROKE_JOIN_BEVEL,
		//! Round-join.
		Round = BL_STROKE_JOIN_ROUND,
	};

	//! A presentation attribute defining the shape to be used at the end of open subpaths.
	public enum class BLStrokeCap : UInt32
	{
		//! Butt cap [default].
		Butt = BL_STROKE_CAP_BUTT,
		//! Square cap.
		Square = BL_STROKE_CAP_SQUARE,
		//! Round cap.
		Round = BL_STROKE_CAP_ROUND,
		//! Round cap reversed.
		RoundReversed = BL_STROKE_CAP_ROUND_REV,
		//! Triangle cap.
		Triangle = BL_STROKE_CAP_TRIANGLE,
		//! Triangle cap reversed.
		TriangleReversed = BL_STROKE_CAP_TRIANGLE_REV,
	};

	//! Stroke transform order.
	public enum class BLStrokeTransformOrder : UInt32
	{
		//! Transform after stroke  => `Transform(Stroke(Input))` [default].
		After = BL_STROKE_TRANSFORM_ORDER_AFTER,
		//! Transform before stroke => `Stroke(Transform(Input))`.
		Before = BL_STROKE_TRANSFORM_ORDER_BEFORE,
	};

	//! Mode that specifies how curves are approximated to line segments.
	public enum class BLFlattenMode : UInt32
	{
		//! Use default mode (decided by Blend2D).
		Default = BL_FLATTEN_MODE_DEFAULT,
		//! Recursive subdivision flattening.
		Recursive = BL_FLATTEN_MODE_RECURSIVE,
	};

	//! Mode that specifies how to construct offset curves.
	public enum class BLOffsetMode : UInt32
	{
		//! Use default mode (decided by Blend2D).
		Default = BL_OFFSET_MODE_DEFAULT,
		//! Iterative offset construction.
		Iterative = BL_OFFSET_MODE_ITERATIVE,
	};

	public value struct BLApproximationOptions sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint8_t flattenMode;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint8_t offsetMode;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint8_t reservedFlags0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint8_t reservedFlags1;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint8_t reservedFlags2;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint8_t reservedFlags3;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint8_t reservedFlags4;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		uint8_t reservedFlags5;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double flattenTolerance;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double simplifyTolerance;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double offsetParameter;

	internal:

		BLApproximationOptions(const ::BLApproximationOptions& other)
		{
			flattenMode = other.flattenMode;
			offsetMode = other.offsetMode;
			flattenTolerance = other.flattenTolerance;
			simplifyTolerance = other.simplifyTolerance;
			offsetParameter = other.offsetParameter;
		}

		BLApproximationOptions(const ::BLApproximationOptions* other)
		{
			flattenMode = other->flattenMode;
			offsetMode = other->offsetMode;
			flattenTolerance = other->flattenTolerance;
			simplifyTolerance = other->simplifyTolerance;
			offsetParameter = other->offsetParameter;
		}

	public:

		static property BLApproximationOptions Default
		{
			BLApproximationOptions get()
			{
				return BLApproximationOptions(&blDefaultApproximationOptions);
			}
		}

		property BLFlattenMode FlattenMode
		{
			BLFlattenMode get()
			{
				return (BLFlattenMode)flattenMode;
			}
			void set(BLFlattenMode value)
			{
				flattenMode = (uint8_t)value;
			}
		}

		property BLOffsetMode OffsetMode
		{
			BLOffsetMode get()
			{
				return (BLOffsetMode)offsetMode;
			}
			void set(BLOffsetMode value)
			{
				offsetMode = (uint8_t)value;
			}
		}

		property double FlattenTolerance
		{
			double get()
			{
				return flattenTolerance;
			}
			void set(double value)
			{
				flattenTolerance = value;
			}
		}

		property double SimplifyTolerance
		{
			double get()
			{
				return simplifyTolerance;
			}
			void set(double value)
			{
				simplifyTolerance = value;
			}
		}

		property double OffsetParameter
		{
			double get()
			{
				return offsetParameter;
			}
			void set(double value)
			{
				offsetParameter = value;
			}
		}
	};

	public ref class BLStrokeOptions sealed : public BLObject
	{
	private:

		typedef ::BLStrokeOptions ImplType;

	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLObjectPointer<ImplType> impl;

	public:

		BLStrokeOptions()
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

		void Reset()
		{
			CheckResult(blStrokeOptionsReset(this));
		}

		void SetCaps(BLStrokeCap strokeCap)
		{
			impl->setCaps((uint32_t)strokeCap);
		}

	public:

		property BLStrokeCap StartCap
		{
			BLStrokeCap get()
			{
				return (BLStrokeCap)impl->startCap;
			}
			void set(BLStrokeCap value)
			{
				impl->startCap = (uint8_t)value;
			}
		}

		property BLStrokeCap EndCap
		{
			BLStrokeCap get()
			{
				return (BLStrokeCap)impl->endCap;
			}
			void set(BLStrokeCap value)
			{
				impl->endCap = (uint8_t)value;
			}
		}

		property BLStrokeJoin Join
		{
			BLStrokeJoin get()
			{
				return (BLStrokeJoin)impl->join;
			}
			void set(BLStrokeJoin value)
			{
				impl->join = (uint8_t)value;
			}
		}

		property BLStrokeTransformOrder TransformOrder
		{
			BLStrokeTransformOrder get()
			{
				return (BLStrokeTransformOrder)impl->transformOrder;
			}
			void set(BLStrokeTransformOrder value)
			{
				impl->transformOrder = (uint8_t)value;
			}
		}

		property double Width
		{
			double get()
			{
				return impl->width;
			}
			void set(double value)
			{
				impl->width = value;
			}
		}

		property double MiterLimit
		{
			double get()
			{
				return impl->miterLimit;
			}
			void set(double value)
			{
				impl->miterLimit = value;
			}
		}

		property double DashOffset
		{
			double get()
			{
				return impl->dashOffset;
			}
			void set(double value)
			{
				impl->dashOffset = value;
			}
		}
	};

	public ref class BLPath sealed : public BLObject
	{
	private:

		typedef ::BLPath ImplType;

	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLObjectPointer<ImplType> impl;

	public:

		BLPath()
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

		// Path Construction

		void Clear()
		{
			CheckResult(blPathClear(this));
		}

		void Shrink()
		{
			CheckResult(blPathShrink(this));
		}

		void Reserve(size_t n)
		{
			CheckResult(blPathReserve(this, n));
		}

		void SetVertexAt(size_t index, BLPathCommand cmd, BLPoint pt)
		{
			CheckResult(blPathSetVertexAt(this, index, (uint32_t)cmd, pt.X, pt.Y));
		}

		void SetVertexAt(size_t index, BLPathCommand cmd, double x, double y)
		{
			CheckResult(blPathSetVertexAt(this, index, (uint32_t)cmd, x, y));
		}

		void MoveTo(BLPoint p0)
		{
			CheckResult(blPathMoveTo(this, p0.X, p0.Y));
		}

		void MoveTo(double x0, double y0)
		{
			CheckResult(blPathMoveTo(this, x0, y0));
		}

		void LineTo(BLPoint p1)
		{
			CheckResult(blPathLineTo(this, p1.X, p1.Y));
		}

		void LineTo(double x1, double y1)
		{
			CheckResult(blPathLineTo(this, x1, y1));
		}

		void PolyTo(array<BLPoint>^ poly)
		{
			if (poly->Length > 0)
			{
				Pin(BLPoint, pPoly, poly[0]);

				CheckResult(blPathPolyTo(this, Point(pPoly), poly->Length));
			}
		}

		void QuadTo(BLPoint p1, BLPoint p2)
		{
			CheckResult(blPathQuadTo(this, p1.X, p1.Y, p2.X, p2.Y));
		}

		void QuadTo(double x1, double y1, double x2, double y2)
		{
			CheckResult(blPathQuadTo(this, x1, y1, x2, y2));
		}

		void CubicTo(BLPoint p1, BLPoint p2, BLPoint p3)
		{
			CheckResult(blPathCubicTo(this, p1.X, p1.Y, p2.X, p2.Y, p3.X, p3.Y));
		}

		void CubicTo(double x1, double y1, double x2, double y2, double x3, double y3)
		{
			CheckResult(blPathCubicTo(this, x1, y1, x2, y2, x3, y3));
		}

		void SmoothQuadTo(BLPoint p2)
		{
			CheckResult(blPathSmoothQuadTo(this, p2.X, p2.Y));
		}

		void SmoothQuadTo(double x2, double y2)
		{
			CheckResult(blPathSmoothQuadTo(this, x2, y2));
		}

		void SmoothCubicTo(BLPoint p2, BLPoint p3)
		{
			CheckResult(blPathSmoothCubicTo(this, p2.X, p2.Y, p3.X, p3.Y));
		}

		void SmoothCubicTo(double x2, double y2, double x3, double y3)
		{
			CheckResult(blPathSmoothCubicTo(this, x2, y2, x3, y3));
		}

		void ArcTo(BLPoint c, BLPoint r, double start, double sweep)
		{
			CheckResult(blPathArcTo(this, c.X, c.Y, r.X, r.Y, start, sweep, false));
		}

		void ArcTo(BLPoint c, BLPoint r, double start, double sweep, bool forceMoveTo)
		{
			CheckResult(blPathArcTo(this, c.X, c.Y, r.X, r.Y, start, sweep, forceMoveTo));
		}

		void ArcTo(double cx, double cy, double rx, double ry, double start, double sweep)
		{
			CheckResult(blPathArcTo(this, cx, cy, rx, ry, start, sweep, false));
		}

		void ArcTo(double cx, double cy, double rx, double ry, double start, double sweep, bool forceMoveTo)
		{
			CheckResult(blPathArcTo(this, cx, cy, rx, ry, start, sweep, forceMoveTo));
		}

		void ArcQuadrantTo(BLPoint p1, BLPoint p2)
		{
			CheckResult(blPathArcQuadrantTo(this, p1.X, p1.Y, p2.X, p2.Y));
		}

		void ArcQuadrantTo(double x1, double y1, double x2, double y2)
		{
			CheckResult(blPathArcQuadrantTo(this, x1, y1, x2, y2));
		}

		void EllipticArcTo(BLPoint rp, double xAxisRotation, bool largeArcFlag, bool sweepFlag, BLPoint p1)
		{
			CheckResult(blPathEllipticArcTo(this, rp.X, rp.Y, xAxisRotation, largeArcFlag, sweepFlag, p1.X, p1.Y));
		}

		void EllipticArcTo(double rx, double ry, double xAxisRotation, bool largeArcFlag, bool sweepFlag, double x1, double y1)
		{
			CheckResult(blPathEllipticArcTo(this, rx, ry, xAxisRotation, largeArcFlag, sweepFlag, x1, y1));
		}

		void Close()
		{
			CheckResult(blPathClose(this));
		}

	public:

		// Adding Figures

		void AddBox(BLBoxI box)
		{
			AddBox(box, BLGeometryDirection::CW);
		}

		void AddBox(BLBoxI box, BLGeometryDirection dir)
		{
			Pin(BLBoxI, pBox, box);

			CheckResult(blPathAddBoxI(this, BoxI(pBox), (uint32_t)dir));
		}

		void AddBox(BLBox box)
		{
			AddBox(box, BLGeometryDirection::CW);
		}

		void AddBox(BLBox box, BLGeometryDirection dir)
		{
			Pin(BLBox, pBox, box);

			CheckResult(blPathAddBoxD(this, Box(pBox), (uint32_t)dir));
		}

		void AddBox(double x0, double y0, double x1, double y1)
		{
			AddBox(BLBox(x0, y0, x1, y1), BLGeometryDirection::CW);
		}

		void AddBox(double x0, double y0, double x1, double y1, BLGeometryDirection dir)
		{
			AddBox(BLBox(x0, y0, x1, y1), dir);
		}

		void AddRect(BLRectI rect)
		{
			AddRect(rect, BLGeometryDirection::CW);
		}

		void AddRect(BLRectI rect, BLGeometryDirection dir)
		{
			Pin(BLRectI, pRect, rect);

			CheckResult(blPathAddRectI(this, RectI(pRect), (uint32_t)dir));
		}

		void AddRect(BLRect rect)
		{
			AddRect(rect, BLGeometryDirection::CW);
		}

		void AddRect(BLRect rect, BLGeometryDirection dir)
		{
			Pin(BLRect, pRect, rect);

			CheckResult(blPathAddRectD(this, Rect(pRect), (uint32_t)dir));
		}

		void AddRect(double x, double y, double w, double h)
		{
			AddRect(BLRect(x, y, w, h), BLGeometryDirection::CW);
		}

		void AddRect(double x, double y, double w, double h, BLGeometryDirection dir)
		{
			AddRect(BLRect(x, y, w, h), dir);
		}

		void AddCircle(BLCircle circle)
		{
			Pin(BLCircle, pCircle, circle);

			AddGeometry(BLGeometryType::Circle, pCircle, nullptr, BLGeometryDirection::CW);
		}

		void AddCircle(BLCircle circle, BLMatrix2D m)
		{
			Pin(BLCircle, pCircle, circle);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Circle, pCircle, pMatrix, BLGeometryDirection::CW);
		}

		void AddCircle(BLCircle circle, BLGeometryDirection dir)
		{
			Pin(BLCircle, pCircle, circle);

			AddGeometry(BLGeometryType::Circle, pCircle, nullptr, dir);
		}

		void AddCircle(BLCircle circle, BLMatrix2D m, BLGeometryDirection dir)
		{
			Pin(BLCircle, pCircle, circle);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Circle, pCircle, pMatrix, dir);
		}

		void AddEllipse(BLEllipse ellipse)
		{
			Pin(BLEllipse, pEllipse, ellipse);

			AddGeometry(BLGeometryType::Circle, pEllipse, nullptr, BLGeometryDirection::CW);
		}

		void AddEllipse(BLEllipse ellipse, BLMatrix2D m)
		{
			Pin(BLEllipse, pEllipse, ellipse);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Ellipse, pEllipse, pMatrix, BLGeometryDirection::CW);
		}

		void AddEllipse(BLEllipse ellipse, BLGeometryDirection dir)
		{
			Pin(BLEllipse, pEllipse, ellipse);

			AddGeometry(BLGeometryType::Ellipse, pEllipse, nullptr, dir);
		}

		void AddEllipse(BLEllipse ellipse, BLMatrix2D m, BLGeometryDirection dir)
		{
			Pin(BLEllipse, pEllipse, ellipse);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Ellipse, pEllipse, pMatrix, dir);
		}

		void AddRoundRect(BLRoundRect roundRect)
		{
			Pin(BLRoundRect, pRoundRect, roundRect);

			AddGeometry(BLGeometryType::RoundRect, pRoundRect, nullptr, BLGeometryDirection::CW);
		}

		void AddRoundRect(BLRoundRect roundRect, BLMatrix2D m)
		{
			Pin(BLRoundRect, pRoundRect, roundRect);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::RoundRect, pRoundRect, pMatrix, BLGeometryDirection::CW);
		}

		void AddRoundRect(BLRoundRect roundRect, BLGeometryDirection dir)
		{
			Pin(BLRoundRect, pRoundRect, roundRect);

			AddGeometry(BLGeometryType::RoundRect, pRoundRect, nullptr, dir);
		}

		void AddRoundRect(BLRoundRect roundRect, BLMatrix2D m, BLGeometryDirection dir)
		{
			Pin(BLRoundRect, pRoundRect, roundRect);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::RoundRect, pRoundRect, pMatrix, dir);
		}

		void AddArc(BLArc arc)
		{
			Pin(BLArc, pArc, arc);

			AddGeometry(BLGeometryType::Arc, pArc, nullptr, BLGeometryDirection::CW);
		}

		void AddArc(BLArc arc, BLMatrix2D m)
		{
			Pin(BLArc, pArc, arc);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Arc, pArc, pMatrix, BLGeometryDirection::CW);
		}

		void AddArc(BLArc arc, BLGeometryDirection dir)
		{
			Pin(BLArc, pArc, arc);

			AddGeometry(BLGeometryType::Arc, pArc, nullptr, dir);
		}

		void AddArc(BLArc arc, BLMatrix2D m, BLGeometryDirection dir)
		{
			Pin(BLArc, pArc, arc);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Arc, pArc, pMatrix, dir);
		}

		void AddChord(BLArc chord)
		{
			Pin(BLArc, pChord, chord);

			AddGeometry(BLGeometryType::Chord, pChord, nullptr, BLGeometryDirection::CW);
		}

		void AddChord(BLArc chord, BLMatrix2D m)
		{
			Pin(BLArc, pChord, chord);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Chord, pChord, pMatrix, BLGeometryDirection::CW);
		}

		void AddChord(BLArc chord, BLGeometryDirection dir)
		{
			Pin(BLArc, pChord, chord);

			AddGeometry(BLGeometryType::Chord, pChord, nullptr, dir);
		}

		void AddChord(BLArc chord, BLMatrix2D m, BLGeometryDirection dir)
		{
			Pin(BLArc, pChord, chord);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Chord, pChord, pMatrix, dir);
		}

		void AddPie(BLArc pie)
		{
			Pin(BLArc, pPie, pie);

			AddGeometry(BLGeometryType::Pie, pPie, nullptr, BLGeometryDirection::CW);
		}

		void AddPie(BLArc pie, BLMatrix2D m)
		{
			Pin(BLArc, pPie, pie);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Pie, pPie, pMatrix, BLGeometryDirection::CW);
		}

		void AddPie(BLArc pie, BLGeometryDirection dir)
		{
			Pin(BLArc, pPie, pie);

			AddGeometry(BLGeometryType::Pie, pPie, nullptr, dir);
		}

		void AddPie(BLArc pie, BLMatrix2D m, BLGeometryDirection dir)
		{
			Pin(BLArc, pPie, pie);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Pie, pPie, pMatrix, dir);
		}

		void AddLine(BLLine line)
		{
			Pin(BLLine, pLine, line);

			AddGeometry(BLGeometryType::Line, pLine, nullptr, BLGeometryDirection::CW);
		}
		void AddLine(BLLine line, BLMatrix2D m)
		{
			Pin(BLLine, pLine, line);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Line, pLine, pMatrix, BLGeometryDirection::CW);
		}

		void AddLine(BLLine line, BLGeometryDirection dir)
		{
			Pin(BLLine, pLine, line);

			AddGeometry(BLGeometryType::Line, pLine, nullptr, dir);
		}

		void AddLine(BLLine line, BLMatrix2D m, BLGeometryDirection dir)
		{
			Pin(BLLine, pLine, line);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Line, pLine, pMatrix, dir);
		}

		void AddTriangle(BLTriangle triangle)
		{
			Pin(BLTriangle, pTriangle, triangle);

			AddGeometry(BLGeometryType::Triangle, pTriangle, nullptr, BLGeometryDirection::CW);
		}

		void AddTriangle(BLTriangle triangle, BLMatrix2D m)
		{
			Pin(BLTriangle, pTriangle, triangle);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Triangle, pTriangle, pMatrix, BLGeometryDirection::CW);
		}

		void AddTriangle(BLTriangle triangle, BLGeometryDirection dir)
		{
			Pin(BLTriangle, pTriangle, triangle);

			AddGeometry(BLGeometryType::Triangle, pTriangle, nullptr, dir);
		}

		void AddTriangle(BLTriangle triangle, BLMatrix2D m, BLGeometryDirection dir)
		{
			Pin(BLTriangle, pTriangle, triangle);
			Pin(BLMatrix2D, pMatrix, m);

			AddGeometry(BLGeometryType::Triangle, pTriangle, pMatrix, dir);
		}

		void AddPolyLine(array<BLPointI>^ poly)
		{
			if (poly->Length > 0)
			{
				Pin(BLPointI, pPoly, poly[0]);

				AddGeometry(BLGeometryType::PolyLineI, pPoly, nullptr, BLGeometryDirection::CW);
			}
		}

		void AddPolyLine(array<BLPointI>^ poly, BLMatrix2D m)
		{
			if (poly->Length > 0)
			{
				Pin(BLPointI, pPoly, poly[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::PolyLineI, pPoly, pMatrix, BLGeometryDirection::CW);
			}
		}

		void AddPolyLine(array<BLPointI>^ poly, BLGeometryDirection dir)
		{
			if (poly->Length > 0)
			{
				Pin(BLPointI, pPoly, poly[0]);

				AddGeometry(BLGeometryType::PolyLineI, pPoly, nullptr, dir);
			}
		}

		void AddPolyLine(array<BLPointI>^ poly, BLMatrix2D m, BLGeometryDirection dir)
		{
			if (poly->Length > 0)
			{
				Pin(BLPointI, pPoly, poly[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::PolyLineI, pPoly, pMatrix, dir);
			}
		}

		void AddPolyLine(array<BLPoint>^ poly)
		{
			if (poly->Length > 0)
			{
				Pin(BLPoint, pPoly, poly[0]);

				AddGeometry(BLGeometryType::PolyLine, pPoly, nullptr, BLGeometryDirection::CW);
			}
		}

		void AddPolyLine(array<BLPoint>^ poly, BLMatrix2D m)
		{
			if (poly->Length > 0)
			{
				Pin(BLPoint, pPoly, poly[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::PolyLine, pPoly, pMatrix, BLGeometryDirection::CW);
			}
		}

		void AddPolyLine(array<BLPoint>^ poly, BLGeometryDirection dir)
		{
			if (poly->Length > 0)
			{
				Pin(BLPoint, pPoly, poly[0]);

				AddGeometry(BLGeometryType::PolyLine, pPoly, nullptr, dir);
			}
		}

		void AddPolyLine(array<BLPoint>^ poly, BLMatrix2D m, BLGeometryDirection dir)
		{
			if (poly->Length > 0)
			{
				Pin(BLPoint, pPoly, poly[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::PolyLine, pPoly, pMatrix, dir);
			}
		}

		void AddPolygon(array<BLPointI>^ poly)
		{
			if (poly->Length > 0)
			{
				Pin(BLPointI, pPoly, poly[0]);

				AddGeometry(BLGeometryType::PolygonI, pPoly, nullptr, BLGeometryDirection::CW);
			}
		}

		void AddPolygon(array<BLPointI>^ poly, BLMatrix2D m)
		{
			if (poly->Length > 0)
			{
				Pin(BLPointI, pPoly, poly[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::PolygonI, pPoly, pMatrix, BLGeometryDirection::CW);
			}
		}

		void AddPolygon(array<BLPointI>^ poly, BLGeometryDirection dir)
		{
			if (poly->Length > 0)
			{
				Pin(BLPointI, pPoly, poly[0]);

				AddGeometry(BLGeometryType::PolygonI, pPoly, nullptr, dir);
			}
		}

		void AddPolygon(array<BLPointI>^ poly, BLMatrix2D m, BLGeometryDirection dir)
		{
			if (poly->Length > 0)
			{
				Pin(BLPointI, pPoly, poly[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::PolygonI, pPoly, pMatrix, dir);
			}
		}

		void AddPolygon(array<BLPoint>^ poly)
		{
			if (poly->Length > 0)
			{
				Pin(BLPoint, pPoly, poly[0]);

				AddGeometry(BLGeometryType::Polygon, pPoly, nullptr, BLGeometryDirection::CW);
			}
		}

		void AddPolygon(array<BLPoint>^ poly, BLMatrix2D m)
		{
			if (poly->Length > 0)
			{
				Pin(BLPoint, pPoly, poly[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::Polygon, pPoly, pMatrix, BLGeometryDirection::CW);
			}
		}

		void AddPolygon(array<BLPoint>^ poly, BLGeometryDirection dir)
		{
			if (poly->Length > 0)
			{
				Pin(BLPoint, pPoly, poly[0]);

				AddGeometry(BLGeometryType::Polygon, pPoly, nullptr, dir);
			}
		}

		void AddPolygon(array<BLPoint>^ poly, BLMatrix2D m, BLGeometryDirection dir)
		{
			if (poly->Length > 0)
			{
				Pin(BLPoint, pPoly, poly[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::Polygon, pPoly, pMatrix, dir);
			}
		}

		void AddBoxArray(array<BLBoxI>^ array)
		{
			if (array->Length > 0)
			{
				Pin(BLBoxI, pArray, array[0]);

				AddGeometry(BLGeometryType::BoxIArray, pArray, nullptr, BLGeometryDirection::CW);
			}
		}

		void AddBoxArray(array<BLBoxI>^ array, BLMatrix2D m)
		{
			if (array->Length > 0)
			{
				Pin(BLBoxI, pArray, array[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::BoxIArray, pArray, pMatrix, BLGeometryDirection::CW);
			}
		}

		void AddBoxArray(array<BLBoxI>^ array, BLGeometryDirection dir)
		{
			if (array->Length > 0)
			{
				Pin(BLBoxI, pArray, array[0]);

				AddGeometry(BLGeometryType::BoxIArray, pArray, nullptr, dir);
			}
		}

		void AddBoxArray(array<BLBoxI>^ array, BLMatrix2D m, BLGeometryDirection dir)
		{
			if (array->Length > 0)
			{
				Pin(BLBoxI, pArray, array[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::BoxIArray, pArray, pMatrix, dir);
			}
		}

		void AddBoxArray(array<BLBox>^ array)
		{
			if (array->Length > 0)
			{
				Pin(BLBox, pArray, array[0]);

				AddGeometry(BLGeometryType::BoxArray, pArray, nullptr, BLGeometryDirection::CW);
			}
		}

		void AddBoxArray(array<BLBox>^ array, BLMatrix2D m)
		{
			if (array->Length > 0)
			{
				Pin(BLBox, pArray, array[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::BoxArray, pArray, pMatrix, BLGeometryDirection::CW);
			}
		}

		void AddBoxArray(array<BLBox>^ array, BLGeometryDirection dir)
		{
			if (array->Length > 0)
			{
				Pin(BLBox, pArray, array[0]);

				AddGeometry(BLGeometryType::BoxArray, pArray, nullptr, dir);
			}
		}

		void AddBoxArray(array<BLBox>^ array, BLMatrix2D m, BLGeometryDirection dir)
		{
			if (array->Length > 0)
			{
				Pin(BLBox, pArray, array[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::BoxArray, pArray, pMatrix, dir);
			}
		}

		void AddRectArray(array<BLRectI>^ array)
		{
			if (array->Length > 0)
			{
				Pin(BLRectI, pArray, array[0]);

				AddGeometry(BLGeometryType::RectIArray, pArray, nullptr, BLGeometryDirection::CW);
			}
		}

		void AddRectArray(array<BLRectI>^ array, BLMatrix2D m)
		{
			if (array->Length > 0)
			{
				Pin(BLRectI, pArray, array[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::RectIArray, pArray, pMatrix, BLGeometryDirection::CW);
			}
		}

		void AddRectArray(array<BLRectI>^ array, BLGeometryDirection dir)
		{
			if (array->Length > 0)
			{
				Pin(BLRectI, pArray, array[0]);

				AddGeometry(BLGeometryType::RectIArray, pArray, nullptr, dir);
			}
		}

		void AddRectArray(array<BLRectI>^ array, BLMatrix2D m, BLGeometryDirection dir)
		{
			if (array->Length > 0)
			{
				Pin(BLRectI, pArray, array[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::RectIArray, pArray, pMatrix, dir);
			}
		}

		void AddRectArray(array<BLRect>^ array)
		{
			if (array->Length > 0)
			{
				Pin(BLRect, pArray, array[0]);

				AddGeometry(BLGeometryType::RectArray, pArray, nullptr, BLGeometryDirection::CW);
			}
		}

		void AddRectArray(array<BLRect>^ array, BLMatrix2D m)
		{
			if (array->Length > 0)
			{
				Pin(BLRect, pArray, array[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::RectArray, pArray, pMatrix, BLGeometryDirection::CW);
			}
		}

		void AddRectArray(array<BLRect>^ array, BLGeometryDirection dir)
		{
			if (array->Length > 0)
			{
				Pin(BLRect, pArray, array[0]);

				AddGeometry(BLGeometryType::RectArray, pArray, nullptr, dir);
			}
		}

		void AddRectArray(array<BLRect>^ array, BLMatrix2D m, BLGeometryDirection dir)
		{
			if (array->Length > 0)
			{
				Pin(BLRect, pArray, array[0]);
				Pin(BLMatrix2D, pMatrix, m);

				AddGeometry(BLGeometryType::RectArray, pArray, pMatrix, dir);
			}
		}

	public:

		// Adding Paths

		void AddPath(BLPath^ path)
		{
			CheckResult(blPathAddPath(this, path, nullptr));
		}

		void AddPath(BLPath^ path, BLRange range)
		{
			Pin(BLRange, pRange, range);

			CheckResult(blPathAddPath(this, path, Range(pRange)));
		}

		void AddPath(BLPath^ path, BLPoint p)
		{
			Pin(BLPoint, pPoint, p);

			CheckResult(blPathAddTranslatedPath(this, path, nullptr, Point(pPoint)));
		}

		void AddPath(BLPath^ path, BLRange range, BLPoint p)
		{
			Pin(BLRange, pRange, range);
			Pin(BLPoint, pPoint, p);

			CheckResult(blPathAddTranslatedPath(this, path, Range(pRange), Point(pPoint)));
		}

		void AddPath(BLPath^ path, BLMatrix2D m)
		{
			Pin(BLMatrix2D, pMatrix, m);

			CheckResult(blPathAddTransformedPath(this, path, nullptr, Matrix2D(pMatrix)));
		}

		void AddPath(BLPath^ path, BLRange range, BLMatrix2D m)
		{
			Pin(BLRange, pRange, range);
			Pin(BLMatrix2D, pMatrix, m);

			CheckResult(blPathAddTransformedPath(this, path, Range(pRange), Matrix2D(pMatrix)));
		}

		void AddReversedPath(BLPath^ path, BLPathReverseMode reverseMode)
		{
			CheckResult(blPathAddReversedPath(this, path, nullptr, (uint32_t)reverseMode));
		}

		void AddReversedPath(BLPath^ path, BLRange range, BLPathReverseMode reverseMode)
		{
			Pin(BLRange, pRange, range);

			CheckResult(blPathAddReversedPath(this, path, Range(pRange), (uint32_t)reverseMode));
		}

		void AddStrokedPath(BLPath^ path, BLStrokeOptions^ strokeOptions, BLApproximationOptions approximationOptions)
		{
			Pin(BLApproximationOptions, pApproximationOptions, approximationOptions);

			CheckResult(blPathAddStrokedPath(this, path, nullptr, strokeOptions, ApproximationOptions(pApproximationOptions)));
		}

		void AddStrokedPath(BLPath^ path, BLRange range, BLStrokeOptions^ strokeOptions, BLApproximationOptions approximationOptions)
		{
			Pin(BLRange, pRange, range);
			Pin(BLApproximationOptions, pApproximationOptions, approximationOptions);

			CheckResult(blPathAddStrokedPath(this, path, Range(pRange), strokeOptions, ApproximationOptions(pApproximationOptions)));
		}

	public:

		// Manipulation

		void RemoveRange(BLRange range)
		{
			Pin(BLRange, pRange, range);

			CheckResult(blPathRemoveRange(this, Range(pRange)));
		}

	public:

		// Transformations

		void Translate(BLPoint p)
		{
			Pin(BLPoint, pPoint, p);

			CheckResult(blPathTranslate(this, nullptr, Point(pPoint)));
		}

		void Translate(BLRange range, BLPoint p)
		{
			Pin(BLRange, pRange, range);
			Pin(BLPoint, pPoint, p);

			CheckResult(blPathTranslate(this, Range(pRange), Point(pPoint)));
		}

		void Transform(BLMatrix2D m)
		{
			Pin(BLMatrix2D, pMatrix, m);

			CheckResult(blPathTransform(this, nullptr, Matrix2D(pMatrix)));
		}

		void Transform(BLRange range, BLMatrix2D m)
		{
			Pin(BLRange, pRange, range);
			Pin(BLMatrix2D, pMatrix, m);

			CheckResult(blPathTransform(this, Range(pRange), Matrix2D(pMatrix)));
		}

	public:

		// Path Information

		void GetControlBox(BLBox% box)
		{
			Pin(BLBox, pBox, box);

			CheckResult(blPathGetControlBox(this, Box(pBox)));
		}

		void GetBoundingBox(BLBox% box)
		{
			Pin(BLBox, pBox, box);

			CheckResult(blPathGetBoundingBox(this, Box(pBox)));
		}

	public:

		// Hit Testing

		BLHitTest HitTest(BLPoint p, BLFillRule fillRule)
		{
			Pin(BLPoint, pPoint, p);

			return static_cast<BLHitTest>(blPathHitTest(this, Point(pPoint), (uint32_t)fillRule));
		}

	private:

		void AddGeometry(BLGeometryType geometryType, const void* geometryData, const BLMatrix2D* m, BLGeometryDirection dir)
		{
			CheckResult(blPathAddGeometry(this, (uint32_t)geometryType, geometryData, nullptr, (uint32_t)dir));
		}

	public:

		property bool IsNone
		{
			bool get()
			{
				return impl->isNone();
			}
		}

		property bool IsEmpty
		{
			bool get()
			{
				return impl->empty();
			}
		}

		property size_t Size
		{
			size_t get()
			{
				return impl->size();
			}
		}

		property size_t Capacity
		{
			size_t get()
			{
				return impl->capacity();
			}
		}

		property BLPathFlags Flags
		{
			BLPathFlags get()
			{
				return (BLPathFlags)impl->impl->flags;
			}
		}

		property array<BLPoint>^ VertexData
		{
			array<BLPoint>^ get()
			{
				return ConvertToArray<BLPoint>(impl->vertexData(), impl->size());
			}
		}

		property array<BLPathCommand>^ CommandData
		{
			array<BLPathCommand>^ get()
			{
				return ConvertToArray<BLPathCommand>(impl->commandData(), impl->size());
			}
		}
	};
}
