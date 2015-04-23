#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>
#include<vector>
#include<iostream>
#include <cstdio>
using namespace std;
static TCHAR WindowsClass[] = _T("win32app");

static TCHAR Title[] = _T("MyApp");
char szText[] = "";
int i = 0;
HINSTANCE hinst;

#define ID_BUTTON 1001
#define ID_COMBO 1002
#define ID_COMBO1 1003
#define ID_EDIT 1004
#define ID_LISTBOX 1010
#define ID_CHECK 1020 



HWND button, button1, pushButton, edit, list, checkbox,combo1,combo2;
char str1[30], str2[14];
int pos;
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
	
char strud[10];
string wor1;
string wor2;

	switch (message)
	{
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_COMBO && HIWORD(wParam) == CBN_SELENDOK) {
			
		        auto  sel = SendMessage(combo1, CB_GETCURSEL, 0, 0);
				pos=sel;
				 SendMessage(combo1, CB_GETLBTEXT, sel, (LPARAM)str2);
          
				
			

						
				
		}

			
		case BN_CLICKED:
		{
			

			if (LOWORD(wParam) == ID_BUTTON){
		
			SendMessage(edit, WM_GETTEXT, sizeof(str1), (LPARAM)str1);
            SendMessage(combo1, CB_DELETESTRING, (WPARAM)pos, 0);
			strcat(str1,str2);
		    SendMessage(combo1, CB_INSERTSTRING, (WPARAM)pos, (LPARAM)str1);
			
	        //SendMessage(combo1, CB_SETCURSEL, (WPARAM)pos, 0);
			
				
			}
		}
		break;
	break;

		
	case WM_CREATE:
		button = CreateWindowEx(NULL, "button", "Записать", WS_CHILD | WS_VISIBLE, 10, 260, 100, 20, hWnd, (HMENU)ID_BUTTON, hinst, NULL);
		edit = CreateWindowEx(NULL, "edit", "Фамилия", WS_CHILD | WS_VISIBLE, 10, 10, 100, 20, hWnd, (HMENU)ID_EDIT, hinst, NULL);
		combo1 = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE |CBS_SIMPLE, 10, 50, 200, 200, hWnd, (HMENU)ID_COMBO, hinst, NULL);
		
		SendMessage(combo1,CB_ADDSTRING, 0, (LPARAM)" программист");
		SendMessage(combo1,CB_ADDSTRING, 0, (LPARAM)" врач");
		SendMessage(combo1, CB_ADDSTRING, 0, (LPARAM) " директор");
		SendMessage(combo1,CB_ADDSTRING, 0, (LPARAM)" профессор");
		SendMessage(combo1,CB_ADDSTRING, 0, (LPARAM)" стоматолог");
		SendMessage(combo1,CB_ADDSTRING, 0, (LPARAM)" шофёр");
		SendMessage(combo1, CB_ADDSTRING, 0, (LPARAM) " сантехник");
		SendMessage(combo1, CB_ADDSTRING, 0, (LPARAM) " токарь");
		SendMessage(combo1, CB_ADDSTRING, 0, (LPARAM) " пилот");
		SendMessage(combo1, WM_SETTEXT, 0, (LPARAM) "Профессии");
	
		

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