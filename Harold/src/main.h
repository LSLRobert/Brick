#ifndef MAIN_H
#define MAIN_H

int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, INT);
LRESULT CALLBACK MainWindowProcedures(HWND, UINT, WPARAM, LPARAM);
DWORD CreateMainWindow(void);
DWORD GameIsAlreadyRunning(void);

void ProcessPlayerInput(void);
void RenderFrameGraphics(void);


#define GAME_NAME           "My Game"
#define GAME_WINDOW_TITLE   "Window Title"

// Global Variables
HANDLE gApplicationWindow;
bool gApplicationIsRunning;

#endif // MAIN_H
