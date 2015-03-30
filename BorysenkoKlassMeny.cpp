#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>
#include<conio.h>
#include <io.h>
static TCHAR WindowsClass[] = _T("win32app");

static TCHAR Title[] = _T("MyApp");
char szText[] = "";
HINSTANCE hinst;
int posB1=-20,posB2=-20,posB3=-20,posB4=-20; 
bool up;
#define ID_BUTTON 1001
#define ID_BUTTON1 1002
#define ID_BUTTON2 1003
#define ID_BUTTON3 1004
#define ID_BUTTON4 1005
#define ID_BUTTON5 1006

HWND button, button1,button2,button3,button4,button5;

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
	char str1[21], str2[10];
	/*wchar_t str[10];*/
	std::string s;

	switch (message)
	{
	case WM_COMMAND:
		case BN_CLICKED:
		{
			if (LOWORD(wParam) == ID_BUTTON){
				SetTimer(hWnd, 1, 10, NULL);
				up=false;
			}
			
				
				//SendMessage(button1, BM_SETSTATE, TRUE, 0);
				//SendMessage(button1, WM_SETTEXT, 0, (LPARAM) "Hello");
			//strcpy(str1,"Button");
			else if (LOWORD(wParam) == ID_BUTTON5){
				up=true;
				//SendMessage(button1, WM_GETTEXT, sizeof(str2), (LPARAM)str2);
				////strcpy(str1, "Button1");
				//MessageBox(hWnd, str2, "", TRUE);
			}
		}
		
		break;
	break;
    case WM_TIMER:
		if(up==false){
		if(posB4<100){
			MoveWindow(button4, 370,posB4+=5 , 100, 20, TRUE);}
		else if(posB3<70&&posB4>=10){
			MoveWindow(button3, 370,posB3+=5 , 100, 20, TRUE);}
		else if(posB2<40&&posB3>=70){
			MoveWindow(button2, 370,posB2+=5 , 100, 20, TRUE);}
		else if(posB1<10&&posB2>=40){
			MoveWindow(button1, 370,posB1+=5 , 100, 20, TRUE);}
		}
		else if(up==true){
			if(posB1>-20){
				MoveWindow(button1, 370,posB1-=5 , 100, 20, TRUE);}
			else if(posB2>-20&&posB1<=-20){
				MoveWindow(button2, 370,posB2-=5 , 100, 20, TRUE);}
			else if(posB3>-20&&posB2<=-20){
				MoveWindow(button3, 370,posB3-=5 , 100, 20, TRUE);}
			else if(posB4>-20&&posB3<=-20){
				MoveWindow(button4, 370,posB4-=5 , 100, 20, TRUE);}
		
		}
			 break;
	case WM_CREATE:
		button = CreateWindowEx(NULL, "button", "Down", WS_CHILD | WS_VISIBLE, 10, 10, 100, 20, hWnd, (HMENU)ID_BUTTON, hinst, NULL);
		button1 = CreateWindowEx(NULL, "button", "Button 1", WS_CHILD | WS_VISIBLE, 370, posB1, 100, 20, hWnd, (HMENU)ID_BUTTON1, hinst, NULL);
		button2 = CreateWindowEx(NULL, "button", "Button 2", WS_CHILD | WS_VISIBLE, 370, posB2, 100, 20, hWnd, (HMENU)ID_BUTTON2, hinst, NULL);
		button3 = CreateWindowEx(NULL, "button", "Button 3", WS_CHILD | WS_VISIBLE, 370, posB3, 100, 20, hWnd, (HMENU)ID_BUTTON3, hinst, NULL);
		button4 = CreateWindowEx(NULL, "button", "Button 4", WS_CHILD | WS_VISIBLE, 370, posB4, 100, 20, hWnd, (HMENU)ID_BUTTON4, hinst, NULL);
		button5 = CreateWindowEx(NULL, "button", "Up", WS_CHILD | WS_VISIBLE, 10, 40, 100, 20, hWnd, (HMENU)ID_BUTTON5, hinst, NULL);
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
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		/*TextOut(hdc, 5, 5, "Hello!", 6);*/
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}