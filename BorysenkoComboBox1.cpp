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
				 SendMessage(combo1, CB_GETLBTEXT, sel, (LPARAM)str1);
             if(pos+2>=SendMessage(combo1, CB_GETCOUNT, 0, 0)){
			//MessageBox(hWnd, "str1", "", TRUE);
			EnableWindow(button, 0);
			}
			else EnableWindow(button, 1);
				
			

						
				
		}

			
		case BN_CLICKED:
		{
			

			if (LOWORD(wParam) == ID_BUTTON){
		
			if(pos+2>=SendMessage(combo1, CB_GETCOUNT, 0, 0)){
			//MessageBox(hWnd, "str1", "", TRUE);
			EnableWindow(button, 0);
			}
			else EnableWindow(button, 1);

         
		     SendMessage(combo1, CB_DELETESTRING, (WPARAM)pos, 0);
			SendMessage(combo1, CB_INSERTSTRING, (WPARAM)++pos, (LPARAM)str1);
	        SendMessage(combo1, CB_SETCURSEL, (WPARAM)pos, 0);
			
				
			}
		}
		break;
	break;

		
	case WM_CREATE:
		button = CreateWindowEx(NULL, "button", "Вниз", WS_CHILD | WS_VISIBLE, 10, 260, 60, 20, hWnd, (HMENU)ID_BUTTON, hinst, NULL);
		
		combo1 = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE |CBS_SIMPLE, 10, 50, 100, 200, hWnd, (HMENU)ID_COMBO, hinst, NULL);
		
		SendMessage(combo1,CB_ADDSTRING, 0, (LPARAM)"1-я строка ");
		SendMessage(combo1,CB_ADDSTRING, 0, (LPARAM)"2-я строка ");
		SendMessage(combo1, CB_ADDSTRING, 0, (LPARAM) "3-я строка");
		SendMessage(combo1,CB_ADDSTRING, 0, (LPARAM)"4-я строка");
		SendMessage(combo1,CB_ADDSTRING, 0, (LPARAM)"5-я строка");
		SendMessage(combo1,CB_ADDSTRING, 0, (LPARAM)"6-я строка");
		SendMessage(combo1, CB_ADDSTRING, 0, (LPARAM) "7-я строка");
		SendMessage(combo1, CB_ADDSTRING, 0, (LPARAM) "8-я строка");
		SendMessage(combo1, CB_ADDSTRING, 0, (LPARAM) "9-я строка");
		SendMessage(combo1, WM_SETTEXT, 0, (LPARAM) "Опускаем");
	
		

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