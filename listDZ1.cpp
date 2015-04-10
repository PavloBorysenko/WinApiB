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
bool zapr=false;
HINSTANCE hinst;

#define ID_BUTTON 1001

#define ID_LISTBOX 1010
#define ID_LISTBOX1 1011




HWND button, list,list1,temp;

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
	char str1[21], str2[10];
	/*wchar_t str[10];*/



	switch (message)
	{
	case WM_COMMAND:
        case LBN_SETFOCUS:
			
			if(LOWORD(wParam) == ID_LISTBOX){
				
				temp=list;
				
				zapr=true;
				}
			else if(LOWORD(wParam) == ID_LISTBOX1){
				temp=list1;
				zapr=true;
				}
	
			
		case BN_CLICKED:
		{
			
			if (LOWORD(wParam) == ID_BUTTON){
			auto c=SendMessage(temp, LB_GETCOUNT, 0, 0);
			itoa(c, str1, 10); 
			SendMessage(temp, LB_GETTEXT, c-1, (LPARAM)str1);
			
			int sum=atoi(str1);
				itoa(sum+1, str1, 10);
            SendMessage(temp, LB_INSERTSTRING, c, (LPARAM)str1);
				
			}
		}
		break;

	break;

		
	case WM_CREATE:
		button = CreateWindowEx(NULL, "button", "Добавить", WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, hWnd, (HMENU)ID_BUTTON, hinst, NULL);
			

		list = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox","", WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL /*| LBS_SORT*/, 50, 50, 100, 400, hWnd,(HMENU)ID_LISTBOX, hinst, NULL);
		list1 = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox","", WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL |LBS_SORT, 250,50, 100, 400, hWnd,(HMENU)ID_LISTBOX1, hinst, NULL);
	

		char s[10];
		char s1[10];
		for (int i = 0; i < 5; i++){

			itoa(1+i, s, 10);
			itoa(201+i, s1, 10);
			SendMessage(list, LB_ADDSTRING, 0, (LPARAM)s);
			SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)s1);
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