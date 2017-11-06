#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib, "atls")

#include <windows.h>
#include <atlbase.h>
#include <atlhost.h>

TCHAR szClassName[] = TEXT("Window");
CComModule g_Module;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND	hBrowser;
	switch (msg)
	{
	case WM_CREATE:
		g_Module.Init(NULL, ((LPCREATESTRUCT)lParam)->hInstance);
		AtlAxWinInit();
		hBrowser = CreateWindow(TEXT(ATLAXWIN_CLASS),
			TEXT("mshtml:<html><html><head><meta http-equiv=\"X-UA-Compatible\" content=\"IE=11\"></head><body>Hello world!</body></html>"),
			WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, 0,
			((LPCREATESTRUCT)lParam)->hInstance,
			0);
		break;
	case WM_SIZE:
		MoveWindow(hBrowser, 0, 0, LOWORD(lParam), HIWORD(lParam), 1);
		break;
	case WM_DESTROY:
		AtlAxWinTerm();
		g_Module.Term();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		0,
		WndProc,
		0,
		0,
		hInstance,
		0,
		0,
		0,
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("WebBrowser"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
