#include "stdafx.h"
#include "Win32Project1.h"
#include "windows.h"
#include <windowsX.h>
#include <winuser.h>
#include <commctrl.h>
#include <cstdlib>
#include <ctime>

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
#define MAX_LOADSTRING 100
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// The title bar text
// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
#define ID_5SECONDS 101
UINT TimmerID = 0;
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
int a, b, c, kq, point = 0;
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(NULL, IDI_ERROR);
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; // Store instance handle in our global variable
	hWnd = CreateWindowEx(0, szWindowClass, L"Brain War",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 400, 300, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	// set up our timer


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
HWND calculation;
HWND result;

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);
	HWND hwnd = CreateWindowEx(0, L"BUTTON", L"Start", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 150, 100, 40, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	calculation = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 100, 100, 40, hWnd, NULL, hInst, NULL);
	SendMessage(calculation, WM_SETFONT, WPARAM(hFont), TRUE);
	result = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 100, 70, 40, hWnd, NULL, hInst, NULL);
	SendMessage(result, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd = CreateWindowEx(0, L"STATIC", L"Question", WS_CHILD | WS_VISIBLE | SS_LEFT, 90, 70, 50, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd = CreateWindowEx(0, L"STATIC", L"Result", WS_CHILD | WS_VISIBLE | SS_LEFT, 200, 70, 50, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	case WM_TIMER:
	{
					 WCHAR *bufferKQ = NULL;
					 int sizeKQ;
					 int kq1;
					 sizeKQ = GetWindowTextLength(result);
					 bufferKQ = new WCHAR[sizeKQ + 1];
					 GetWindowText(result, bufferKQ, sizeKQ + 1);
					 kq1 = _wtof(bufferKQ);
					 if (sizeKQ == 0)
					 {
						 int msgboxID = MessageBox(
							 NULL,
							 (LPCWSTR)L"Time up",
							 (LPCWSTR)L"Game over",
							 MB_ICONINFORMATION | MB_RETRYCANCEL | MB_DEFBUTTON2
							 );
						 if (msgboxID == IDRETRY)
						 {
							 SetWindowText(calculation, NULL);
							 SetWindowText(result, NULL);
							 TimmerID = SetTimer(hWnd, ID_5SECONDS, 5 * 1000, NULL);
						 }
						 else
							 PostQuitMessage(0);
					 }
					
					 else if (kq1 == kq)
					 {
						 KillTimer(hWnd, TimmerID);
						 int msgboxID = MessageBox(
							 NULL,
							 (LPCWSTR)L"Right",
							 (LPCWSTR)L"Congratulation",
							 MB_ICONINFORMATION | MB_OKCANCEL | MB_DEFBUTTON2
							 );
						 if (msgboxID == IDCANCEL)
							 PostQuitMessage(0);
						 
					 }
					 else
					 {
						 KillTimer(hWnd, TimmerID);
						 int msgboxID = MessageBox(
							 NULL,
							 (LPCWSTR)L"Wrong, RETRY?",
							 (LPCWSTR)L"Game over",
							 MB_ICONINFORMATION | MB_RETRYCANCEL | MB_DEFBUTTON2
							 );
						 if (msgboxID == IDRETRY)
						 {
							 SetWindowText(calculation, NULL);
							 SetWindowText(result, NULL);
							 TimmerID = SetTimer(hWnd, ID_5SECONDS, 5 * 1000, NULL);
						 }
						 else 
							 PostQuitMessage(0);
					 }
					 KillTimer(hWnd, TimmerID);
	}
		
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	WCHAR *buffer = NULL;
	srand(time(NULL));
	a = rand() % 50 + 1;
	c = rand() % 3;
	b = rand() % 50 + 1;
	switch (id)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case IDC_BUTTON1:
	{
						buffer = new WCHAR[255];
						
						if (c == 0)
						{
							kq = a + b;
							swprintf(buffer, 255, L"%d + %d", a, b);
							SetWindowText(calculation, buffer);
						}
						else if (c == 1)
						{
							kq = a - b;
							swprintf(buffer, 255, L"%d - %d", a, b);
							SetWindowText(calculation, buffer);
						}
						else
						{
							kq = a*b;
							swprintf(buffer, 255, L"%d * %d", a, b);
							SetWindowText(calculation, buffer);
						}
						
	
						TimmerID = SetTimer(hWnd, ID_5SECONDS, 5 * 1000, NULL);
						break;
	}
		
	}
}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}
