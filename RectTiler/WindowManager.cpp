#include "framework.h"
#include "shellapi.h"
#include "WindowManager.h"
#include "resource.h"

NOTIFYICONDATA niData;

void RegisterKeys(HWND hWnd)
{
    RegisterHotKey(hWnd, LEFT_HOTKEY_ID, 6, VK_LEFT);
    RegisterHotKey(hWnd, RIGHT_HOTKEY_ID, 6, VK_RIGHT);
}

void DeregisterEverything(void)
{
    Shell_NotifyIcon(NIM_DELETE, &niData);
}

void PositionWindow(int option)
{
    RECT rectScreen;
    RECT rectWindow;

    HWND hWnd = GetForegroundWindow();
    HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFOEX info;
    info.cbSize = sizeof(info);

    GetMonitorInfo(monitor, (LPMONITORINFO)&info);
    rectScreen = info.rcWork;
    int screenWidth = rectScreen.right - rectScreen.left;
    int screenHeight = rectScreen.bottom - rectScreen.top;

    GetWindowRect(hWnd, &rectWindow);
    int windowWidth = rectWindow.right - rectWindow.left;
    int windowHeight = rectWindow.bottom - rectWindow.top;

    switch (option)
    {
    case LEFT_HOTKEY_ID:
        SetWindowPos(hWnd, NULL, rectScreen.left, rectScreen.top, 2 * (screenWidth / 3), screenHeight, SWP_NOZORDER);
        break;
    case RIGHT_HOTKEY_ID:
        SetWindowPos(hWnd, NULL, rectScreen.right - (2 * (screenWidth / 3)), rectScreen.top, 2 * (screenWidth / 3), screenHeight, SWP_NOZORDER);
        break;
    }
}

void CreateSystemTray(HINSTANCE hInst, HWND hWnd)
{

    ZeroMemory(&niData, sizeof(NOTIFYICONDATA));
    niData.cbSize = sizeof(NOTIFYICONDATA);
    niData.uID = MY_TRAY_ICON_ID;
    niData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    niData.hIcon = (HICON)LoadImage(
        hInst,
        MAKEINTRESOURCE(IDI_RECTTILER),
        IMAGE_ICON,
        GetSystemMetrics(SM_CXSMICON),
        GetSystemMetrics(SM_CYSMICON),
        LR_DEFAULTCOLOR);
    niData.hWnd = hWnd;
    niData.uCallbackMessage = MY_TRAY_ICON_MESSAGE;

    Shell_NotifyIcon(NIM_ADD, &niData);
}