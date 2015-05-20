// у.cpp: определяет точку входа для приложения.
//

#include "math.h"
#include "stdafx.h"
#include "у.h"
//#include "Progress_WINAPI.h"
#include <CommCtrl.h>
#include <string>
//STYLE FOR PROGRSS
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' \
//version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#define MAX_LOADSTRING 100
#define ID_PROGRESS 1101
#define ID_TIMER 1102
#define ID_MAS 1103
#define ID_START 1104
#define ID_SLIDER 1106
#define ID_BODY 1107
#define ID_R 1108
#define ID_R1 1109
#define ID_BUTT_CEL 1110
HWND
progress, mas, start,  slider,body,edit,edit1,cel;
HANDLE hBitBomb1,hBitBomb2,hBitBark;
// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
int x=20,y=280,xC=700,col=0;
double N,t=0,rad,pos1,power=0,pos2;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
//  КОММЕНТАРИИ:
//
//    Эта функция и ее использование необходимы только в случае, если нужно, чтобы данный код
//    был совместим с системами Win32, не имеющими функции RegisterClassEx'
//    которая была добавлена в Windows 95. Вызов этой функции важен для того,
//    чтобы приложение получило "качественные" мелкие значки и установило связь
//    с ними.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
	void bombImg(HWND bomb){

		hBitBomb1 = LoadImage(NULL, "bomb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SendMessage(bomb, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitBomb1);
	}
	void BOOM(HWND boom){

		hBitBomb2 = LoadImage(NULL, "boom.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SendMessage(boom, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitBomb2);
	}
	void BARK(HWND bark){
        hBitBark = LoadImage(NULL, "bark.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SendMessage(bark, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitBark);
	}
	void Muve(HWND bark){
	xC=rand()%500+300;
	MoveWindow(bark,xC,260, 110, 70, TRUE);
	BARK(cel);
	}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
    case WM_CREATE:
		//Slider
		slider = CreateWindowEx(NULL, TRACKBAR_CLASS, "", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE | TBS_HORZ | TBS_TOP, 350, 350, 200, 50, hWnd, (HMENU)ID_SLIDER, hInst, NULL);
		SendMessage(slider, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 90));
		
        mas = CreateWindowEx(NULL, "button", "Plus", WS_CHILD | WS_VISIBLE, 20, 380, 50, 20, hWnd, (HMENU)ID_MAS, hInst, NULL);
		start = CreateWindowEx(NULL, "button", "Start", WS_CHILD | WS_VISIBLE, 200, 350, 50, 20, hWnd, (HMENU)ID_START, hInst, NULL);
		body = CreateWindowEx(NULL, "button", "body", WS_CHILD | WS_VISIBLE|BS_BITMAP, 20, 280, 40, 40, hWnd, (HMENU)ID_BODY, hInst, NULL);
		cel = CreateWindowEx(NULL, "button", "body", WS_CHILD | WS_VISIBLE|BS_BITMAP, xC, 260, 110, 70, hWnd, (HMENU)ID_BUTT_CEL, hInst, NULL);
	    bombImg(body);
		BARK(cel);
			//Progress
		progress = CreateWindowEx(NULL, PROGRESS_CLASS, "", WS_CHILD | WS_VISIBLE, 20, 350, 124, 20, hWnd, (HMENU)ID_PROGRESS, hInst, NULL);
		SendMessage(progress, PBM_SETRANGE, 0, MAKELPARAM(0, 10));
		SendMessage(progress, PBM_SETSTEP, (WPARAM)1, 0);
		edit = CreateWindowEx(NULL, "edit", "0", WS_CHILD | WS_VISIBLE, 570, 380, 55, 40, hWnd, (HMENU)ID_R, hInst, NULL);
		edit1= CreateWindowEx(NULL, "edit", "0", WS_CHILD | WS_VISIBLE, 780, 380, 55, 40, hWnd, (HMENU)ID_R1, hInst, NULL);
		break;
	case WM_TIMER:
		t+=0.1;
		rad=pos1*(3.14/180);
	    N=((power*cos(rad))*t);
	    MoveWindow(body,x+N,y-((power*sin(rad))*t-9.8*t*t/2), 40, 40, TRUE);
		if(t/2>=power*sin(rad)/9.8){
			BOOM(body);
			KillTimer(hWnd, ID_TIMER);
			if(x+N>xC-20&&x+N<xC+90){
				col++;
          	    char s[10];
		        itoa(col, s, 10);
			    SendMessage(edit1, WM_SETTEXT, 0, (LPARAM)s);
			   MessageBox(hWnd, "Попал!!!!!!!", "", TRUE);
			   Muve(cel);
			}
		}
		break;
	case WM_HSCROLL:{
		auto pos = SendMessage(slider, TBM_GETPOS, 0, 0);
		char s1[10];
		/*sprintf(s1, "%f",pos);*/
          itoa(pos, s1, 10);
		SendMessage(edit, WM_SETTEXT, 0, (LPARAM)s1);
		pos1=(double)pos;
					}break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
			case ID_START:
             bombImg(body);
			 MoveWindow(body,20,280, 40, 40, TRUE);
			 t=0;
				SetTimer(hWnd, ID_TIMER, 10, 0);
				break;
			case ID_MAS:
				if(power>90){
				power=0;
			}
			SendMessage(progress, PBM_STEPIT, 0, 0);
		    power+=10;
			
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: добавьте любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
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
