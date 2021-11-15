#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>

int _declspec(dllimport) InitCEF();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdShow, int nCmdShow)
{
    return InitCEF();
}
