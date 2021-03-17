#pragma once

#include "pch.h"

using namespace System;
using namespace System::Diagnostics;
using namespace System::Runtime::InteropServices;

#define Pin(type, name, source) pin_ptr<type> name = &source;
#define ConvertWchar(name, source) pin_ptr<const wchar_t> name = PtrToStringChars(source)
#define ConvertChar(name, source) StringConvert name(source)

#define Range(source) (::BLRange*)(source)

namespace Blend2D
{
	//! Blend2D result code.
	public enum class BLResultCode : Int32
	{
		//! Successful result code.
		BL_SUCCESS = 0,

		BL_ERROR_START_INDEX = 0x00010000u,

		BL_ERROR_OUT_OF_MEMORY = 0x00010000u,  //!< Out of memory                 [ENOMEM].
		BL_ERROR_INVALID_VALUE,                //!< Invalid value/argument        [EINVAL].
		BL_ERROR_INVALID_STATE,                //!< Invalid state                 [EFAULT].
		BL_ERROR_INVALID_HANDLE,               //!< Invalid handle or file.       [EBADF].
		BL_ERROR_VALUE_TOO_LARGE,              //!< Value too large               [EOVERFLOW].
		BL_ERROR_NOT_INITIALIZED,              //!< Object not initialized.
		BL_ERROR_NOT_IMPLEMENTED,              //!< Not implemented               [ENOSYS].
		BL_ERROR_NOT_PERMITTED,                //!< Operation not permitted       [EPERM].

		BL_ERROR_IO,                           //!< IO error                      [EIO].
		BL_ERROR_BUSY,                         //!< Device or resource busy       [EBUSY].
		BL_ERROR_INTERRUPTED,                  //!< Operation interrupted         [EINTR].
		BL_ERROR_TRY_AGAIN,                    //!< Try again                     [EAGAIN].
		BL_ERROR_TIMED_OUT,                    //!< Timed out                     [ETIMEDOUT].
		BL_ERROR_BROKEN_PIPE,                  //!< Broken pipe                   [EPIPE].
		BL_ERROR_INVALID_SEEK,                 //!< File is not seekable          [ESPIPE].
		BL_ERROR_SYMLINK_LOOP,                 //!< Too many levels of symlinks   [ELOOP].
		BL_ERROR_FILE_TOO_LARGE,               //!< File is too large             [EFBIG].
		BL_ERROR_ALREADY_EXISTS,               //!< File/directory already exists [EEXIST].
		BL_ERROR_ACCESS_DENIED,                //!< Access denied                 [EACCES].
		BL_ERROR_MEDIA_CHANGED,                //!< Media changed                 [Windows::ERROR_MEDIA_CHANGED].
		BL_ERROR_READ_ONLY_FS,                 //!< The file/FS is read-only      [EROFS].
		BL_ERROR_NO_DEVICE,                    //!< Device doesn't exist          [ENXIO].
		BL_ERROR_NO_ENTRY,                     //!< Not found, no entry (fs)      [ENOENT].
		BL_ERROR_NO_MEDIA,                     //!< No media in drive/device      [ENOMEDIUM].
		BL_ERROR_NO_MORE_DATA,                 //!< No more data / end of file    [ENODATA].
		BL_ERROR_NO_MORE_FILES,                //!< No more files                 [ENMFILE].
		BL_ERROR_NO_SPACE_LEFT,                //!< No space left on device       [ENOSPC].
		BL_ERROR_NOT_EMPTY,                    //!< Directory is not empty        [ENOTEMPTY].
		BL_ERROR_NOT_FILE,                     //!< Not a file                    [EISDIR].
		BL_ERROR_NOT_DIRECTORY,                //!< Not a directory               [ENOTDIR].
		BL_ERROR_NOT_SAME_DEVICE,              //!< Not same device               [EXDEV].
		BL_ERROR_NOT_BLOCK_DEVICE,             //!< Not a block device            [ENOTBLK].

		BL_ERROR_INVALID_FILE_NAME,            //!< File/path name is invalid     [n/a].
		BL_ERROR_FILE_NAME_TOO_LONG,           //!< File/path name is too long    [ENAMETOOLONG].

