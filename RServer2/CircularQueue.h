#pragma once
#include "Include.h"
template <class T>
class CCircularQueue
{
public:
	CCircularQueue(VOID)
	{
		ZeroMemory(mQueue, sizeof(mQueue));
		mQueueHead = mQueueTail = 0;
	}
	~CCircularQueue(VOID) {}
private:
	T		mQueue[MAX_QUEUE_LENGTH];
	DWORD	mQueueHead;
	DWORD	mQueueTail;

public:
	BOOL Begin(VOID)
	{
		ZeroMemory(mQueue, sizeof(mQueue));
		mQueueHead = mQueueTail = 00;
		return TRUE;
	}
	BOOL End(VOID) { return TRUE; }
	BOOL Push(T data)
	{
		DWORD TempTail = (mQueueTail + 1) % MAX_QUEUE_LENGTH;
		if (TempTail == mQueueHead)
			return FALSE;
		CopyMemory(&mQueue[TempTail], &data, sizeof(T));
		mQueueTail = TempTail;
		return TRUE;
	}
	BOOL Pop(T& data)
	{
		if (mQueueHead == mQueueTail)
			return FALSE;
		DWORD TempHead = (mQueueHead + 1) % MAX_QUEUE_LENGTH;
		CopyMemory(&data, &mQueue[TempHead], sizeof(T));
		mQueueHead = TempHead;
		return TRUE;
	}
	BOOL IsEmpty(VOID)
	{
		if (mQueueHead == mQueueTail) return TRUE;
		return FALSE;
	}
};
//À¸¹ò¹ò
