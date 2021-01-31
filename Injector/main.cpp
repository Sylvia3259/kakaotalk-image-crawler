#include <iostream>
#include <string>
#include <Windows.h>
#include <BlackBone/Process/Process.h>
using namespace std;
using namespace blackbone;

wstring ExePath() {
    WCHAR buffer[1024];
    GetModuleFileName(NULL, buffer, 1024);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}

int main(int argc, char* argv[]) {
	Process process;
	process.Attach(L"KakaoTalk.exe");
	process.mmap().MapImage(ExePath() + L"\\KakaoTalk Image Downloader.dll");
	process.Detach();
}
