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

#define ID_BUTTON 1001
#define ID_EDIT1 1002
#define ID_EDIT 1003



HWND button, button1, pushButton,edit1, edit;

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
	char str1[60], str2[60];
	
	std::string s;

	switch (message)
	{
	case WM_COMMAND:
		case BN_CLICKED:
		{
			

			if (LOWORD(wParam) == ID_BUTTON){
				
				SendMessage(edit, WM_GETTEXT,sizeof(str1), (LPARAM)str1);
				SendMessage(edit1, WM_GETTEXT,sizeof(str1), (LPARAM)str2);
				
				SendMessage(edit, WM_SETTEXT, 0, (LPARAM)str2);
				SendMessage(edit1, WM_SETTEXT, 0, (LPARAM)str1);
				MessageBox(hWnd, "Обмен произведен", "", TRUE);
			}
		}
		break;
	break;
	case WM_CREATE:
		button = CreateWindowEx(NULL, "button", "Обмен", WS_CHILD | WS_VISIBLE, 50, 140, 100, 20, hWnd, (HMENU)ID_BUTTON, hinst, NULL);
		edit1 = CreateWindowEx(NULL, "edit", "", WS_CHILD | WS_VISIBLE| ES_MULTILINE, 50, 100, 150, 18, hWnd, (HMENU)ID_EDIT1, hinst, NULL);
		edit = CreateWindowEx(NULL, "edit", "", WS_CHILD | WS_VISIBLE | ES_MULTILINE, 250, 100, 150, 18, hWnd, (HMENU)ID_EDIT, hinst, NULL);
		
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