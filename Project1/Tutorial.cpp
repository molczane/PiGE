#include "Framework.h"
#include "Tutorial.h"
#include <string.h>

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TUTORIAL, szWindowClass, MAX_LOADSTRING);
	
	MyRegisterClass(hInstance);
	
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TUTORIAL));
	MSG msg;
	
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return static_cast <int>(msg.wParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TUTORIAL));
	wcex.hCursor = nullptr;
	wcex.hbrBackground = reinterpret_cast <HBRUSH>(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TUTORIAL);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;
	
	HWND hWnd = CreateWindowW(szWindowClass, szTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance,
			nullptr);
	/*HWND hWnd;
	int size = 150;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
								i * 150, j * 150, 150, 150,
								NULL, NULL, hInstance, NULL);
		}
	}*/
	
	if (!hWnd)
	{
		return FALSE;
	}
	
	// Set WS_EX_LAYERED on this window
	//SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	// Make this window 50% alpha
	//SetLayeredWindowAttributes(hWnd, 0, (255 * 50) / 100, LWA_ALPHA);
	// Show this window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				case IDM_ABOUT:
					DialogBox (hInst , MAKEINTRESOURCE ( IDD_ABOUTBOX ), hWnd, About );
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
			/*RECT rc;
			GetWindowRect(hWnd, &rc);
			OffsetRect(&rc, 20, 0);
			MoveWindow(hWnd, rc.left, rc.top,
			rc.right - rc.left, rc.bottom - rc.top, TRUE);*/
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_SIZE:
		{
			// get the size of the client area
			int clientWidth = LOWORD(lParam);
			int clientHeight = HIWORD(lParam);
			// get the size of the window
			RECT rc;
			GetWindowRect(hWnd, &rc);
			// modify the caption of the window
			TCHAR s[256];
			_stprintf_s(s, 256,
							_T(" Window 's size : %d x %d Client area 's size : %d x %d"),
							rc.right - rc.left, rc.bottom - rc.top,
							clientWidth, clientHeight);
			SetWindowText(hWnd, s);
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return static_cast <INT_PTR>(TRUE);
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return static_cast <INT_PTR>(TRUE);
		}
		break;
	}
	return static_cast <INT_PTR>(FALSE);
}