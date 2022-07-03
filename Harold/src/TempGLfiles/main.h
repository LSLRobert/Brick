#ifndef MAIN_H
#define MAIN_H

// defines
#define APP_NAME                "My Game"

#define APP_WINDOW_TITLE        "Window Title"

#define APP_WINDOW_WIDTH        640

#define APP_WINDOW_HEIGHT       480

#define APP_RESOLUTION_WIDTH    384

#define APP_RESOLUTION_HEIGHT   240


// Global Variables
HANDLE gApplicationWindow;

bool gApplicationIsRunning;

MONITORINFO gMonitorInfo;

HDC gDeviceContext;

HGLRC gGlResource;


// Declaration
int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, INT);

LRESULT CALLBACK MainWindowProcedures(HWND, UINT, WPARAM, LPARAM);

DWORD CreateMainWindow(void);

DWORD CreateWindowGlContext(void);

DWORD GameIsAlreadyRunning(void);

LSTATUS GetRegKeyValue(char*, HKEY, char*, char*);

void SetDPIAware(void);

void ProcessPlayerInput(void);

void RenderFrameGraphics(void);

#endif // MAIN_H
