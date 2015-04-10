#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>
#include<conio.h>
#include <io.h>
static TCHAR WindowsClass[] = _T("win32app");

static TCHAR Title[] = _T("MyApp");
char szText[] = "";
int i = 0;
HINSTANCE hinst;

#define ID_BUTTON 1001


#define ID_CHECK 1020 
#define ID_CHECK1 1021
#define ID_CHECK2 1022
#define ID_CHECK3 1023



HWND button, button1, pushButton, edit, list, checkbox,checkbox1,checkbox2,checkbox3;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);*/
	wcex.hbrBackground = CreateSolidBrush(RGB(150, 70, 150));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "Call faild!", "MyApp", NULL);
		return 1;
	}

	hinst = hinstance;

	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		500,
		500,
		NULL,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, _T("Create window faild!"), "MyApp", NULL);
		return 1;
	}
	SetTimer(hWnd, 1, 100, NULL);
	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	int xPos, yPos, length, mY = 0;
	char str[41];
	/*wchar_t str[10];*/
	strcpy(str," ");


	switch (message)
	{
	case WM_COMMAND:

		

		{	auto res = SendMessage(checkbox, BM_GETCHECK, 0, 0);
			if (res == BST_CHECKED)
			{
				strcat(str,"  Сильный");
			}
			auto res1 = SendMessage(checkbox1, BM_GETCHECK, 0, 0);
			if (res1 == BST_CHECKED)
			{
				strcat(str,"  Смелый");
			}
			auto res2 = SendMessage(checkbox2, BM_GETCHECK, 0, 0);
			if (res2 == BST_CHECKED)
			{
				strcat(str,"  Добрый");
			}
			auto res3 = SendMessage(checkbox3, BM_GETCHECK, 0, 0);
			if (res3 == BST_CHECKED)
			{
				strcat(str,"  Умный");
			}
		}

		
			
		case BN_CLICKED:
		{
			

			if (LOWORD(wParam) == ID_BUTTON){
			
				
				MessageBox(hWnd, str, "", TRUE);
				strcpy(str," ");
				
			}
		}
		break;
	break;

		
	case WM_CREATE:
		button = CreateWindowEx(NULL, "button", "Показать", WS_CHILD | WS_VISIBLE, 10, 10, 100, 20, hWnd, (HMENU)ID_BUTTON, hinst, NULL);
	
		checkbox = CreateWindow("button", "Сильный", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 10, 50, 100, 40, hWnd, (HMENU)ID_CHECK, hinst, NULL);
		checkbox1 = CreateWindow("button", "Смелый", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 10, 95, 100, 40, hWnd, (HMENU)ID_CHECK1, hinst, NULL);
		checkbox2 = CreateWindow("button", "Добрый", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 10, 140, 100, 40, hWnd, (HMENU)ID_CHECK2, hinst, NULL);
		checkbox3 = CreateWindow("button", "Умный", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 10, 185, 100, 40, hWnd, (HMENU)ID_CHECK3, hinst, NULL);

		char s[10];
		for (int i = 0; i < 10; i++){
			itoa(i, s, 10);
			strcat(s, "String");
			SendMessage(list, LB_ADDSTRING, 0, (LPARAM)s);
		}
		

		break;
	case WM_LBUTTONDBLCLK:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_KEYDOWN:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
		break;
	case WM_KILLFOCUS:
		break;

	case WM_NOTIFY:		
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		/*TextOut(hdc, 5, 5, "Hello!", 6);*/
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}