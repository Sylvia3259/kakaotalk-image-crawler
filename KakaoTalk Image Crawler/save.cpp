#include "pch.h"
using namespace Gdiplus;
using namespace Gdiplus::DllExports;

#pragma data_seg(".shared")
WCHAR szSavePath[1024] = L"";
#pragma data_seg()
#pragma comment(linker, "/SECTION:.shared,RWS")

GpStatus SaveImageToFile(GpImage* image, LPCWSTR lpszFilename, LPCWSTR format) {
	static int count = 1;
	WCHAR path[100];
	CLSID png;
	swprintf_s(path, L"D:\\test\\test%d.png", count++);
	CLSIDFromString(L"{557CF406-1A04-11D3-9A73-0000F81EF32E}", &png);
	return GdipSaveImageToFile(image, path, &png, NULL);
}

extern "C" _declspec(dllexport) LPCWSTR GetSavePath() {
	return szSavePath;
}

extern "C" _declspec(dllexport) void SetSavePath(LPCWSTR lpszNewSavePath) {
	wcscpy_s(szSavePath, lpszNewSavePath);
}