		BL_ERROR_TOO_MANY_OPEN_FILES,          //!< Too many open files           [EMFILE].
		BL_ERROR_TOO_MANY_OPEN_FILES_BY_OS,    //!< Too many open files by OS     [ENFILE].
		BL_ERROR_TOO_MANY_LINKS,               //!< Too many symbolic links on FS [EMLINK].
		BL_ERROR_TOO_MANY_THREADS,             //!< Too many threads              [EAGAIN].
		BL_ERROR_THREAD_POOL_EXHAUSTED,        //!< Thread pool is exhausted and couldn't acquire the requested thread count.

		BL_ERROR_FILE_EMPTY,                   //!< File is empty (not specific to any OS error).
		BL_ERROR_OPEN_FAILED,                  //!< File open failed              [Windows::ERROR_OPEN_FAILED].
		BL_ERROR_NOT_ROOT_DEVICE,              //!< Not a root device/directory   [Windows::ERROR_DIR_NOT_ROOT].

		BL_ERROR_UNKNOWN_SYSTEM_ERROR,         //!< Unknown system error that failed to translate to Blend2D result code.

		BL_ERROR_INVALID_ALIGNMENT,            //!< Invalid data alignment.
		BL_ERROR_INVALID_SIGNATURE,            //!< Invalid data signature or header.
		BL_ERROR_INVALID_DATA,                 //!< Invalid or corrupted data.
		BL_ERROR_INVALID_STRING,               //!< Invalid string (invalid data of either UTF8, UTF16, or UTF32).
		BL_ERROR_DATA_TRUNCATED,               //!< Truncated data (more data required than memory/stream provides).
		BL_ERROR_DATA_TOO_LARGE,               //!< Input data too large to be processed.
		BL_ERROR_DECOMPRESSION_FAILED,         //!< Decompression failed due to invalid data (RLE, Huffman, etc).

		BL_ERROR_INVALID_GEOMETRY,             //!< Invalid geometry (invalid path data or shape).
		BL_ERROR_NO_MATCHING_VERTEX,           //!< Returned when there is no matching vertex in path data.

		BL_ERROR_NO_MATCHING_COOKIE,           //!< No matching cookie (BLContext).
		BL_ERROR_NO_STATES_TO_RESTORE,         //!< No states to restore (BLContext).

		BL_ERROR_IMAGE_TOO_LARGE,              //!< The size of the image is too large.
		BL_ERROR_IMAGE_NO_MATCHING_CODEC,      //!< Image codec for a required format doesn't exist.
		BL_ERROR_IMAGE_UNKNOWN_FILE_FORMAT,    //!< Unknown or invalid file format that cannot be read.
		BL_ERROR_IMAGE_DECODER_NOT_PROVIDED,   //!< Image codec doesn't support reading the file format.
		BL_ERROR_IMAGE_ENCODER_NOT_PROVIDED,   //!< Image codec doesn't support writing the file format.

		BL_ERROR_PNG_MULTIPLE_IHDR,            //!< Multiple IHDR chunks are not allowed (PNG).
		BL_ERROR_PNG_INVALID_IDAT,             //!< Invalid IDAT chunk (PNG).
		BL_ERROR_PNG_INVALID_IEND,             //!< Invalid IEND chunk (PNG).
		BL_ERROR_PNG_INVALID_PLTE,             //!< Invalid PLTE chunk (PNG).
		BL_ERROR_PNG_INVALID_TRNS,             //!< Invalid tRNS chunk (PNG).
		BL_ERROR_PNG_INVALID_FILTER,           //!< Invalid filter type (PNG).

		BL_ERROR_JPEG_UNSUPPORTED_FEATURE,     //!< Unsupported feature (JPEG).
		BL_ERROR_JPEG_INVALID_SOS,             //!< Invalid SOS marker or header (JPEG).
		BL_ERROR_JPEG_INVALID_SOF,             //!< Invalid SOF marker (JPEG).
		BL_ERROR_JPEG_MULTIPLE_SOF,            //!< Multiple SOF markers (JPEG).
		BL_ERROR_JPEG_UNSUPPORTED_SOF,         //!< Unsupported SOF marker (JPEG).

		BL_ERROR_FONT_NOT_INITIALIZED,         //!< Font doesn't have any data as it's not initialized.
		BL_ERROR_FONT_NO_MATCH,                //!< Font or font-face was not matched (BLFontManager).
		BL_ERROR_FONT_NO_CHARACTER_MAPPING,    //!< Font has no character to glyph mapping data.
		BL_ERROR_FONT_MISSING_IMPORTANT_TABLE, //!< Font has missing an important table.
		BL_ERROR_FONT_FEATURE_NOT_AVAILABLE,   //!< Font feature is not available.
		BL_ERROR_FONT_CFF_INVALID_DATA,        //!< Font has an invalid CFF data.
		BL_ERROR_FONT_PROGRAM_TERMINATED,      //!< Font program terminated because the execution reached the limit.

