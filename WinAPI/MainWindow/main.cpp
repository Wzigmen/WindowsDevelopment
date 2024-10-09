#include<Windows.h>

#define IDC_STATIC	1000 // 1) Создаем ResourceID для дочернего элемента
#define IDC_EDIT	1001
#define IDC_BUTTON	1002

CONST CHAR g_sz_WINDOW_CLASS[] = "Main Window"; // Имя класса окна

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow)
{
	//DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	// 1) Регистрация класса
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	//Appearance:
	/*wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;*/
	wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\cat.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\skeleton.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	//
	wClass.hCursor = (HCURSOR)LoadImage
	(
		hInstance,
		"Crystal Cursors\\Dark\\14_alternate_select.cur",
		IMAGE_CURSOR,
		LR_DEFAULTSIZE, 
		LR_DEFAULTSIZE, 
		LR_LOADFROMFILE
	);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;

	if (RegisterClassEx(&wClass) == NULL) {
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
	}

	// 2) Cоздание окна
	HWND hwnd = CreateWindowEx
		(
			NULL,
			g_sz_WINDOW_CLASS,
			g_sz_WINDOW_CLASS,
			WS_OVERLAPPEDWINDOW, // Windows Style
			CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT,
			NULL,	//Parent
			NULL,	//hMenu Для главного окна это RecourceID главного меню,
			//для дочернего окна (кнопки и другие элементы) - 
			//это ID-ресурса соответствующего элемента(кнопки, такстового пол, и т.д.)
			//По этому RosourceID мы находим дочерний элемент окна при помощи функции GetDlgItem();
			hInstance,
			NULL
		);
	if (hwnd == NULL) {
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.message;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE: {
		CreateWindowEx
		(
			NULL,
			"Static",
			"Это static_text, бейба",
			WS_CHILD | WS_VISIBLE, // Для всех дочерних окон стиль обязательно будет WS_CHILD (это как минимум)
			100, 10, // x, y
			200, 20,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx(
			NULL, "Edit", "",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 30,
			200, 20,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx(
			NULL, "Button", "Применить",
			WS_CHILD | WS_VISIBLE,
			200, 50,
			100, 32,
			hwnd,
			(HMENU)IDC_BUTTON,
			GetModuleHandle(NULL),
			NULL
		);
	}
		break;
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON: {
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			HWND hStatic = GetDlgItem(hwnd, IDC_STATIC);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
		}
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_CLOSE: DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}