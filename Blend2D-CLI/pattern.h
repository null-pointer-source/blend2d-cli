#pragma once

#include "api.h"
#include "object.h"
#include "geometry.h"
#include "matrix.h"
#include "rgba.h"
#include "image.h"

using namespace System;
using namespace System::Diagnostics;

namespace Blend2D
{
	public ref class BLPattern sealed : public BLObject
	{
	private:

		typedef ::BLPattern ImplType;

	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLObjectPointer<ImplType> impl;

	public:

		BLPattern(BLImage^ image)
			: BLObject()
		{
			CheckResult(blPatternInitAs(this, image, nullptr, (uint32_t)BLExtendMode::Repeat, nullptr));
		}

		BLPattern(BLImage^ image, BLExtendMode extendMode)
			: BLObject()
		{
			CheckResult(blPatternInitAs(this, image, nullptr, (uint32_t)extendMode, nullptr));
		}

	internal:

		BLPattern()
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
			CheckResult(blPatternReset(this));
		}	
		
		void ResetArea()
		{
			CheckResult(blPatternReset(this));
		}

		void SetArea(BLRectI area)
		{
			Pin(BLRectI, pArea, area)

			CheckResult(blPatternSetArea(this, RectI(pArea)));
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
			CheckResult(blPatternApplyMatrixOp(this, (uint32_t)opType, opData));
		}

		void ApplyMatrixOpV(BLMatrix2DOp opType, double v1, double v2)
		{
			double opData[] = { v1, v2 };

			CheckResult(blPatternApplyMatrixOp(this, (uint32_t)opType, opData));
		}

		void ApplyMatrixOpV(BLMatrix2DOp opType, double v1, double v2, double v3)
		{
			double opData[] = { v1, v2, v3 };

			CheckResult(blPatternApplyMatrixOp(this, (uint32_t)opType, opData));
		}

	public:

		property bool IsNone
		{
			bool get()
			{
				return impl->isNone();
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

		property BLRectI Area
		{
			BLRectI get()
			{
				return BLRectI(impl->area());
			}
			void set(BLRectI value)
			{
				Pin(BLRectI, pArea, value);

				CheckResult(blPatternSetArea(this, RectI(pArea)));
			}
		}
	};
}