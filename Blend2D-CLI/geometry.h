#pragma once

#include "api.h"

using namespace System;
using namespace System::Diagnostics;

#define PointI(source) (::BLPointI*)(source)
#define RectI(source) (::BLRectI*)(source)
#define BoxI(source) (::BLBoxI*)(source)

#define Point(source) (::BLPoint*)(source)
#define Rect(source) (::BLRect*)(source)
#define Box(source) (::BLBox*)(source)

namespace Blend2D
{
	//! Direction of a geometry used by geometric primitives and paths.
	public enum class BLGeometryDirection : UInt32
	{
		//! No direction specified.
		None = BL_GEOMETRY_DIRECTION_NONE,
		//! Clockwise direction.
		CW = BL_GEOMETRY_DIRECTION_CW,
		//! Counter-clockwise direction.
		CCW = BL_GEOMETRY_DIRECTION_CCW
	};

	//! Geometry type.
	public enum class BLGeometryType : UInt32
	{
		//! No geometry provided.
		None = BL_GEOMETRY_TYPE_NONE,
		//! BLBoxI struct.
		BoxI = BL_GEOMETRY_TYPE_BOXI,
		//! BLBox struct.
		Box = BL_GEOMETRY_TYPE_BOXD,
		//! BLRectI struct.
		RectI = BL_GEOMETRY_TYPE_RECTI,
		//! BLRect struct.
		Rect = BL_GEOMETRY_TYPE_RECTD,
		//! BLCircle struct.
		Circle = BL_GEOMETRY_TYPE_CIRCLE,
		//! BLEllipse struct.
		Ellipse = BL_GEOMETRY_TYPE_ELLIPSE,
		//! BLRoundRect struct.
		RoundRect = BL_GEOMETRY_TYPE_ROUND_RECT,
		//! BLArc struct.
		Arc = BL_GEOMETRY_TYPE_ARC,
		//! BLArc struct representing chord.
		Chord = BL_GEOMETRY_TYPE_CHORD,
		//! BLArc struct representing pie.
		Pie = BL_GEOMETRY_TYPE_PIE,
		//! BLLine struct.
		Line = BL_GEOMETRY_TYPE_LINE,
		//! BLTriangle struct.
		Triangle = BL_GEOMETRY_TYPE_TRIANGLE,
		//! BLArrayView<BLPointI> representing a polyline.
		PolyLineI = BL_GEOMETRY_TYPE_POLYLINEI,
		//! BLArrayView<BLPoint> representing a polyline.
		PolyLine = BL_GEOMETRY_TYPE_POLYLINED,
		//! BLArrayView<BLPointI> representing a polygon.
		PolygonI = BL_GEOMETRY_TYPE_POLYGONI,
		//! BLArrayView<BLPoint> representing a polygon.
		Polygon = BL_GEOMETRY_TYPE_POLYGOND,
		//! BLArrayView<BLBoxI> struct.
		BoxIArray = BL_GEOMETRY_TYPE_ARRAY_VIEW_BOXI,
		//! BLArrayView<BLBox> struct.
		BoxArray = BL_GEOMETRY_TYPE_ARRAY_VIEW_BOXD,
		//! BLArrayView<BLRectI> struct.
		RectIArray = BL_GEOMETRY_TYPE_ARRAY_VIEW_RECTI,
		//! BLArrayView<BLRect> struct.
		RectArray = BL_GEOMETRY_TYPE_ARRAY_VIEW_RECTD,
		//! BLPath (or BLPathCore).
		Path = BL_GEOMETRY_TYPE_PATH,
		//! BLRegion (or BLRegionCore).
		Region = BL_GEOMETRY_TYPE_REGION,
	};

	//! Fill rule.
	public enum class BLFillRule : UInt32
	{
		//! Non-zero fill-rule.
		NonZero = BL_FILL_RULE_NON_ZERO,
		//! Even-odd fill-rule.
		EvenOdd = BL_FILL_RULE_EVEN_ODD,
	};

	//! Hit-test result.
	public enum class BLHitTest : UInt32
	{
		//!< Fully in.
		In = BL_HIT_TEST_IN,
		//!< Partially in/out.
		Part = BL_HIT_TEST_PART,
		//!< Fully out.
		Out = BL_HIT_TEST_OUT,
		//!< Hit test failed (invalid argument, NaNs, etc).
		Invalid = BL_HIT_TEST_INVALID,
	};

