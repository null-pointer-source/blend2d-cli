#pragma once

#include "api.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;

namespace Blend2D
{
	public ref class BLControlBlt sealed
	{
	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLImage^ image = nullptr;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		Action<BLImage^, BLRectI>^ paint = nullptr;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		int state;

	public:

		BLControlBlt(Action<BLImage^, BLRectI>^ paint)
			: paint(paint), state(0)
		{
			if (paint == nullptr)
			{
				throw gcnew ArgumentNullException("paint");
			}
		}

		~BLControlBlt()
		{
			BLControlBlt::!BLControlBlt();
		}

		!BLControlBlt()
		{
			Cleanup();
		}

	public:

		void Paint(Control^ control)
		{
			if (state > 0)
			{
				throw gcnew InvalidOperationException("Invalid paint state.");
			}

			state++;

			try
			{
				Resize(control);
				PaintAndBlt(control);
			}
			finally
			{
				state--;
			}
		}

	private:

		void Resize(Control^ control)
		{
			if (control->Width > 0 || control->Height > 0)
			{
				if (image == nullptr)
				{
					image = gcnew BLImage(control);
				}
				else if (control->Width != image->Width || control->Height != image->Height)
				{
					delete image;
					image = gcnew BLImage(control);
				}
			}
			else
			{
				Cleanup();
			}
		}

		void PaintAndBlt(Control^ control)
		{
			PAINTSTRUCT ps;

			auto hwnd = (HWND)control->Handle.ToPointer();
			auto hdc = BeginPaint(hwnd, &ps);

			try
			{
				if (paint != nullptr && image != nullptr)
				{
					auto x = ps.rcPaint.left;
					auto y = ps.rcPaint.top;
					auto width = ps.rcPaint.right - ps.rcPaint.left;
					auto height = ps.rcPaint.bottom - ps.rcPaint.top;

					paint(image, BLRectI(x, y, width, height));
					BitBlt(hdc, x, y, width, height, image->hdc, x, y, SRCCOPY);
				}
			}
			finally
			{
				EndPaint(hwnd, &ps);
			}
		}

		void Cleanup()
		{
			if (image != nullptr)
			{
				delete image;
				image = nullptr;
			}
		}
	};
}
