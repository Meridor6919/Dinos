#pragma warning(disable : 4996)
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#include <string>
#include "Dino.h"
#include "Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	RECT rect;
	HWND hwnd = GetDesktopWindow();
	GetWindowRect(hwnd, &rect);
	int X = rect.right - rect.left;
	int Y = rect.bottom - rect.top;

	float Gametime = 0.0f;
	float Clock = clock() / CLOCKS_PER_SEC;
	float speed;

	HWND MainWindowHwnd;
	MSG msg;
	
	GenerateWindow(hInstance, nCmdShow, "WindowClass_1", "Dinosaur", X, Y, MainWindowHwnd);
	InitializeInput();
	Dino D(MainWindowHwnd, X, Y);

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}

		Gametime = static_cast<float>(clock()) / 1000.0f - Clock;
		speed = Gametime / 10.0f + 8.0f;
		if (speed > 16.0f)
			speed = 16.0f;

		if (!D.Main(Gametime))
			D.Fail(Clock);
	}
	D.Delete();
	return msg.wParam;
}





// this function initializes and prepares Direct3D for use



