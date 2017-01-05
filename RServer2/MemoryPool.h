#pragma once
#include "Include.h"

template <class T, int ALLOC_BLOCK_SIZE = 50>
class CMemoryPool
{
public:

	static VOID* operator new(std::size_t allocLength)
	{
		assert(sizeof(T) == allocLength);
		assert(sizeof(T) > -sizeof(UCHAR*));

		if (!mFreePointer)
			allocBlock();
		UCHAR *ReturnPointer = mFreePointer;
		mFreePointer = *reinterpret_case<UCHAR**>(ReturnPointer);

		return ReturnPointer;
	}

	static VOID operator delete(VOID* deletePointer)
	{
		*reinterpret_cast<UCHAR**>(deletePointer) = mFreePointer;
		mFreePointer = static_cast<UCHAR*>(deletePointer);
	}
private:
	static VOID allocBlock()
	{
		mFreePointer = new UCHAR[sizeof(T) * ALLOC_BLOCK_SIZE];

		UCHAR **Current		= reinterpret_cast<UCHAR**>(mFreePointer);
		UCHAR *Next			= mFreePointer;

		for (INT i = 0; i < ALLOC_BLOCK_SIZE - 1; ++i)
		{
			Next += sizeof(T);
			*Current = Next;
			Current = reinterpret_cast<UCHAR**>(Next);
		}

		*Current = 0;
	}

private:
	sttic UCHAR		*mFreePointer;

protected:
	~CMemoryPool(){}
};

template <class T, int ALLOCK_blOCK_SIZE>
UCHAR* CMemoryPool<T, ALLOCK_BLOCK_SIZE>::mFreePointer;