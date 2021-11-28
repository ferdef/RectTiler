#include "framework.h"
#include "shellapi.h"
#include "WindowManager.h"
#include "RectTiler.h"

HINSTANCE hInst; // current instance

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
INT_PTR CALLBACK    DlgProc(HWND, UINT, WPARAM, LPARAM);

void                ExitTiler(HWND);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RECTTILER));

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

    return (int) msg.wParam;
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

   HWND hWnd = CreateDialog( hInstance,
       MAKEINTRESOURCE(IDD_ABOUTBOX),
       NULL,
       (DLGPROC)DlgProc);
   
   if (!hWnd)
   {
      return FALSE;
   }
   
   RegisterKeys(hWnd);
   CreateSystemTray(hInst, hWnd);
   
   return TRUE;
}

void ExitTiler(HWND hWnd)
{
    DeregisterEverything();    
    DestroyWindow(hWnd);
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_HOTKEY:
        PositionWindow((int)wParam);
        break;
    case MY_TRAY_ICON_MESSAGE:
        switch (lParam)
        {
        case WM_LBUTTONDBLCLK:
            ShowWindow(hDlg,  SW_RESTORE);
            break;
        case WM_RBUTTONUP:
            ExitTiler(hDlg);
            break;
        }
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            ExitTiler(hDlg);
        }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return (INT_PTR)FALSE;
}