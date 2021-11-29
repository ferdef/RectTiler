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
    
    RECT currentWindowRect;
    GetWindowRect(hWnd, &currentWindowRect);
    currentWindowRect.right -= currentWindowRect.left;
    currentWindowRect.bottom -= currentWindowRect.top;
    RECT windowRect;

    switch (option)
    {
    case LEFT_HOTKEY_ID:
        windowRect = GetWindowLeft(rectScreen, currentWindowRect);
        break;
    case RIGHT_HOTKEY_ID:
        windowRect = GetWindowRight(rectScreen, currentWindowRect);
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

RECT* GetLeftRects(RECT rectScreen, RECT* rects)
{
    SIZE size = GetScreenSize(rectScreen);

    rects[0] = {
        rectScreen.left,
        rectScreen.top,
        2 * (size.cx / 3),
        size.cy
    };
    rects[1] = {
        rectScreen.left,
        rectScreen.top,
        size.cx / 2,
        size.cy
    };
    rects[2] = {
        rectScreen.left,
        rectScreen.top,
        (size.cx / 3),
        size.cy
    };

    return rects;
}

RECT* GetRightRects(RECT rectScreen, RECT* rects)
{
    SIZE size = GetScreenSize(rectScreen);

    rects[0] = {
        rectScreen.right - (2 * (size.cx / 3)),
        rectScreen.top,
        2 * (size.cx / 3),
        size.cy
    };
    rects[1] = {
        rectScreen.right - (size.cx / 2),
        rectScreen.top,
        size.cx / 2,
        size.cy
    };
    rects[2] = {
        rectScreen.right - (size.cx / 3),
        rectScreen.top,
        (size.cx / 3),
        size.cy
    };

    return rects;
}

int GetRect(RECT* rects, RECT currentWindowRect)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        if (rects[i].left == currentWindowRect.left &&
            rects[i].top == currentWindowRect.top &&
            rects[i].right == currentWindowRect.right &&
            rects[i].bottom == currentWindowRect.bottom)
        {
            break;
        }
    }

    i++;
    if (i >= 3) i = 0;

    return i;
}

RECT GetWindowLeft(RECT rectScreen, RECT currentWindowRect)
{
    RECT rects[3];
    GetLeftRects(rectScreen, rects); 
    int index = GetRect(rects, currentWindowRect);

    return rects[index];
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

RECT GetWindowRight(RECT rectScreen, RECT currentWindowRect)
{
    RECT rects[3];
    GetRightRects(rectScreen, rects);
    int index = GetRect(rects, currentWindowRect);

    return rects[index];
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