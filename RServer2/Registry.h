#pragma once
#include "Include.h"
class CRegistry
{
public:
	CRegistry(VOID);
	virtual ~CRegistry(VOID);

public:
	BOOL Open(HKEY rootKey, LPCTSTR subKey);
	BOOL Close(VOID);

	BOOL CreateKey(HKEY rootKey, LPCTSTR subKey);
	BOOL DeleteKey(HKEY rootKey, LPCTSTR subKey);

	BOOL Setvalue(LPCTSTR valueName, LPCTSTR value);
	BOOL Setvalue(LPCTSTR valueName, DWORD value);
	BOOL SetvalueForMultiSz(LPCTSTR valueName, LPCTSTR value, DWORD byteLength);
	BOOL Getvalue(LPCTSTR valueName, LPCTSTR value, LPDWORD bufferLength);
	BOOL Getvalue(LPCTSTR valueName, LPDWORD value);

	BOOL Deletevalue(LPCTSTR valueName);
private:
	HKEY mRootKey;
	BOOL mIsOpened;
};

