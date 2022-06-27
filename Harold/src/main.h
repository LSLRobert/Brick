#ifndef MAIN_H
#define MAIN_H

int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, INT);
LRESULT CALLBACK MainWindowProcedures(HWND, UINT, WPARAM, LPARAM);
DWORD CreateMainWindow();
DWORD GameIsAlreadyRunning();

#define GAME_NAME           "My Game"
#define GAME_WINDOW_TITLE   "Window Title"

#endif // MAIN_H
