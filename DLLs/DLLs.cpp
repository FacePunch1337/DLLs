
#include "framework.h"
#include "DLLs.h"

#define MAX_LOADSTRING 100
#define CMD_BUTTON_1 1001
#define CMD_BUTTON_2 1002
#define CMD_BUTTON_3 1003
#define CMD_BUTTON_4 1004
#define CMD_BUTTON_5 1005

typedef long (*sqr_type)(long); // sqr_type ~~ long (*)(long)

sqr_type sqr_fun;               // sqr_type sqr_fun == long (*sqr_fun)(long)

typedef void (*Dec_Hex_type) (const char*, char*);
Dec_Hex_type dec_hex;
Dec_Hex_type hex_dec;



// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND reshWnd;
HWND reshWnd2;
HWND inputhWnd;
HWND inputhWnd2;
WCHAR txt[50];

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void Button1Click();
void dec2hexClick();
void hex2decClick();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DLLS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DLLS));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DLLS));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DLLS);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        CreateWindowW(L"Button", L"Sqr", WS_CHILD | WS_VISIBLE,
            10, 10, 75, 23, hWnd, (HMENU)CMD_BUTTON_1, hInst, NULL);
        inputhWnd = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT,
            10, 50, 75, 23, hWnd, 0, hInst, NULL);
        CreateWindowW(L"Button", L"Dec2Hex", WS_CHILD | WS_VISIBLE,
            95, 50, 75, 23, hWnd, (HMENU)CMD_BUTTON_4, hInst, NULL);
        reshWnd = CreateWindowW(L"Static", L"Result", WS_CHILD | WS_VISIBLE | ES_LEFT,
            175, 50, 75, 23, hWnd, 0, hInst, NULL);
        inputhWnd2 = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT,
            10, 90, 75, 23, hWnd, 0, hInst, NULL);
        CreateWindowW(L"Button", L"Hex2Dec", WS_CHILD | WS_VISIBLE,
            95, 90, 75, 23, hWnd, (HMENU)CMD_BUTTON_5, hInst, NULL);
        reshWnd2 = CreateWindowW(L"Static", L"Result", WS_CHILD | WS_VISIBLE | ES_LEFT,
            175, 90, 75, 23, hWnd, 0, hInst, NULL);
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case CMD_BUTTON_1:
            Button1Click();
            break;
        case CMD_BUTTON_4:
            dec2hexClick();
            break;
        case CMD_BUTTON_5:
            hex2decClick();
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
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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

void Button1Click() {
    HMODULE dll = LoadLibraryW(L"DllCreate.dll");
    if (dll == NULL) {
        MessageBoxW(NULL, L"Error", L"", MB_ICONERROR);
    }
    else {
        sqr_fun = (sqr_type)GetProcAddress(dll, "Cub");
        if (sqr_fun == NULL) {
            MessageBoxW(NULL, L"Error", L"", MB_OK | MB_ICONINFORMATION);
        }
        else {
            WCHAR str[50];
            long x = 3;
            _snwprintf_s(str, 50, L"%d ^ 3 = %d", x, sqr_fun(x));
            MessageBoxW(NULL, str, L"", MB_OK | MB_ICONINFORMATION);
        }
    }
}


void dec2hexClick() {
    HMODULE dll = LoadLibraryW(L"DllCreate.dll");
    if (dll == NULL) {
        MessageBoxW(NULL, L"Error", L"", MB_ICONERROR);
    }
    else {
        dec_hex = (Dec_Hex_type)GetProcAddress(dll, "dec2hex");
        if (dec_hex == NULL) {
            MessageBoxW(NULL, L"Error", L"", MB_OK | MB_ICONINFORMATION);
        }
        else {
            char dec[50];
            char hex[50];
            SendMessageA(inputhWnd, WM_GETTEXT, 50, (LPARAM)dec);
            dec_hex(dec, hex);
            SendMessageA(reshWnd, WM_SETTEXT, 0, (LPARAM)hex);
        }
    }
}

void hex2decClick() {
    HMODULE dll = LoadLibraryW(L"DllCreate.dll");
    if (dll == NULL) {
        MessageBoxW(NULL, L"Error", L"", MB_ICONERROR);
    }
    else {
        hex_dec = (Dec_Hex_type)GetProcAddress(dll, "hex2dec");
        if (hex_dec == NULL) {
            MessageBoxW(NULL, L"Error", L"", MB_OK | MB_ICONINFORMATION);
        }
        else {
            char* dec = new char[50];
            char* hex = new char[50];
            SendMessageA(inputhWnd2, WM_GETTEXT, 50, (LPARAM)hex);
            hex_dec(hex, dec);
            SendMessageA(reshWnd2, WM_SETTEXT, 0, (LPARAM)dec);
        }
    }
}
