#include "pch.h"
using namespace Gdiplus;
using namespace Gdiplus::DllExports;

GpStatus SaveImageToFile(GpImage* image, LPCWSTR lpszFilename, LPCWSTR format);

GpStatus(WINGDIPAPI* lpfnGdipCreateBitmapFromStream)(IStream*, GpBitmap**) = GdipCreateBitmapFromStream;
GpStatus(WINGDIPAPI* lpfnGdipCreateBitmapFromFile)(GDIPCONST WCHAR*, GpBitmap**) = GdipCreateBitmapFromFile;

GpStatus WINGDIPAPI MyGdipCreateBitmapFromStream(IStream* stream, GpBitmap** bitmap) {
	GpStatus status = lpfnGdipCreateBitmapFromStream(stream, bitmap);
	SaveImageToFile(*bitmap, L"", L"");
	return status;
}

GpStatus WINGDIPAPI MyGdipCreateBitmapFromFile(GDIPCONST WCHAR* filename, GpBitmap** bitmap) {
	GpStatus status = lpfnGdipCreateBitmapFromFile(filename, bitmap);
	SaveImageToFile(*bitmap, L"", L"");
	return status;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	if (DetourIsHelperProcess())
		return TRUE;

	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		DetourRestoreAfterWith();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)lpfnGdipCreateBitmapFromStream, MyGdipCreateBitmapFromStream);
		DetourAttach(&(PVOID&)lpfnGdipCreateBitmapFromFile, MyGdipCreateBitmapFromFile);
		DetourTransactionCommit();
		break;
	case DLL_PROCESS_DETACH:
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)lpfnGdipCreateBitmapFromStream, MyGdipCreateBitmapFromStream);
		DetourDetach(&(PVOID&)lpfnGdipCreateBitmapFromFile, MyGdipCreateBitmapFromFile);
		DetourTransactionCommit();
		break;
	}

	return TRUE;
}
