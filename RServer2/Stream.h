#pragma once
#include "Include.h"

class CStream
{
public:
	CStream(VOID);
	~CStream(VOID);
private:
	BYTE *mBufferPointer;
	DWORD mLength;
public:
	BOOL SetBuffer(BYTE *buffer);
	BOOL ReadInt32(INT *data);
	BOOL ReadDWORD(DWORD *data);
	BOOL ReadDWORD_PTR(DWORD_PTR *data);
	BOOL ReadByte(BYTE *data);
	BOOL ReadBytes(BYTE *data, DWORD length);
	BOOL ReadFloat(FLOAT *data);
	BOOL ReadInt64(INT64 *data);
	BOOL ReadSHORT(SHORT *data);
	BOOL ReadUSHORT(USHORT *data);
	BOOL ReadBOOL(BOOL *data);
	BOOL WriteInt32(INT data);
	BOOL WriteDWORD(DWORD *data);
	BOOL WriteDWORD_PTR(DWORD_PTR *data);
	BOOL WriteByte(BYTE *data);
	BOOL WriteBytes(BYTE *data, DWORD length);
	BOOL WriteFloat(FLOAT *data);
	BOOL WriteInt64(INT64 *data);
	BOOL WriteSHORT(SHORT *data);
	BOOL WriteUSHORT(USHORT *data);
	BOOL WriteBOOL(BOOL *data);
	DWORD GetLength(VOID);
};

class CStreamSP
{
public:
	CStreamSP(VOID) { Stream = new CStream(); };
	~CStreamSP(VOID) { delete Stream; };

	CStream* operator->(VOID) { return Stream; };
	operator CStream*(VOID) { return Stream; };

private:
	CStream *Stream;
};