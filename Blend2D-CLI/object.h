#pragma once

#include "api.h"

using namespace System;
using namespace System::Diagnostics;
using namespace System::Collections::Generic;
using namespace System::Threading;

namespace Blend2D
{
	template <typename T>
	private ref class BLObjectPointer sealed
	{
	private:

		T* target = nullptr;

	public:

		BLObjectPointer()
		{
			target = new T();
		}

		~BLObjectPointer()
		{
			BLObjectPointer::!BLObjectPointer();
		}

	protected:

		!BLObjectPointer()
		{
			if (target != nullptr)
			{
				delete target;
				target = nullptr;
			}
		}

	public:

		T* operator -> ()
		{
			return target;
		}

		operator T* ()
		{
			return target;
		}
	};

	public ref class BLObject abstract
	{
	internal:

		BLObject();

		~BLObject()
		{
			BLObject::!BLObject();
		}

	protected:

		!BLObject()
		{
			Destroy();
		}

	protected:

		virtual void Destroy()
		{
		}
	};

	public ref class BLObjectPool sealed
	{
	private:

		[ThreadStaticAttribute]
		static BLObjectPool^ current = nullptr;

		Stack<BLObject^>^ stack;

	public:

		BLObjectPool()
		{
			stack = gcnew Stack<BLObject^>();

			if (current != nullptr)
			{
				throw gcnew InvalidOperationException("ivalid pool state");
			}

			current = this;
		}

		~BLObjectPool()
		{
			current = nullptr;
			BLObjectPool::!BLObjectPool();
		}

	protected:

		!BLObjectPool()
		{
			DisposeItems();
		}

	private:

		void DisposeItems()
		{
			if (stack != nullptr)
			{
				while (stack->Count > 0)
				{
					auto current = stack->Pop();
					delete current;
				}

				delete stack;
				stack = nullptr;
			}
		}

	internal:

		static void Add(BLObject^ item)
		{
			if (current != nullptr)
			{
				current->stack->Push(item);
			}
		}
	};
}