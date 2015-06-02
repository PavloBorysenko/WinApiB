#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<commctrl.h>
#include<string>
#include<Math.h>
#include<tchar.h>
using namespace std;

HINSTANCE hInst;
 
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);
void RegisterDialogClass(HWND);
void CreateDialogWindow(HWND);
void OpenDialog(HWND);


INT APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, INT nCmdShow){
	hInst = hInst;
	MSG msg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.hIconSm = NULL;
	wcl.lpszClassName = "My APP";
	wcl.lpfnWndProc = WinProc;
	if (!RegisterClassEx(&wcl))
		return 0;
	HWND hWnd;
	hWnd = CreateWindow(
		"My APP",
		"WindowName", // Title
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL
		);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void CreateUpDown(HWND);

POINT point;
UINT code;
LPNMUPDOWN lpnmud;
int val;
struct Name{
	char car[50];	
};
Name  mas[5]={"Mazda","Opel","Seat","Tayota","ZAZ"};
char car1[20];
char NCar[100];
int power[5]={100,85,90,120,46};
int spd[5]={220,160,180,260,110};
int cheng=0;
void NAME(int c){
	strcpy(NCar,mas[c].car);
	strcat(NCar,"  pw:");
	char s[10];
	itoa(power[c], s, 10);
	strcat(NCar,s);
	strcat(NCar,"  sp:");
	itoa(spd[c], s, 10);
	strcat(NCar,s);	
}
HWND newDialog,list,edit1,edit2,edit3,button1;
#define ID_EDIT1 501
#define ID_EDIT2 502
#define ID_EDIT3 503
#define ID_BUTTON 601
#define ID_SHOW_DIALOG 100
#define ID_LISTBOX 1000

LRESULT CALLBACK WinProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int wmId;
	int wmEvent;
	
	
	switch (message){
	case WM_CREATE:

		RegisterDialogClass(hWnd);
		newDialog = CreateWindowEx(NULL, "button", "Редактировать", WS_VISIBLE | WS_CHILD, 20, 50, 110, 25, hWnd, (HMENU)ID_SHOW_DIALOG, hInst, NULL);
		list = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox","", WS_CHILD | WS_VISIBLE , 150, 50, 200, 100, hWnd,(HMENU)ID_LISTBOX, hInst, NULL);
		for(int i=0;i<5;i++){
			NAME(i);
		SendMessage(list, LB_ADDSTRING, 0, (LPARAM)NCar);
		}
		break;
	case WM_NOTIFY:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		//CreateDialogWindow(hWnd);
		
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId){
		case ID_SHOW_DIALOG:
			auto rezul = SendMessage(list,LB_GETCURSEL, 0, 0);
			if(rezul<0||rezul>5){
			break;
			}
			cheng=rezul;
			/*char s[10];
			itoa(cheng,s,10);
            MessageBox(hWnd, s, "", TRUE);*/
			CreateDialogWindow(hWnd);

			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	int wmID;
	int wmEVent;
	switch (msg)
	{
	case WM_CREATE:

        edit1 = CreateWindowEx(NULL, "edit", "", WS_CHILD | WS_VISIBLE, 130, 10, 100, 20, hwnd, (HMENU)ID_EDIT1, hInst, NULL);
        edit2 = CreateWindowEx(NULL, "edit", "", WS_CHILD | WS_VISIBLE|ES_NUMBER, 130, 50, 100, 20, hwnd, (HMENU)ID_EDIT2, hInst, NULL);
		edit3 = CreateWindowEx(NULL, "edit", "", WS_CHILD | WS_VISIBLE|ES_NUMBER, 130, 90, 100, 20, hwnd, (HMENU)ID_EDIT3, hInst, NULL);
		button1=CreateWindowEx(NULL, "button", "ok", WS_VISIBLE | WS_CHILD, 30, 50, 80, 25, hwnd, (HMENU)ID_BUTTON, NULL, NULL);
		char s[10];
		char s1[10];
		itoa(power[cheng],s,10);
		itoa(spd[cheng],s1,10);
		SendMessage(edit1, WM_SETTEXT, 0, (LPARAM)mas[cheng].car);
		SendMessage(edit2, WM_SETTEXT, 0, (LPARAM)s);
		SendMessage(edit3, WM_SETTEXT, 0, (LPARAM)s1);

		break;
	case WM_COMMAND:
		wmID = LOWORD(wParam);
		wmEVent = HIWORD(wParam);
		switch (wmID){
		case ID_BUTTON:
			char s2[20];
		    char s3[20];
			SendMessage(edit1,WM_GETTEXT,sizeof(s2), (LPARAM)mas[cheng].car );
			SendMessage(edit2,WM_GETTEXT,sizeof(s2), (LPARAM) s2);
			SendMessage(edit3,WM_GETTEXT,sizeof(s3), (LPARAM) s3);
			power[cheng]=atoi(s2);
			spd[cheng]=atoi(s3);
			
			NAME(cheng);
			SendMessage(list, LB_DELETESTRING, (WPARAM)cheng, 0);
			SendMessage(list, LB_INSERTSTRING, (WPARAM)cheng, (LPARAM)NCar);
			
			DestroyWindow(hwnd);
			break;
		}
		break;
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void RegisterDialogClass(HWND hwnd)
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC)DialogProc;
	wc.hInstance = hInst;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszClassName = "DialogClass";
	RegisterClassEx(&wc);
}

void CreateDialogWindow(HWND hwnd)
{
	CreateWindowEx(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST, "DialogClass", "Dialog Window", WS_VISIBLE, 100, 280, 250, 150, NULL, NULL, hInst, NULL);
}