	public value struct BLPointI sealed
	{
	private:

		typedef ::BLPointI ImplType;

	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int x;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int y;

	public:

		BLPointI(int x, int y)
			: x(x), y(y)
		{
		}

	internal:

		BLPointI(const ImplType& other)
		{
			x = other.x;
			y = other.y;
		}

	public:

		String^ ToString() override
		{
			return String::Format("X={0}, Y={1}", X, Y);
		}

		void Reset()
		{
			x = 0;
			y = 0;
		}

	public:

		property int X
		{
			int get()
			{
				return x;
			}
			void set(int value)
			{
				x = value;
			}
		}

		property int Y
		{
			int get()
			{
				return y;
			}
			void set(int value)
			{
				y = value;
			}
		}
	};

	public value struct BLRectI sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int x;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int y;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int width;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int height;

	public:

		BLRectI(int x, int y, int width, int height)
			: x(x), y(y), width(width), height(height)
		{
		}

	internal:

		BLRectI(const ::BLRectI& other)
		{
			x = other.x;
			y = other.y;
			width = other.w;
			height = other.h;
		}

	public:

		String^ ToString() override
		{
			return String::Format("X={0}, Y={1}, Width={2}, Height={3}", X, Y, Width, Height);
		}

	public:

		property int X
		{
			int get()
			{
				return x;
			}
			void set(int value)
			{
				x = value;
			}
		}

		property int Y
		{
			int get()
			{
				return y;
			}
			void set(int value)
			{
				y = value;
			}
		}

		property int Width
		{
			int get()
			{
				return width;
			}
			void set(int value)
			{
				width = value;
			}
		}

