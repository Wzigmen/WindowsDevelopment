//ListBox
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include<Windows.h>
#include"resource.h"

CONST CHAR* g_LIST_BOX_ITEMS[] = { "This", "is", "my", "First", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcDelete(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcChange(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow) 
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(g_LIST_BOX_ITEMS) / sizeof(g_LIST_BOX_ITEMS[0]); i++)
		{
			SendMessage(hCombo, LB_ADDSTRING, 0, (LPARAM)g_LIST_BOX_ITEMS[i]);
		}
	}
		break;
	case WM_COMMAND: 
		switch (LOWORD(wParam))
		{
		case IDC_LIST1: {
			if (HIWORD(wParam) == LBN_DBLCLK) {
				//CONST INT SIZE = 256;
				//CHAR sz_buffer[SIZE];
				//INT i = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);
				//SendMessage((HWND)lParam, LB_GETTEXT, SIZE, (LPARAM)sz_buffer);
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD_ITEM), hwnd, (DLGPROC)DlgProcChange, 0);
			}
		}
			break;
		case IDC_BUTTON_ADD: {
			//GetModuleHandle(NULL); ���������� hInstance �������� ���������
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD_ITEM), hwnd, (DLGPROC)DlgProcAdd, 0);
		}
			break;
		case IDC_BUTTON_DELETE: {
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			CHAR sz_message[SIZE]{ "�� ������ �� �������" };
			HWND hCombo = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hCombo, LB_GETCURSEL, 0, 0);
			SendMessage(hCombo, LB_GETTEXT, i, (LPARAM)sz_buffer);
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			SendMessage(hListBox, LB_DELETESTRING, i, 0);
			if (i == LB_ERR)
				MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDOK: {
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			CHAR sz_message[SIZE]{"�� ������ �� �������"};
			HWND hCombo = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hCombo, LB_GETCURSEL, 0, 0);
			SendMessage(hCombo, LB_GETTEXT, i, (LPARAM)sz_buffer);
			
			if(i!=LB_ERR)
				sprintf(sz_message, "�� ������� ������� � %i �� ��������� %s", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);

		}
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:		// ��������� ��� ������� ������ ������� �
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)
	{
	case WM_INITDIALOG: {
		/*SetFocus(GetDlgItem)*/
	}
		break;
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDOK: 
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_NAME), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			HWND hParend = GetParent(hwnd);
			HWND hListBox = GetDlgItem(hParend, IDC_LIST1);
			if (SendMessage(hListBox, LB_FINDSTRING, -1, (LPARAM)sz_buffer) == LB_ERR)
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			else
				MessageBox(hwnd, "����� ��������� ��� ����������", "Info", MB_OK | MB_ICONINFORMATION);
		}
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
	} break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}
BOOL CALLBACK DlgProcDelete(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)
	{
	case WM_INITDIALOG: 
		break;
	case WM_COMMAND: {
		INT i = SendMessage(hwnd, LB_GETCURSEL, 0, 0);
		SendMessage(hwnd, LB_DELETESTRING, i, 0);
	}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}
BOOL CALLBACK DlgProcChange(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)"��������");
			SendMessage(GetDlgItem(hwnd, IDOK), WM_SETTEXT, 0, (LPARAM)"Co�������");

			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE];
			HWND hParent = GetParent(hwnd);
			HWND hListBox = GetDlgItem(hParent, IDC_LIST1);
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_NAME);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hEdit, EM_SETSEL, 0, SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0));
			SetFocus(GetDlgItem(hwnd, IDC_EDIT_NAME));
		}
			break;
		case WM_COMMAND: {
			switch (LOWORD(wParam))
			{
			case IDOK: {
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_NAME);
				HWND hParent = GetParent(hwnd);
				HWND hListBox = GetDlgItem(hParent, IDC_LIST1);
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE];
				SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				//SendMessage(hListBox, LB_SETITEMDATA, i, (LPARAM)sz_buffer);
				if (SendMessage(hListBox,LB_FINDSTRING, -1, (LPARAM)sz_buffer)==LB_ERR)
				{
					SendMessage(hListBox, LB_DELETESTRING, i, 0);
					SendMessage(hListBox, LB_INSERTSTRING, i, (LPARAM)sz_buffer);
					EndDialog(hwnd, 0);
				}
				else 
				{
					MessageBox(hwnd, "����� �������� ��� ���� � ������", "Info", MB_OK | MB_ICONINFORMATION);
				}
			}
				break;
			case IDCANCEL: EndDialog(hwnd, 0);
			}
		}
			break;
		case WM_CLOSE:
			EndDialog(hwnd, 0);
	}
	return FALSE;
}