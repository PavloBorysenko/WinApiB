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
#define ID_BUTTON1 1002
#define ID_EDIT 1003
#define ID_LISTBOX 1010
#define ID_CHECK 1020 



HWND button, button1, pushButton, edit, list, checkbox;

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
	char str1[20], str2[10];
	/*wchar_t str[10];*/



	switch (message)
	{
	case WM_COMMAND:

	

		
			
		case BN_CLICKED:
		{
			

			if (LOWORD(wParam) == ID_BUTTON){
			
				char str[20];
				SendMessage(edit, WM_GETTEXT, sizeof(str), (LPARAM)str);
				
				auto rezul = SendMessage(list,LB_FINDSTRING, -1, (LPARAM) str);
				
				SendMessage(list,LB_GETTEXT,rezul, (LPARAM) str1);
				/*MessageBox(hWnd, str1, "", TRUE);*/
				
				if(rezul>=0&&strcmp(str,str1)==0){
					itoa(rezul+1, str, 10);
					strcat(str,"-позиция");
					MessageBox(hWnd, str, "", TRUE);
				}
				else{
					MessageBox(hWnd, "Cтрока не найдена", "", TRUE);
				}


			
			}
		}
		break;
	break;

		
	case WM_CREATE:
		button = CreateWindowEx(NULL, "button", "Button", WS_CHILD | WS_VISIBLE, 10, 10, 60, 20, hWnd, (HMENU)ID_BUTTON, hinst, NULL);
		
		edit = CreateWindowEx(NULL, "edit", "", WS_CHILD | WS_VISIBLE, 100, 10, 100, 20, hWnd, (HMENU)ID_EDIT, hinst, NULL);
			

		list = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox","", WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT, 50, 50, 100, 400, hWnd,(HMENU)ID_LISTBOX, hinst, NULL);
		

		

		char s[10];
		for (int i = 0; i < 10; i++){

			itoa(rand()%100, s, 10);
			/*strcat(s, "String");*/
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