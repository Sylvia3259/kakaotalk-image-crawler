#include <iostream>
#include <string>
#include <Windows.h>
#include <BlackBone/Process/Process.h>
using namespace std;
using namespace blackbone;

int main(int argc, char* argv[]) {
	WCHAR buffer[1024];
	GetModuleFileName(NULL, buffer, 1024);
	size_t pos = wstring(buffer).find_last_of(L"\\/");
	wstring currentPath = wstring(buffer).substr(0, pos);

	Process process;
	auto status = process.Attach(L"KakaoTalk.exe");
	if (!NT_SUCCESS(status)) {
		cout << hex << uppercase;
		cout << "Cannot attach to process (0x" << status << ")";
		return 1;
	}
	auto result = process.modules().Inject(
		currentPath + L"\\KakaoTalk Image Downloader.dll"
	);
	if (!result) {
		cout << hex << uppercase;
		cout << "Failed to inject image (0x" << result.status << ")";
		return 1;
	}
	process.Detach();

	return 0;
}
