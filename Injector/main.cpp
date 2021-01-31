#include <iostream>
#include <filesystem>
#include <string>
#include <Windows.h>
#include <BlackBone/Process/Process.h>
using namespace std;
using namespace blackbone;

int main(int argc, char* argv[]) {
	Process process;
	process.Attach(L"KakaoTalk.exe");
	auto result = process.modules().Inject(
		filesystem::current_path().wstring() + L"\\KakaoTalk Image Downloader.dll"
	);
	if (!result) {
		cout << hex << uppercase;
		cout << "Failed to inject image (0x" << result.status << ")";
	}
	process.Detach();

	return 0;
}
