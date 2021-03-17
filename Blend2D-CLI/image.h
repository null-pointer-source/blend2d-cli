#pragma once

#include "api.h"
#include "object.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;

namespace Blend2D
{
	public ref class BLImageCodec sealed : public BLObject
	{
	private:

		typedef ::BLImageCodec ImplType;

	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLObjectPointer<ImplType> impl;

	public:

		BLImageCodec()
			: BLObject()
		{
		}

	private:

		BLImageCodec(const ImplType& other)
			: BLObject()
		{
			CheckResult(blVariantInitWeak(this, &other));
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

		void FindByName(String^ name)
		{
			ConvertChar(str, name);

			CheckResult(blImageCodecFindByName(this, str, name->Length, nullptr));;
		}

		void FindByExtension(String^ name)
		{
			ConvertChar(str, name);

			CheckResult(blImageCodecFindByExtension(this, str, name->Length, nullptr));;
		}

	public:

		static List<BLImageCodec^>^ BuiltInCodecs()
		{
			auto list = gcnew List<BLImageCodec^>();

			for (const auto& codec : ImplType::builtInCodecs().view())
			{
				list->Add(gcnew BLImageCodec(codec));
			}

			return list;
		}

	public:

		property String^ Name
		{
			String^ get()
			{
				return gcnew String(impl->name());
			}
		}

		property String^ MimeType
		{
			String^ get()
			{
				return gcnew String(impl->mimeType());
			}
		}

		property String^ Vendor
		{
			String^ get()
			{
				return gcnew String(impl->vendor());
			}
		}

		property String^ Extensions
		{
			String^ get()
			{
				return gcnew String(impl->extensions());
			}
		}
	};

	public ref class BLImage sealed : public BLObject
	{
	private:

		typedef ::BLImage ImplType;

	private:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BLObjectPointer<ImplType> impl;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		Bitmap^ sourceBitmap = nullptr;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		BitmapData^ sourceData = nullptr;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		HBITMAP bitmap = nullptr;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		HBITMAP oldBitmap = nullptr;

	internal:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		HDC hdc = nullptr;

	public:

		BLImage()
			: BLObject()
		{
		}

		BLImage(String^ fileName)
			: BLObject()
		{
			ReadFromFile(fileName);
		}

		BLImage(Bitmap^ bitmap)
			: BLObject()
		{
			InitFromBitmap(bitmap);
		}

		BLImage(int width, int height, BLFormat format)
			: BLObject()
		{
			CheckResult(blImageInitAs(this, width, height, (uint32_t)format));
		}

	internal:

		BLImage(Control^ control)
			: BLObject()
		{
			InitFromControl(control);
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
			if (sourceBitmap != nullptr && sourceData != nullptr)
			{
				sourceBitmap->UnlockBits(sourceData);
				sourceBitmap = nullptr;
				sourceData = nullptr;
			}

			if (hdc != nullptr && oldBitmap != nullptr)
			{
				SelectObject(hdc, oldBitmap);
				oldBitmap = nullptr;
			}

			if (bitmap != nullptr)
			{
				DeleteObject(bitmap);
				bitmap = nullptr;
			}

			if (hdc != nullptr)
			{
				DeleteDC(hdc);
				hdc = nullptr;
			}
		}

	public:

		void WriteToFile(String^ fileName)
		{
			ConvertChar(str, fileName);

			CheckResult(blImageWriteToFile(this, str, nullptr));
		}

		void WriteToFile(String^ fileName, BLImageCodec^ codec)
		{
			ConvertChar(str, fileName);

			CheckResult(blImageWriteToFile(this, str, codec));
		}

		void ReadFromFile(String^ fileName)
		{
			ConvertChar(str, fileName);

			CheckResult(blImageReadFromFile(this, str, nullptr));
		}

	private:

		void InitFromBitmap(Bitmap^ bitmap)
		{
			auto format = BLFormat::None;

			switch (bitmap->PixelFormat)
			{
			case PixelFormat::Format32bppArgb:
				format = BLFormat::XRGB32;
				break;

			case PixelFormat::Format32bppPArgb:
				format = BLFormat::PRGB32;
				break;

			default:
				throw gcnew InvalidOperationException("Format not supported.");
			}

			sourceBitmap = bitmap;
			sourceData = sourceBitmap->LockBits(System::Drawing::Rectangle(0, 0, sourceBitmap->Width, sourceBitmap->Height), ImageLockMode::ReadWrite, sourceBitmap->PixelFormat);

			CheckResult(blImageCreateFromData(this, sourceBitmap->Width, sourceBitmap->Height, (uint32_t)format, (void*)sourceData->Scan0, sourceData->Stride, nullptr, nullptr));
		}

		void InitFromControl(Control^ control)
		{
			auto hwnd = (HWND)control->Handle.ToPointer();
			auto source = GetDC(hwnd);
			auto width = control->Width;
			auto height = control->Height;
			auto stride = width * 4;

			try
			{
				BITMAPINFO bi;
				void* lpBitmapBits;

				ZeroMemory(&bi, sizeof(BITMAPINFO));
				bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				bi.bmiHeader.biWidth = width;
				bi.bmiHeader.biHeight = -height;
				bi.bmiHeader.biPlanes = 1;
				bi.bmiHeader.biBitCount = 32;
				bi.bmiHeader.biCompression = BI_RGB;

				hdc = CreateCompatibleDC(source);
				bitmap = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, &lpBitmapBits, nullptr, 0);

				if (bitmap != nullptr)
				{
					oldBitmap = (HBITMAP)SelectObject(hdc, bitmap);

					CheckResult(blImageCreateFromData(this, width, height, (uint32_t)BLFormat::PRGB32, lpBitmapBits, stride, nullptr, nullptr));
				}
				else
				{
					DeleteDC(hdc);

					throw gcnew InvalidOperationException("CreateDIBSection failed !");
				}
			}
			finally
			{
				ReleaseDC(hwnd, source);
			}
		}

	public:

		static operator Image ^ (BLImage^ image)
		{
			auto format = PixelFormat::Undefined;

			switch (image->Format)
			{
			case BLFormat::XRGB32:
				format = PixelFormat::Format32bppArgb;
				break;

			case BLFormat::PRGB32:
				format = PixelFormat::Format32bppPArgb;
				break;

			default:
				throw gcnew InvalidOperationException("Format not supported.");
			}

			auto bitmap = gcnew Bitmap(image->Width, image->Height, format);
			auto data = bitmap->LockBits(System::Drawing::Rectangle(0, 0, bitmap->Width, bitmap->Height), ImageLockMode::ReadWrite, bitmap->PixelFormat);
			memcpy((void*)data->Scan0, (void*)image->PixelData, image->Height * image->Stride);
			bitmap->UnlockBits(data);
			return bitmap;
		}

	public:

		property int Width
		{
			int get()
			{
				return impl->width();
			}
		}

		property int Height
		{
			int get()
			{
				return impl->height();
			}
		}

		property intptr_t Stride
		{
			intptr_t get()
			{
				return impl->impl->stride;
			}
		}

		property IntPtr PixelData
		{
			IntPtr get()
			{
				return (IntPtr)impl->impl->pixelData;
			}
		}

		property BLFormat Format
		{
			BLFormat get()
			{
				return (BLFormat)impl->format();
			}
		}
	};
}