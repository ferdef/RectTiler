#include "framework.h"
#include "shellapi.h"
#include "WindowManager.h"
#include "resource.h"

NOTIFYICONDATA niData;

void RegisterKeys(HWND hWnd)
{
    RegisterHotKey(hWnd, LEFT_HOTKEY_ID, 6, VK_LEFT);
    RegisterHotKey(hWnd, RIGHT_HOTKEY_ID, 6, VK_RIGHT);
    RegisterHotKey(hWnd, TOP_LEFT_HOTKEY_ID, 7, VK_LEFT);
    RegisterHotKey(hWnd, TOP_RIGHT_HOTKEY_ID, 7, VK_RIGHT);
    RegisterHotKey(hWnd, BOTTOM_LEFT_HOTKEY_ID, 5, VK_LEFT);
    RegisterHotKey(hWnd, BOTTOM_RIGHT_HOTKEY_ID, 5, VK_RIGHT);
}

void DeregisterEverything(void)
{
    Shell_NotifyIcon(NIM_DELETE, &niData);
}

void PositionWindow(int option)
{
    RECT rectScreen;

    HWND hWnd = GetForegroundWindow();
    HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFOEX info;
    info.cbSize = sizeof(info);

    GetMonitorInfo(monitor, (LPMONITORINFO)&info);
    rectScreen = info.rcWork;
    
    RECT windowRect;

    switch (option)
    {
    case LEFT_HOTKEY_ID:
        windowRect = GetWindowLeft(rectScreen);
        break;
    case RIGHT_HOTKEY_ID:
        windowRect = GetWindowRight(rectScreen);
        break;
    case TOP_LEFT_HOTKEY_ID:
        windowRect = GetWindowTopLeft(rectScreen);
        break;
    case TOP_RIGHT_HOTKEY_ID:
        windowRect = GetWindowTopRight(rectScreen);
        break;
    case BOTTOM_LEFT_HOTKEY_ID:
        windowRect = GetWindowBottomLeft(rectScreen);
        break;
    case BOTTOM_RIGHT_HOTKEY_ID:
        windowRect = GetWindowBottomRight(rectScreen);
        break;

    default:
        return;
    }
    SetWindowPos(hWnd, NULL, windowRect.left, windowRect.top, windowRect.right, windowRect.bottom, SWP_NOZORDER);
}

SIZE GetScreenSize(RECT rectScreen)
{
    SIZE size = {
        rectScreen.right - rectScreen.left,
        rectScreen.bottom - rectScreen.top
    };
    return size;
}

RECT GetWindowLeft(RECT rectScreen)
{
    SIZE size = GetScreenSize(rectScreen);

    RECT rect = {
        rectScreen.left,
        rectScreen.top,
        2 * (size.cx / 3),
        size.cy
    };

    return rect;
}

RECT GetWindowTopLeft(RECT rectScreen)
{
    SIZE size = GetScreenSize(rectScreen);

    RECT rect = {
        rectScreen.left,
        rectScreen.top,
        2 * (size.cx / 3),
        size.cy / 2
    };

    return rect;
}

RECT GetWindowBottomLeft(RECT rectScreen)
{
    SIZE size = GetScreenSize(rectScreen);

    RECT rect = {
        rectScreen.left,
        rectScreen.top + (size.cy / 2),
        2 * (size.cx / 3),
        size.cy / 2
    };

    return rect;
}

RECT GetWindowRight(RECT rectScreen)
{
    SIZE size = GetScreenSize(rectScreen);

    RECT rect = {
        rectScreen.right - (2 * (size.cx / 3)), 
        rectScreen.top, 
        2 * (size.cx / 3), 
        size.cy
    };

    return rect;
}

RECT GetWindowTopRight(RECT rectScreen)
{
    SIZE size = GetScreenSize(rectScreen);

    RECT rect = {
        rectScreen.right - (2 * (size.cx / 3)),
        rectScreen.top,
        2 * (size.cx / 3),
        size.cy / 2
    };

    return rect;
}

RECT GetWindowBottomRight(RECT rectScreen)
{
    SIZE size = GetScreenSize(rectScreen);

    RECT rect = {
        rectScreen.right - (2 * (size.cx / 3)),
        rectScreen.top + (size.cy / 2),
        2 * (size.cx / 3),
        size.cy / 2
    };

    return rect;
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