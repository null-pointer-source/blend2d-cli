#pragma once

#include "api.h"
#include "object.h"
#include "geometry.h"
#include "matrix.h"
#include "rgba.h"

using namespace System;
using namespace System::Diagnostics;

#define GradientStop(source) (::BLGradientStop*)(source)

namespace Blend2D
{
	//! Gradient type.
	public enum class BLGradientType : UInt32
	{
		//! Linear gradient type.
		Linear = BL_GRADIENT_TYPE_LINEAR,
		//! Radial gradient type.
		Radial = BL_GRADIENT_TYPE_RADIAL,
		//! Conical gradient type.
		Conical = BL_GRADIENT_TYPE_CONICAL,
	};

	//! Gradient data index.
	public enum class BLGradientValue : UInt32
	{
		//! x0 - start 'x' for Linear/Radial and center 'x' for Conical.
		X0 = BL_GRADIENT_VALUE_RADIAL_R0,
		//! y0 - start 'y' for Linear/Radial and center 'y' for Conical.
		Y0 = BL_GRADIENT_VALUE_COMMON_Y0,
		//! x1 - end 'x' for Linear/Radial.
		X1 = BL_GRADIENT_VALUE_COMMON_X1,
		//! y1 - end 'y' for Linear/Radial.
		Y1 = BL_GRADIENT_VALUE_COMMON_Y1,
		//! Radial gradient r0 radius.
		R0 = BL_GRADIENT_VALUE_RADIAL_R0,
		//! Conical gradient angle.
		Angle = BL_GRADIENT_VALUE_CONICAL_ANGLE,
	};

	public value struct BLLinearGradientValues sealed
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

		BLLinearGradientValues(double x0, double y0, double x1, double y1)
			: x0(x0), y0(y0), x1(x1), y1(y1)
		{
		}

	public:

		String^ ToString() override
		{
			return String::Format("X0={0:0.00}, Y0={1:0.00}, X1={2:0.00}, Y1={3:0.00}", x0, y0, x1, y1);
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

	public value struct BLRadialGradientValues sealed
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
		double r0;

	public:

		BLRadialGradientValues(double x0, double y0, double x1, double y1, double r0)
			: x0(x0), y0(y0), x1(x1), y1(y1), r0(r0)
		{
		}

	public:

		String^ ToString() override
		{
			return String::Format("X0={0:0.00}, Y0={1:0.00}, X1={2:0.00}, Y1={3:0.00}, R0={4:0.00}", x0, y0, x1, y1, r0);
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

		property double R0
		{
			double get()
			{
				return r0;
			}
			void set(double value)
			{
				r0 = value;
			}
		}
	};

	public value struct BLConicalGradientValues sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double x0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double y0;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double angle;

	public:

		BLConicalGradientValues(double x0, double y0, double angle)
			: x0(x0), y0(y0), angle(angle)
		{
		}

	public:

		String^ ToString() override
		{
			return String::Format("X0={0:0.00}, Y0={1:0.00}, Angle={2:0.00}", x0, y0, angle);
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

		property double Angle
		{
			double get()
			{
				return angle;
			}
			void set(double value)
			{
				angle = value;
			}
		}
	};

	public value struct BLGradientStop sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double offset;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLRgba64 rgba;

	public:

		BLGradientStop(double offset, BLRgba32 rgba32)
			: offset(offset)
		{
			rgba.Reset(rgba32);
		}

		BLGradientStop(double offset, BLRgba64 rgba64)
			: offset(offset)
		{
			rgba.Reset(rgba64);
		}

	internal:

		BLGradientStop(const ::BLGradientStop& other)
		{
			offset = other.offset;
			rgba.value = other.rgba.value;
		}

	public:

		String^ ToString() override
		{
			return String::Format("Offset={0:0.00}, A=0x{1:X4}, R=0x{2:X4}, G=0x{3:X4}, B=0x{4:X4}", offset, rgba.a, rgba.r, rgba.g, rgba.b);
		}

	public:

		void Reset()
		{
			offset = 0.0;
			rgba.Reset();
		}

		void Reset(double offset, BLRgba32 rgba32)
		{
			offset = offset;
			rgba.Reset(rgba32);
		}

		void Reset(double offset, BLRgba64 rgba64)
		{
			offset = offset;
			rgba.Reset(rgba64);
		}
	};

