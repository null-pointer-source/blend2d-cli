// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#pragma once

// Exclude rarely used parts of the windows headers
#define WIN32_LEAN_AND_MEAN

//Define Unicode
#ifndef UNICODE
#define UNICODE
#endif

// Common Public Headers
#include <vcclr.h>
#include <Windows.h>
#include <msclr\marshal.h>

// Blend2D Includes
#include "blend2d.h"

// Common Lib
#pragma comment (lib, "user32.lib")
#pragma comment( lib, "gdi32.lib" )

// Blend2D Lib
#if defined(_M_X64) || defined(__amd64__)
#if defined(BL_BUILD_DEBUG)
#pragma comment( lib, "blend2d_x64_debug.lib" )
#else
#pragma comment( lib, "blend2d_x64_release.lib" )
#endif
#else
#if defined(BL_BUILD_DEBUG)
#pragma comment( lib, "blend2d_x86_debug.lib" )
#else
#pragma comment( lib, "blend2d_x86_release.lib" )
#endif
#endif
