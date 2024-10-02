//ComboBox
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include<Windows.h>
#include"resource.h"

CONST CHAR* g_combo_box_items[] = { "This", "is", "my", "First", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdline, INT nCmdShow) 
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_INITDIALOG: 
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTATOM(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(g_combo_box_items) / sizeof(g_combo_box_items[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_combo_box_items[i]);
		}
		SendMessage(hCombo, CB_SETCURSEL, 0, 0); 
		//CB_SETCURSEL - ComboBox Set Current Selection

	} 
	break;
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDOK: {
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
			MessageBox(hwnd, sz_buffer, "info", MB_OK | MB_ICONASTERISK);

			CHAR sz_message[SIZE]{};
			sprintf(sz_message, "Вы выбрали №%i со значением %s", i, sz_buffer);
				// Функция sprintf выполняет форматирование строк, позволяет вставить в троку переменные значения 
				// Cпецификатор %i - целое число
				// Спецификатор %s - строка
		}
			break;
		case IDCANCEL:	EndDialog(hwnd, 0);
			break;
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}