		BL_ERROR_INVALID_GLYPH                 //!< Invalid glyph identifier.
	};

	//! Extend mode.
	public enum class BLExtendMode : UInt32
	{
		//! Pad extend [default].
		Pad = BL_EXTEND_MODE_PAD,
		//! Repeat extend.
		Repeat = BL_EXTEND_MODE_REPEAT,
		//! Reflect extend.
		Reflect = BL_EXTEND_MODE_REFLECT,

		//! Alias to `BL_EXTEND_MODE_PAD`.
		PAD_X_PAD_Y = BL_EXTEND_MODE_PAD_X_PAD_Y,
		//! Alias to `BL_EXTEND_MODE_REPEAT`.
		REPEAT_X_REPEAT_Y = BL_EXTEND_MODE_REPEAT_X_REPEAT_Y,
		//! Alias to `BL_EXTEND_MODE_REFLECT`.
		REFLECT_X_REFLECT_Y = BL_EXTEND_MODE_REFLECT_X_REFLECT_Y,
		//! Pad X and repeat Y.
		PAD_X_REPEAT_Y = BL_EXTEND_MODE_PAD_X_REPEAT_Y,
		//! Pad X and reflect Y.
		PAD_X_REFLECT_Y = BL_EXTEND_MODE_PAD_X_REFLECT_Y,
		//! Repeat X and pad Y.
		REPEAT_X_PAD_Y = BL_EXTEND_MODE_REPEAT_X_PAD_Y,
		//! Repeat X and reflect Y.
		REPEAT_X_REFLECT_Y = BL_EXTEND_MODE_REPEAT_X_REFLECT_Y,
		//! Reflect X and pad Y.
		REFLECT_X_PAD_Y = BL_EXTEND_MODE_REFLECT_X_PAD_Y,
		//! Reflect X and repeat Y.
		REFLECT_X_REPEAT_Y = BL_EXTEND_MODE_REFLECT_X_REPEAT_Y,
	};

	public enum class BLFormat : UInt32
	{
		//! None or invalid pixel format.
		None = BL_FORMAT_NONE,
		//! 32-bit premultiplied ARGB pixel format (8-bit components).
		PRGB32 = BL_FORMAT_PRGB32,
		//! 32-bit (X)RGB pixel format (8-bit components, alpha ignored).
		XRGB32 = BL_FORMAT_XRGB32,
		//! 8-bit alpha-only pixel format.
		A8 = BL_FORMAT_A8,
	};

	public enum class BLTextEncoding : UInt32
	{
		//! UTF-8 encoding.
		UTF8 = BL_TEXT_ENCODING_UTF8,
		//! UTF-16 encoding (native endian).
		UTF16 = BL_TEXT_ENCODING_UTF16,
		//! UTF-32 encoding (native endian).
		UTF32 = BL_TEXT_ENCODING_UTF32,
		//! LATIN1 encoding (one byte per character).
		LATIN1 = BL_TEXT_ENCODING_LATIN1,
		//! Platform native `wchar_t` (or Windows `WCHAR`) encoding, alias to
		//! either UTF-32, UTF-16, or UTF-8 depending on `sizeof(wchar_t)`.
		WCHAR = BL_TEXT_ENCODING_WCHAR,
	};

	private ref class StringConvert sealed
	{
	private:

		IntPtr ptr;

	public:

		StringConvert(String^ string)
		{
			ptr = Marshal::StringToHGlobalAnsi(string);
		}

		~StringConvert()
		{
			StringConvert::!StringConvert();
		}

	protected:

		!StringConvert()
		{
			Marshal::FreeHGlobal(ptr);
		}

	public:

		operator const char* ()
		{
			return (const char*)ptr.ToPointer();
		}
	};


	public value struct BLRange sealed
	{
	internal:

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		size_t start;

		[DebuggerBrowsableAttribute(DebuggerBrowsableState::Never)]
		size_t end;

	public:

		BLRange(size_t start, size_t end)
			: start(start), end(end)
		{
		}
	};

	template<typename T>	
	extern array<T>^ ConvertToArray(const void* data, size_t count);

	extern BLResultCode CheckResult(BLResult result);
}