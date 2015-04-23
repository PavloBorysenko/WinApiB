#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>
#include<vector>
#include<iostream>
#include <cstdio>
#include <time.h>

using namespace std;
static TCHAR WindowsClass[] = _T("win32app");

static TCHAR Title[] = _T("MyApp");
char szText[] = "";
int i = 0;
HINSTANCE hinst;
#define ID_EDIT 104
#define ID_EDIT1 105 
#define ID_BUTTON 1
#define ID_COMBO 1001
#define ID_COMBO1 1002
#define ID_COMBO2 1003 
#define ID_COMBO3 1004
#define ID_LISTBOX 1010



HWND button, edit1, edit, list,combo1,combo2,combo3,combo4;
char str[40],str1[14], str2[14],strPc[40],str1Pc[14],str2Pc[14];
char strH[40],strF[40],strB[40];
bool redy1=false,redy2=false,redy3=false,redy4=false;
int ud=0,napr=0,blok=0,udPc=0,naprPc=0;
int life=100,Mylife=100;
int PowH,PowF;
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
	srand(time(NULL));

	switch (message)
	{
		
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_COMBO3 && HIWORD(wParam) == CBN_SELENDOK){
		 auto seler = SendMessage(combo4, CB_GETCURSEL, 0, 0);
		 switch(seler){
		 case 0:
			 PowH=5;
			 PowF=10;
			 break;
		 case 1:
			  PowH=8;
			 PowF=16;
			 break;
		 case 2:
			 PowH=10;
			 PowF=20;
			 break;
		 }
		 strcpy(strH,"*враг попал -");
		 strcpy(strF,"*враг попал -");
		 strcpy(strB,"*Пробил блок -");
		 char strT[10];
		 itoa(PowH, strT, 10);
		 strcat(strH,strT);
		 strcat(strB,strT);
		 itoa(PowF, strT, 10);
		 strcat(strF,strT);
		 EnableWindow(combo4, 0);
		 redy4=true;
		}
		if (LOWORD(wParam) == ID_COMBO2 && HIWORD(wParam) == CBN_SELENDOK){
			 auto sele = SendMessage(combo3, CB_GETCURSEL, 0, 0);
				 blok=sele;
				redy3=true;
			}
		if (LOWORD(wParam) == ID_COMBO && HIWORD(wParam) == CBN_SELENDOK) {
			    strcpy(str,"");
			
		         auto sel = SendMessage(combo1, CB_GETCURSEL, 0, 0);
				 ud=sel;
				  SendMessage(combo1, CB_GETLBTEXT, sel, (LPARAM)str1);
				  redy1=true;
				strcat(str,str1);
		strcat(str,str2);		
				
		}
		if (LOWORD(wParam) == ID_COMBO1 && HIWORD(wParam) == CBN_SELENDOK) {
			    strcpy(str,"");
		         auto se = SendMessage(combo2, CB_GETCURSEL, 0, 0);
				 napr=se;
				  SendMessage(combo2, CB_GETLBTEXT, se, (LPARAM)str2);
			redy2=true;
		strcat(str,str1);
		strcat(str,str2);
		}
		
		if(redy1==true&&redy2==true&&redy3==true&&redy4==true){
		EnableWindow(button, 1);
		
		}
			
		case BN_CLICKED:
		{	

			if (LOWORD(wParam) == ID_BUTTON){
		    auto c=SendMessage(list, LB_GETCOUNT, 0, 0);
			
			SendMessage(list,LB_INSERTSTRING, c, (LPARAM)str);
			
			    c=SendMessage(list, LB_GETCOUNT, 0, 0);
			if(napr==rand()%3){
				if(ud==1){
					if(rand()%2!=0){
                      life-=5;
					  SendMessage(list, LB_INSERTSTRING, c, (LPARAM)"*Пробил блок -5");
					}
					else SendMessage(list, LB_INSERTSTRING, c, (LPARAM)"****Попал в блок!");
				}
				else SendMessage(list, LB_INSERTSTRING, c, (LPARAM)"****Попал в блок!");
			}
			else{
			    switch(ud){
				case 1:
					life-=5;
					SendMessage(list, LB_INSERTSTRING, c, (LPARAM)"****Попал -5 жизни");
					break;
				case 0:
					life-=10;
					SendMessage(list, LB_INSERTSTRING, c, (LPARAM)"****Попал -10 жизни");
				}
			}
			
			char s[10];
			itoa(life, s, 10);
			SendMessage(edit, WM_SETTEXT, 0, (LPARAM) s);
			if(life<=0){
			MessageBox(hWnd, "Враг повержен", "", TRUE);
			exit(0);
			}
			 c=SendMessage(list, LB_GETCOUNT, 0, 0);
			SendMessage(list, LB_INSERTSTRING, c, (LPARAM)"*******************");
			SendMessage(list, LB_INSERTSTRING, ++c, (LPARAM)"Удар противника");
			strcpy(strPc,"");
			udPc=rand()%2;
			naprPc=rand()%3;
			SendMessage(combo1, CB_GETLBTEXT, udPc, (LPARAM)str1Pc);
			SendMessage(combo2, CB_GETLBTEXT, naprPc, (LPARAM)str2Pc);
			strcat(strPc,str1Pc);
		    strcat(strPc,str2Pc);
            c=SendMessage(list, LB_GETCOUNT, 0, 0);
			SendMessage(list, LB_INSERTSTRING, c, (LPARAM)strPc);
			  
			if(naprPc==blok){
				if(udPc==1){
					if(rand()%2!=0){
                      Mylife-=PowH;
					  
					  SendMessage(list, LB_INSERTSTRING, ++c, (LPARAM)strB);
					}
					else SendMessage(list, LB_INSERTSTRING, ++c, (LPARAM)"****Попал в блок!");
				}
				else SendMessage(list, LB_INSERTSTRING, ++c, (LPARAM)"****Попал в блок!");
				
			}
			else{
				
			    switch(udPc){
				case 1:
					Mylife-=PowH;
				
					SendMessage(list, LB_INSERTSTRING, ++c, (LPARAM)strH);
					break;
				case 0:
					Mylife-=PowF;
					
					SendMessage(list, LB_INSERTSTRING, ++c, (LPARAM)strF);
				}
			}
			
			char sPc[10];
			itoa(Mylife, sPc, 10);

			SendMessage(edit1, WM_SETTEXT, 0, (LPARAM) sPc);
			if(Mylife<=0){
			MessageBox(hWnd, "Ты проиграл", "", TRUE);
			exit(0);
			}
			SendMessage(list, LB_INSERTSTRING, ++c, (LPARAM)"*******************");
			SendMessage(list, LB_INSERTSTRING, ++c, (LPARAM)"Твой удар");
			}
		}
		break;
	break;

		
	case WM_CREATE:
		button = CreateWindowEx(NULL, "button", "Удар", WS_CHILD | WS_VISIBLE, 10, 30, 60, 20, hWnd, (HMENU)ID_BUTTON, hinst, NULL);
	
		edit = CreateWindowEx(NULL, "edit", "100", WS_CHILD | WS_VISIBLE, 350, 350, 35, 20, hWnd, (HMENU)ID_EDIT, hinst, NULL);
		edit1 = CreateWindowEx(NULL, "edit", "100", WS_CHILD | WS_VISIBLE, 10, 350, 35, 20, hWnd, (HMENU)ID_EDIT1, hinst, NULL);
			

		list = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox","", WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL, 150, 30, 150, 400, hWnd,(HMENU)ID_LISTBOX, hinst, NULL);
	

		
		combo1 = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE |CBS_DROPDOWN, 10, 70, 110, 110, hWnd, (HMENU)ID_COMBO, hinst, NULL);
		combo2 = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 10, 170, 110, 110, hWnd, (HMENU)ID_COMBO1, hinst, NULL);
		combo3 = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 10, 270, 110, 110, hWnd, (HMENU)ID_COMBO2, hinst, NULL);
		combo4 = CreateWindow("combobox", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 350, 50, 110, 110, hWnd, (HMENU)ID_COMBO3, hinst, NULL);
		EnableWindow(button, 0);
		SendMessage(combo1,CB_ADDSTRING, 0, (LPARAM)"ногой ");
		SendMessage(combo1,CB_ADDSTRING, 0, (LPARAM)"рукой ");
		SendMessage(combo1, WM_SETTEXT, 0, (LPARAM) "инструмент");
		SendMessage(combo2,CB_ADDSTRING, 0, (LPARAM)"в голову");
		SendMessage(combo2,CB_ADDSTRING, 0, (LPARAM)"в живот");
		SendMessage(combo2,CB_ADDSTRING, 0, (LPARAM)"в ногу");
		SendMessage(combo2, WM_SETTEXT, 0, (LPARAM) "прицел");
	    SendMessage(combo3,CB_ADDSTRING, 0, (LPARAM)" верхний");
		SendMessage(combo3,CB_ADDSTRING, 0, (LPARAM)" средний");
		SendMessage(combo3,CB_ADDSTRING, 0, (LPARAM)" нижний");
		SendMessage(combo3, WM_SETTEXT, 0, (LPARAM) "выбери блок");
		SendMessage(combo4,CB_ADDSTRING, 0, (LPARAM)"Слабак");
		SendMessage(combo4,CB_ADDSTRING, 0, (LPARAM)"Боец");
		SendMessage(combo4,CB_ADDSTRING, 0, (LPARAM)"Герой");
		SendMessage(combo4, WM_SETTEXT, 0, (LPARAM) "Сила врага");
	     MessageBox(hWnd, "   Удар ногой 100% задерживается блоком, а вероятность срабатывания блока против удара рукой - 50%", "!!!Правила!!!", TRUE);
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
	
		break;
	case WM_KILLFOCUS:
		break;

	case WM_NOTIFY:		
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 5, 5, "Для начала игры выберите все пункты!", 36);
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