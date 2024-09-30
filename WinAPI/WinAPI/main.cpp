#include <Windows.h>
#include "resource.h"

CONST CHAR g_sz_LOGIN_INVITATION[] = "Введите имя пробабушки";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR IpCmdLine, INT nCmdShow)
{
	//hInstance - экземпляр запущенного *.exe-файла нашей программы
	//hPrevInst - НЕ используется
	//LPSTR - Long Pointer To String
	//IpCmdLine - CommpandLine(командная строка с параметрами записка приложения)
	//nCmdShow - режим отображения окна (равернуто на весь экран, свернуто на панель задач и т.д.)
	//Префиксы: n..., lp... это Венгерская нотация
	//			n - Number
	//			lp - Long Pointer
	//			h - HINSTANCE

	//MessageBox
	//(
	//	NULL, 
	//	"Hello Boy!\nThis is MassageBox()", 
	//	"Window title", 
	//	MB_CANCELTRYCONTINUE | MB_HELP | MB_DEFBUTTON3 |
	//	MB_ICONINFORMATION |
	//	//MB_SYSTEMMODAL
	//	MB_DEFAULT_DESKTOP_ONLY |
	//	MB_RIGHT
	//);
	
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);
	
	return 0;
}
//                         окно       сообщение    парамерт       параметр   
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	//hwnd - Hendler to Window. обработчик или дескриптор окна - это число, при помощи которого можно обратиться к окну.
	//uMsg - Message. Сообщение, которое отправляется к окну.
	//wPara, IParam - это параметры сообщения, у каждого сообщения свой набор параметров.
	//LOWORD - Младшее слово.
	//HIWORD - Старшее слово.
	//DWORD - Double Word;

	switch (uMsg)
	{
	case WM_INITDIALOG: // Это сообщение отправляется один раз при инициализации окна
	{
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION); // (LPARAM)g_sz_LOGIN_INVITATION
	} break;
	case WM_COMMAND:	// Обрабатывает нажатие кнопок и другие действия пользователя
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN: { // Делаем надпись поверх строки 
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage((HWND)lParam, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				if (strcmp(sz_buffer, g_sz_LOGIN_INVITATION) == 0)
					SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)"");
			}
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				if (strcmp(sz_buffer, "") == 0)
					SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
			}
			//EN_ - Edit Notofocation
			//Функция strcmp(const char* str1, const char* str2) cравнивает строки и возвращает значение типа 'int":
			//		0  - строки идентичны
			//		!0 - строки отличаются
		} break;
		case IDC_BUTTON_COPY: 
		{
			// Создать буфер
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};

			// Получаем обработчики текстовых полей
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);

			// Считываем содержимое поля Login в буфер
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			//// Делаем надпись поверх строки 
			//HWND hEditEDIT_LOGIN = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			//if (sz_buffer[0] == 0) 
			//	ShowWindow(hEditEDIT_LOGIN, SW_SHOW);

			// Записываем полученый текст в текстовое поле Password:
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		} break;
		case IDOK:		MessageBox(hwnd, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:	EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:		// Отравляет при нажатии кнопки Закрыть Х
		EndDialog(hwnd, 0);
		break;
	}

	return FALSE;
}