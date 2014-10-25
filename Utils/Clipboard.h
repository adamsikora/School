/*
Adam Sikora
16.2.2014

*/

#ifndef CLIPBOARD_H
#define CLIPBOARD_H


#include "windows.h"
#include <direct.h>

#include <string>

void CopyToClipboard(std::string answer)
{
	const char* output = answer.c_str();
	const size_t len = strlen(output) + 1;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), output, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}

#endif //CLIPBOARD_H
