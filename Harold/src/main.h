#ifndef MAIN_H
#define MAIN_H

// defines
#define APP_NAME                "My Game"

#define APP_WINDOW_TITLE        "Window Title"

#define APP_WINDOW_WIDTH        640

#define APP_WINDOW_HEIGHT       480

#define APP_RESOLUTION_WIDTH    384

#define APP_RESOLUTION_HEIGHT   240

#define APP_RESOLUTION_BPP      32

#define APP_RESOLUTION_MEMORY   (APP_RESOLUTION_WIDTH * APP_RESOLUTION_HEIGHT * (APP_RESOLUTION_BPP / 8))

// structures
typedef struct GAMEBITMAP
{
  BITMAPINFO BitmapInfo;
  
  i32 Padding;
  
  void* Memory;
  
} GAMEBITMAP;

typedef struct PIXEL32
{
  u8 Red;
  
  u8 Green;
  
  u8 Blue;
  
  u8 Alpha;
  
} PIXEL32;


// Global Variables
HANDLE gApplicationWindow;

bool gApplicationIsRunning;

GAMEBITMAP gDrawingSurface;

MONITORINFO gMonitorInfo;


// Declaration
int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, INT);

LRESULT CALLBACK MainWindowProcedures(HWND, UINT, WPARAM, LPARAM);

DWORD CreateMainWindow(void);

DWORD GameIsAlreadyRunning(void);

void GetRegKeyValue(char*, HKEY, char*, char*);

void SetDPIAware(void);

void ProcessPlayerInput(void);

void RenderFrameGraphics(void);


#endif // MAIN_H
