#include "pch.h"
#include "api.h"
#include "object.h"

using namespace System;

namespace Blend2D
{
	BLObject::BLObject()
	{
		BLObjectPool::Add(this);
	}
}