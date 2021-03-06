#pragma once

#define LEFT_HOTKEY_ID 1
#define RIGHT_HOTKEY_ID 2
#define TOP_LEFT_HOTKEY_ID 3
#define TOP_RIGHT_HOTKEY_ID 4
#define BOTTOM_LEFT_HOTKEY_ID 5
#define BOTTOM_RIGHT_HOTKEY_ID 6
#define TOP_HOTKEY_ID 7
#define BOTTOM_HOTKEY_ID 8
#define MY_TRAY_ICON_ID 1
#define MY_TRAY_ICON_MESSAGE 10

void RegisterKeys(HWND);
void DeregisterEverything(void);
void PositionWindow(int);
void CreateSystemTray(HINSTANCE, HWND);