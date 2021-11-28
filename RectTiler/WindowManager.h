#pragma once

#define LEFT_HOTKEY_ID 1
#define RIGHT_HOTKEY_ID 2
#define MY_TRAY_ICON_ID 1
#define MY_TRAY_ICON_MESSAGE 10

void RegisterKeys(HWND);
void DeregisterEverything(void);
void PositionWindow(int);
void CreateSystemTray(HINSTANCE, HWND);