		property int Height
		{
			int get()
			{
				return height;
			}
			void set(int value)
			{
				height = value;
			}
		}
	};

	public value struct BLBoxI sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int x0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int y0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int x1;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int y1;

	public:

		BLBoxI(int x0, int y0, int x1, int y1)
			: x0(x0), y0(y0), x1(x1), y1(y1)
		{
		}

	public:

		String^ ToString() override
		{
			return String::Format("X0={0}, Y0={1}, X1={2}, Y1={3}", X0, Y0, X1, Y1);
		}

	public:

		property int X0
		{
			int get()
			{
				return x0;
			}
			void set(int value)
			{
				x0 = value;
			}
		}

		property int Y0
		{
			int get()
			{
				return y0;
			}
			void set(int value)
			{
				y0 = value;
			}
		}

		property int X1
		{
			int get()
			{
				return x1;
			}
			void set(int value)
			{
				x1 = value;
			}
		}

		property int Y1
		{
			int get()
			{
				return y1;
			}
			void set(int value)
			{
				y1 = value;
			}
		}
	};

	public value struct BLPoint sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double x;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double y;

	public:

		BLPoint(double x, double y)
			: x(x), y(y)
		{
		}

	internal:

		BLPoint(const ::BLPoint& other)
		{
			x = other.x;
			y = other.y;
		}

	public:

		String^ ToString() override
		{
			return String::Format("X={0:0.00}, Y={1:0.00}", X, Y);
		}

		void Reset()
		{
			x = 0;
			y = 0;
		}

	public:

		property double X
		{
			double get()
			{
				return x;
			}
			void set(double value)
			{
				x = value;
			}
		}

		property double Y
		{
			double get()
			{
				return y;
			}
			void set(double value)
			{
				y = value;
			}
		}
	};

	public value struct BLSize sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double width;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double height;

	public:

		BLSize(double width, double height)
			: width(width), height(height)
		{
		}

	public:

		String^ ToString() override
		{
			return String::Format("Width={0:0.00}, Height={1:0.00}", Width, Height);
		}

	public:

		property double Width
		{
			double get()
			{
				return width;
			}
			void set(double value)
			{
				width = value;
			}
		}

		property double Height
		{
			double get()
			{
				return height;
			}
			void set(double value)
			{
				height = value;
			}
		}
	};

	public value struct BLRect sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double x;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double y;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double width;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double height;

	public:

		BLRect(double x, double y, double width, double height)
			: x(x), y(y), width(width), height(height)
		{
		}

	public:

		String^ ToString() override
		{
			return String::Format("X={0:0.00}, Y={1:0.00}, Width={2:0.00}, Height={3:0.00}", X, Y, Width, Height);
		}

	public:

		property double X
		{
			double get()
			{
				return x;
			}
			void set(double value)
			{
				x = value;
			}
		}

		property double Y
		{
			double get()
			{
				return y;
			}
			void set(double value)
			{
				y = value;
			}
		}

		property double Width
		{
			double get()
			{
				return width;
			}
			void set(double value)
			{
				width = value;
			}
		}

		property double Height
		{
			double get()
			{
				return height;
			}
			void set(double value)
			{
				height = value;
			}
		}
	};

	public value struct BLBox sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double x0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double y0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double x1;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double y1;

	public:

		BLBox(double x0, double y0, double x1, double y1)
			: x0(x0), y0(y0), x1(x1), y1(y1)
		{
		}

	public:

		String^ ToString() override
		{
			return String::Format("X0={0:0.00}, Y0={1:0.00}, X1={2:0.00}, Y1={3:0.00}", X0, Y0, X1, Y1);
		}

	public:

		property double X0
		{
			double get()
			{
				return x0;
			}
			void set(double value)
			{
				x0 = value;
			}
		}

		property double Y0
		{
			double get()
			{
				return y0;
			}
			void set(double value)
			{
				y0 = value;
			}
		}

		property double X1
		{
			double get()
			{
				return x1;
			}
			void set(double value)
			{
				x1 = value;
			}
		}

		property double Y1
		{
			double get()
			{
				return y1;
			}
			void set(double value)
			{
				y1 = value;
			}
		}
	};

	public value struct BLLine sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double x0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double y0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double x1;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double y1;

	public:

		BLLine(double x0, double y0, double x1, double y1)
			: x0(x0), y0(y0), x1(x1), y1(y1)
		{
		}

	public:

		String^ ToString() override
		{
			return String::Format("X0={0:0.00}, Y0={1:0.00}, X1={2:0.00}, Y1={2:0.00}", X0, Y0, X1, Y1);
		}

	public:

		property double X0
		{
			double get()
			{
				return x0;
			}
			void set(double value)
			{
				x0 = value;
			}
		}

		property double Y0
		{
			double get()
			{
				return y0;
			}
			void set(double value)
			{
				y0 = value;
			}
		}

		property double X1
		{
			double get()
			{
				return x1;
			}
			void set(double value)
			{
				x1 = value;
			}
		}

		property double Y1
		{
			double get()
			{
				return y1;
			}
			void set(double value)
			{
				y1 = value;
			}
		}
	};

	public value struct BLTriangle sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double x0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double y0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double x1;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double y1;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double x2;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double y2;

	public:

		BLTriangle(double x0, double y0, double x1, double y1, double x2, double y2)
			: x0(x0), y0(y0), x1(x1), y1(y1), x2(x2), y2(y2)
		{
		}

	public:

		String^ ToString() override
		{
			return String::Format("X0={0:0.00}, Y0={1:0.00}, X1={2:0.00}, Y1={3:0.00}, X2={4:0.00}, Y2={5:0.00}", X0, Y0, X1, Y1, X2, Y2);
		}

	public:

		property double X0
		{
			double get()
			{
				return x0;
			}
			void set(double value)
			{
				x0 = value;
			}
		}

		property double Y0
		{
			double get()
			{
				return y0;
			}
			void set(double value)
			{
				y0 = value;
			}
		}

		property double X1
		{
			double get()
			{
				return x1;
			}
			void set(double value)
			{
				x1 = value;
			}
		}

		property double Y1
		{
			double get()
			{
				return y1;
			}
			void set(double value)
			{
				y1 = value;
			}
		}

		property double X2
		{
			double get()
			{
				return x2;
			}
			void set(double value)
			{
				x2 = value;
			}
		}

		property double Y2
		{
			double get()
			{
				return y2;
			}
			void set(double value)
			{
				y2 = value;
			}
		}
	};

	public value struct BLRoundRect sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double x;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double y;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double width;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double height;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double radiusX;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double radiusY;

	public:

		BLRoundRect(double x, double y, double width, double height, double radius)
			: x(x), y(y), width(width), height(height), radiusX(radius), radiusY(radius)
		{
		}

		BLRoundRect(double x, double y, double width, double height, double radiusX, double radiusY)
			: x(x), y(y), width(width), height(height), radiusX(radiusX), radiusY(radiusY)
		{
		}

	public:

		String^ ToString() override
		{
			return String::Format("X={0:0.00}, Y={1:0}, Width={2:0.00}, Height={3:0.00}, RadiusX={4:0.00}, RadiusY={5:0.00}", X, Y, Width, Height, RadiusX, RadiusY);
		}

	public:

		property double X
		{
			double get()
			{
				return x;
			}
			void set(double value)
			{
				x = value;
			}
		}

		property double Y
		{
			double get()
			{
				return y;
			}
			void set(double value)
			{
				y = value;
			}
		}

		property double Width
		{
			double get()
			{
				return width;
			}
			void set(double value)
			{
				width = value;
			}
		}

		property double Height
		{
			double get()
			{
				return height;
			}
			void set(double value)
			{
				height = value;
			}
		}

		property double RadiusX
		{
			double get()
			{
				return radiusX;
			}
			void set(double value)
			{
				radiusX = value;
			}
		}

		property double RadiusY
		{
			double get()
			{
				return radiusY;
			}
			void set(double value)
			{
				radiusY = value;
			}
		}
	};

	public value struct BLCircle sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double centerX;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double centerY;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double radius;

	public:

		BLCircle(double centerX, double centerY, double radius)
			: centerX(centerX), centerY(centerY), radius(radius)
		{
		}

	public:

		virtual String^ ToString() override
		{
			return String::Format("CenterX={0:0.00}, CenterY={1:0.00}, Radius={2:0.00}", CenterX, CenterY, Radius);
		}

	public:

		property double CenterX
		{
			double get()
			{
				return centerX;
			}
			void set(double value)
			{
				centerX = value;
			}
		}

		property double CenterY
		{
			double get()
			{
				return centerY;
			}
			void set(double value)
			{
				centerY = value;
			}
		}

		property double Radius
		{
			double get()
			{
				return radius;
			}
			void set(double value)
			{
				radius = value;
			}
		}
	};

	public value struct BLEllipse sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double centerX;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double centerY;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double radiusX;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double radiusY;

	public:

		BLEllipse(double centerX, double centerY, double radiusX, double radiusY)
			: centerX(centerX), centerY(centerY), radiusX(radiusX), radiusY(radiusY)
		{
		}

	public:

		virtual String^ ToString() override
		{
			return String::Format("CenterX={0:0.00}, CenterY={1:0.00}, RadiusX={2:0.00}, RadiusY={3:0.00}", CenterX, CenterY, RadiusX, RadiusY);
		}

	public:

		property double CenterX
		{
			double get()
			{
				return centerX;
			}
			void set(double value)
			{
				centerX = value;
			}
		}

		property double CenterY
		{
			double get()
			{
				return centerY;
			}
			void set(double value)
			{
				centerY = value;
			}
		}

		property double RadiusX
		{
			double get()
			{
				return radiusX;
			}
			void set(double value)
			{
				radiusX = value;
			}
		}

		property double RadiusY
		{
			double get()
			{
				return radiusY;
			}
			void set(double value)
			{
				radiusY = value;
			}
		}
	};

	public value struct BLArc sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double centerX;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double centerY;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double radiusX;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double radiusY;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double start;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double sweep;

	public:

		BLArc(double centerX, double centerY, double radiusX, double radiusY, double start, double sweep)
			: centerX(centerX), centerY(centerY), radiusX(radiusX), radiusY(radiusY), start(start), sweep(sweep)
		{
		}

	public:

		virtual String^ ToString() override
		{
			return String::Format("CenterX={0:0.00}, CenterY={1:0.00}, RadiusX={2:0.00}, RadiusY={3:0.00}, Start={4:0.00}, Sweep={5:0.00}", CenterX, CenterY, RadiusX, RadiusY, Start, Sweep);
		}

	public:

		property double CenterX
		{
			double get()
			{
				return centerX;
			}
			void set(double value)
			{
				centerX = value;
			}
		}

		property double CenterY
		{
			double get()
			{
				return centerY;
			}
			void set(double value)
			{
				centerY = value;
			}
		}

		property double RadiusX
		{
			double get()
			{
				return radiusX;
			}
			void set(double value)
			{
				radiusX = value;
			}
		}

		property double RadiusY
		{
			double get()
			{
				return radiusY;
			}
			void set(double value)
			{
				radiusY = value;
			}
		}

		property double Start
		{
			double get()
			{
				return start;
			}
			void set(double value)
			{
				start = value;
			}
		}

		property double Sweep
		{
			double get()
			{
				return sweep;
			}
			void set(double value)
			{
				sweep = value;
			}
		}
	};
}