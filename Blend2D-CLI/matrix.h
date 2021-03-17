#pragma once

#include "api.h"
#include "object.h"
#include "geometry.h"

using namespace System;
using namespace System::Diagnostics;

#define Matrix2D(source) (::BLMatrix2D*)(source)

namespace Blend2D
{
	//! 2D matrix type that can be obtained by calling `BLMatrix2D::type()`.
	public enum class BLMatrix2DType : UInt32
	{
		//! Identity matrix.
		Identity = BL_MATRIX2D_TYPE_IDENTITY,
		//! Has translation part (the rest is like identity).
		Translate = BL_MATRIX2D_TYPE_TRANSLATE,
		//! Has translation and scaling parts.
		Scale = BL_MATRIX2D_TYPE_SCALE,
		//! Has translation and scaling parts, however scaling swaps X/Y.
		Swap = BL_MATRIX2D_TYPE_SWAP,
		//! Generic affine matrix.
		Affine = BL_MATRIX2D_TYPE_AFFINE,
		//! Invalid/degenerate matrix not useful for transformations.
		Invalid = BL_MATRIX2D_TYPE_INVALID,
	};

	//! 2D matrix data index.
	public enum class BLMatrix2DValue : UInt32
	{
		//! Value at index 0 - M00.
		Value00 = BL_MATRIX2D_VALUE_00,
		//! Value at index 1 - M01.
		Value01 = BL_MATRIX2D_VALUE_01,
		//! Value at index 2 - M10.
		Value10 = BL_MATRIX2D_VALUE_10,
		//! Value at index 3 - M11.
		Value11 = BL_MATRIX2D_VALUE_11,
		//! Value at index 4 - M20.
		Value20 = BL_MATRIX2D_VALUE_20,
		//! Value at index 5 - M21.
		Value21 = BL_MATRIX2D_VALUE_21,
	};

	//! 2D matrix operation.
	public enum class BLMatrix2DOp : UInt32
	{
		//! Reset matrix to identity (argument ignored, should be nullptr).
		Reset = BL_MATRIX2D_OP_RESET,
		//! Assign (copy) the other matrix.
		Assign = BL_MATRIX2D_OP_ASSIGN,

		//! Translate the matrix by [x, y].
		Translate = BL_MATRIX2D_OP_TRANSLATE,
		//! Scale the matrix by [x, y].
		Scale = BL_MATRIX2D_OP_SCALE,
		//! Skew the matrix by [x, y].
		Skew = BL_MATRIX2D_OP_SKEW,
		//! Rotate the matrix by the given angle about [0, 0].
		Rotate = BL_MATRIX2D_OP_ROTATE,
		//! Rotate the matrix by the given angle about [x, y].
		RotatePoint = BL_MATRIX2D_OP_ROTATE_PT,
		//! Transform this matrix by other `BLMatrix2D`.
		Transform = BL_MATRIX2D_OP_TRANSFORM,

		//! Post-translate the matrix by [x, y].
		PostTranslate = BL_MATRIX2D_OP_POST_TRANSLATE,
		//! Post-scale the matrix by [x, y].
		PostScale = BL_MATRIX2D_OP_POST_SCALE,
		//! Post-skew the matrix by [x, y].
		PostSkew = BL_MATRIX2D_OP_POST_SKEW,
		//! Post-rotate the matrix about [0, 0].
		PostRotate = BL_MATRIX2D_OP_POST_ROTATE,
		//! Post-rotate the matrix about a reference BLPoint.
		PostRotatePoint = BL_MATRIX2D_OP_POST_ROTATE_PT,
		//! Post-transform this matrix by other `BLMatrix2D`.
		PostTransform = BL_MATRIX2D_OP_POST_TRANSFORM,
	};

	public value struct BLMatrix2D sealed
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

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double m20;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		double m21;

	public:

		BLMatrix2D(double m00, double m01, double m10, double m11, double m20, double m21)
			: m00(m00), m01(m01), m10(m10), m11(m11), m20(m20), m21(m21)
		{
		}

	internal:

		BLMatrix2D(const ::BLMatrix2D& other)
		{
			m00 = other.m00;
			m01 = other.m01;
			m10 = other.m10;
			m11 = other.m11;
			m20 = other.m20;
			m21 = other.m21;
		}

	public:

		String^ ToString() override
		{
			return String::Format("M00={0:0.00}, M01={1:0.00}, M10={2:0.00}, M11={3:0.00}, M20={4:0.00}, M21={5:0.00}", m00, m01, m10, m11, m20, m21);
		}

	public:

		property BLMatrix2DType Type
		{
			BLMatrix2DType get()
			{
				Pin(BLMatrix2D, pMatrix, *this);

				return (BLMatrix2DType)blMatrix2DGetType(Matrix2D(pMatrix));
			}
		}

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

		property double M20
		{
			double get()
			{
				return m20;
			}
		}

		property double M21
		{
			double get()
			{
				return m21;
			}
		}
	};
}