	public ref class BLGradient : public BLObject
	{
	private:

		typedef ::BLGradient ImplType;

	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLObjectPointer<ImplType> impl;

	public:

		BLGradient()
			: BLObject()
		{
		}

		BLGradient(BLLinearGradientValues values)
			: BLObject()
		{
			Pin(BLLinearGradientValues, pValues, values);

			CheckResult(blGradientInitAs(this, (uint32_t)BLGradientType::Linear, pValues, (uint32_t)BLExtendMode::Pad, nullptr, 0, nullptr));
		}

		BLGradient(BLLinearGradientValues values, BLExtendMode extendMode)
			: BLObject()
		{
			Pin(BLLinearGradientValues, pValues, values);

			CheckResult(blGradientInitAs(this, (uint32_t)BLGradientType::Linear, pValues, (uint32_t)extendMode, nullptr, 0, nullptr));
		}

		BLGradient(BLRadialGradientValues values)
			: BLObject()
		{
			Pin(BLRadialGradientValues, pValues, values);

			CheckResult(blGradientInitAs(this, (uint32_t)BLGradientType::Radial, pValues, (uint32_t)BLExtendMode::Pad, nullptr, 0, nullptr));
		}

		BLGradient(BLRadialGradientValues values, BLExtendMode extendMode)
			: BLObject()
		{
			Pin(BLRadialGradientValues, pValues, values);

			CheckResult(blGradientInitAs(this, (uint32_t)BLGradientType::Radial, pValues, (uint32_t)extendMode, nullptr, 0, nullptr));
		}

		BLGradient(BLConicalGradientValues values)
			: BLObject()
		{
			Pin(BLConicalGradientValues, pValues, values);

			CheckResult(blGradientInitAs(this, (uint32_t)BLGradientType::Conical, pValues, (uint32_t)BLExtendMode::Pad, nullptr, 0, nullptr));
		}

		BLGradient(BLConicalGradientValues values, BLExtendMode extendMode)
			: BLObject()
		{
			Pin(BLConicalGradientValues, pValues, values);

			CheckResult(blGradientInitAs(this, (uint32_t)BLGradientType::Conical, pValues, (uint32_t)extendMode, nullptr, 0, nullptr));
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
			CheckResult(blGradientReset(this));
		}

		void Shrink()
		{
			CheckResult(blGradientShrink(this));
		}

		void Reserve(size_t count)
		{
			CheckResult(blGradientReserve(this, count));
		}

	public:

		// Gradient Stops

		void ResetStops()
		{
			CheckResult(blGradientResetStops(this));
		}

		void AssignStops(array<BLGradientStop>^ stops)
		{
			if (stops->Length > 0)
			{
				Pin(BLGradientStop, pStops, stops[0]);

				CheckResult(blGradientAssignStops(this, GradientStop(pStops), stops->Length));
			}

			CheckResult(blGradientResetStops(this));
		}

		void AddStop(double offset, BLRgba32 rgba32)
		{
			CheckResult(blGradientAddStopRgba32(this, offset, rgba32.value));
		}

		void AddStop(double offset, BLRgba64 rgba64)
		{
			CheckResult(blGradientAddStopRgba64(this, offset, rgba64.value));
		}

		void RemoveStop(size_t index)
		{
			CheckResult(blGradientRemoveStop(this, index));
		}

		void RemoveStopByOffset(double offset)
		{
			CheckResult(blGradientRemoveStopByOffset(this, offset, false));
		}

		void RemoveStopByOffset(double offset, bool all)
		{
			CheckResult(blGradientRemoveStopByOffset(this, offset, all));
		}

		void RemoveStopByOffset(double offsetMin, double offsetMax)
		{
			CheckResult(blGradientRemoveStopsFromTo(this, offsetMin, offsetMax));
		}

		void RemoveStops(BLRange range)
		{
			CheckResult(blGradientRemoveStops(this, range.start, range.end));
		}

		void ReplaceStop(size_t index, double offset, BLRgba32 rgba32)
		{
			CheckResult(blGradientReplaceStopRgba32(this, index, offset, rgba32.value));
		}

		void ReplaceStop(size_t index, double offset, BLRgba64 rgba64)
		{
			CheckResult(blGradientReplaceStopRgba64(this, index, offset, rgba64.value));
		}

		size_t IndexOfStop(double offset)
		{
			return blGradientIndexOfStop(this, offset);
		}

		BLGradientStop StopAt(size_t index)
		{
			return BLGradientStop(impl->stopAt(index));
		}

	public:

		// Transformations

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

		void ApplyMatrixOp(BLMatrix2DOp opType, const void* opData)
		{
			CheckResult(blGradientApplyMatrixOp(this, (uint32_t)opType, opData));
		}

		void ApplyMatrixOpV(BLMatrix2DOp opType, double v1, double v2)
		{
			double opData[] = { v1, v2 };

			CheckResult(blGradientApplyMatrixOp(this, (uint32_t)opType, opData));
		}

		void ApplyMatrixOpV(BLMatrix2DOp opType, double v1, double v2, double v3)
		{
			double opData[] = { v1, v2, v3 };

			CheckResult(blGradientApplyMatrixOp(this, (uint32_t)opType, opData));
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

		property BLGradientType Type
		{
			BLGradientType get()
			{
				return (BLGradientType)impl->type();
			}
			void set(BLGradientType value)
			{
				impl->setType((uint32_t)value);
			}
		}

		property BLExtendMode ExtendMode
		{
			BLExtendMode get()
			{
				return (BLExtendMode)impl->extendMode();
			}
			void set(BLExtendMode value)
			{
				impl->setExtendMode((uint32_t)value);
			}
		}

		property double default[BLGradientValue]
		{
			double get(BLGradientValue index)
			{
				return impl->value((size_t)index);
			}
			void set(BLGradientValue index, double value)
			{
				impl->setValue((size_t)index, value);
			}
		}

		property double X0
		{
			double get()
			{
				return impl->x0();
			}
			void set(double value)
			{
				impl->setX0(value);
			}
		}

		property double Y0
		{
			double get()
			{
				return impl->y0();
			}
			void set(double value)
			{
				impl->setY0(value);
			}
		}

		property double X1
		{
			double get()
			{
				return impl->x1();
			}
			void set(double value)
			{
				impl->setX1(value);
			}
		}

		property double Y1
		{
			double get()
			{
				return impl->y1();
			}
			void set(double value)
			{
				impl->setY1(value);
			}
		}

		property double R0
		{
			double get()
			{
				return impl->r0();
			}
			void set(double value)
			{
				impl->setR0(value);
			}
		}

		property double Angle
		{
			double get()
			{
				return impl->angle();
			}
			void set(double value)
			{
				impl->setAngle(value);
			}
		}

		property bool HasMatrix
		{
			bool get()
			{
				return impl->hasMatrix();
			}
		}

		property BLMatrix2DType MatrixType
		{
			BLMatrix2DType get()
			{
				return (BLMatrix2DType)impl->matrixType();
			}
		}

		property BLMatrix2D Matrix
		{
			BLMatrix2D get()
			{
				return BLMatrix2D(impl->matrix());
			}
			void set(BLMatrix2D value)
			{
				Pin(BLMatrix2D, pMatrix, value);

				ApplyMatrixOp(BLMatrix2DOp::Assign, pMatrix);
			}
		}

		property array<BLGradientStop>^ Stops
		{
			array<BLGradientStop>^ get()
			{
				return ConvertToArray<BLGradientStop>(impl->stops(), impl->size());
			}
		}
	};
}