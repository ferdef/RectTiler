# RectTiler
Small Tool to tile windows to 2/3 of the size of the screen

Current shortcuts:
* Ctrl + Shift + Left : Tile to Left side of current display. Repeating this combination will cycle among 2/3, 1/2 and 1/3 of the screen
* Ctrl + Shift + Right : Tile to Right side of current display. Repeating this combination will cycle among 2/3, 1/2 and 1/3 of the screen
* Ctrl + Shift + Alt + Left : Tile to Top Left side of current display
* Ctrl + Shift + Alt + Right : Tile to Top Right side of current display
* Shift + Alt + Left : Tile to Bottom Left side of current display
* Shift + Alt + Right : Tile to Bottom Right side of current display

## Changelog:

### 2021-11-30

* Removed unneeded code
* Window can now be resized to 1/3, 1/2 and 2/3 when attaching to Corners too

### 2021-11-28

* Removed unneeded code
* App shows shortcuts in Dialog.
* Dialog allows you to Exit the App
* Window can now be resized to 1/3, 1/2 and 2/3 when attaching to Left and Right borders
* Let user also place windows at the corners of the screen (top-left, top-right, bottom-left, bottom-right)

### 2021-11-27

* App opens and allows the user to relocate any active window to the left or right side of its current display, ocuppying 2/3 of such screen.
* A System Tray icon is placed and it shows a Dialog when left clicked while it closes the app when right clicked

## Missing Features

* Ability to change Keyboard shortcuts
* Let user place windows at the top half or bottom half of the screen

## Bugs

* Although the window is being horizontally positioned at 0, it still shows a gap between the screen edge and the window, most possibly caused by Aero and shadow sections. Needs to be handled
