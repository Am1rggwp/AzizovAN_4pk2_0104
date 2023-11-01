#include "framework.h"
#include "PZ_15.h"
#define MAX_LOADSTRING 100
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE
	hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PZ15, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PZ15));
	MSG msg;
	HDC hDC; // Контекст устройства
	PAINTSTRUCT ps;
	RECT rect;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}


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
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PZ15));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PZ15);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance,
		nullptr);
	if (!hWnd)
	{
		return FALSE;
	}
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
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rect;

		GetClientRect(hWnd, &rect);
		HFONT hFont = CreateFont(
			20, // Высота шрифта
			0, // Ширина символов (0 - авто)
			0, // Угол наклона (0 - нормальный)
			0, // Угол поворота (0 - нормальный)
			FW_NORMAL, // Толщина шрифта (FW_NORMAL - нормальный)
			FALSE, // Курсив
			FALSE, // Подчеркивание
			FALSE, // Зачеркивание
			ANSI_CHARSET, // Набор символов
			OUT_TT_PRECIS, // Точность вывода
			CLIP_DEFAULT_PRECIS, // Точность отсечения
			ANTIALIASED_QUALITY, // Качество шрифта
			FF_MODERN, // Семейство шрифта
			L"Calibry" // Имя шрифта
		);

		// Выбор созданного шрифта
		HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
		//цвет текста
		SetTextColor(hdc, RGB(255, 255, 255));
		//
		SetBkColor(hdc, RGB(76, 121, 131));
		// вывыод текста 
		DrawText(hdc, TEXT("ЭТООООООООО PZ_15"), -1, &rect, DT_SINGLELINE |
			DT_CENTER | DT_VCENTER);
		// Восстанавление предыдущего шрифта
		SelectObject(hdc, hOldFont);
		// Удаление созданного шрифта
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);

	}
	break;
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_ACTIVE || LOWORD(wParam) == WA_CLICKACTIVE)
		{
			Backgr = RGB(191, 21, 92); // Цвет при активации окна
		}
		else
		{
			backgroundColor = RGB(200, 200, 200); // Цвет при деактивации окна
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_MOVE:
		backg = RGB(255, 0, 0); // Цвет при перемещении окна
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_RBUTTONDBLCLK:
		backgroundColor = RGB(0, 8, 255); // Цвет при двойном щелчке правой кнопкой мыши
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
}