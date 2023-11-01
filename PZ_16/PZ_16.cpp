#include <windows.h>
#include "MathLibary.h"
#include <string>
#include <iostream>
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    HINSTANCE hInst;
    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
    WNDCLASSEX wcex;
    HWND hWnd;
    MSG msg;


    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"Win32App";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, L"Ошибка регистрации окна!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hWnd = CreateWindowEx(0, L"Win32App", L"ПЗ 16",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, NULL, NULL, hInstance, NULL);

    if (hWnd == NULL) {
        MessageBox(NULL, L"Ошибка создания окна!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hBtn;
    static HWND hEdit1;
    static HWND hEditZnak;
    static HWND hEdit3;
    static HWND hEditResul;

    LPWSTR s1 = new WCHAR[100];
    LPWSTR s2 = new WCHAR[100];
    switch (message) {
    case WM_CREATE:
        hBtn = CreateWindow(L"button", L"Выполнить",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            70, 150, 120, 30, hWnd, 0, (HINSTANCE)lParam, NULL);
        hEdit1 = CreateWindow(L"edit", L" ",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 70, 100, 50, 20,
            hWnd, 0, (HINSTANCE)lParam, NULL);
        hEditZnak = CreateWindow(L"edit", L"+",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 125, 100, 20, 20,
            hWnd, 0, (HINSTANCE)lParam, NULL);
        hEdit3 = CreateWindow(L"edit", L" ",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 150, 100, 50, 20,
            hWnd, 0, (HINSTANCE)lParam, NULL);
        hEditResul = CreateWindow(L"edit", L"=",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 210, 100, 100, 20,
            hWnd, 0, (HINSTANCE)lParam, NULL);
        ShowWindow(hBtn, SW_SHOWNORMAL);
        break;
    case WM_COMMAND:

        if (lParam == (LPARAM)hBtn) {
            GetWindowText(hEdit1, s1, 100);
            GetWindowText(hEdit3, s2, 100);
            WCHAR operatorText[2];
            GetWindowText(hEditZnak, operatorText, 2);


            double result = 0.0;
            if (operatorText[0] == L'+') {
                result = MathLib::Arithmetic::Add(std::stod(s1), std::stod(s2));
            }
            else if (operatorText[0] == L'-') {
                result = MathLib::Arithmetic::Substruct(std::stod(s1), std::stod(s2));
            }
            else if (operatorText[0] == L'*') {
                result = MathLib::Arithmetic::Multiply(std::stod(s1), std::stod(s2));
            }
            else if (operatorText[0] == L'/') {
                result = MathLib::Arithmetic::Devide(std::stod(s1), std::stod(s2));
            }
            std::wstring resultSttr = std::to_wstring(result);
            SetWindowText(hEditResul, resultSttr.c_str());

            // Далее вы можете что-то сделать с результатом, например, отобразить его в другом текстовом поле.
        }



        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MOVE:
        MessageBox(hWnd, L"Окно было перемещено!", L"Смс-ка", MB_OK | MB_ICONINFORMATION);
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(144, 238, 144)));
        RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
        break;
    case WM_ACTIVATE:
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(173, 216, 230)));
        RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
        break;
    case WM_RBUTTONDBLCLK:
        MessageBox(hWnd, L"Ну нажал так нажал!", L"Смс-ка", MB_OK | MB_ICONINFORMATION);
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(240, 128, 128)));
        RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}