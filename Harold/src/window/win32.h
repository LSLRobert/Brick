////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 4, 2022
//
////////////////////////////////////////////////////////////
#ifndef LS_WIN32_H
#define LS_WIN32_H

// Structures
typedef struct MainArgs
{
  HINSTANCE hInstance;
  HINSTANCE hPrevInstance;
  PSTR lpCmdLine;
  INT nCmdShow;
  
} MainArgs;

typedef struct WindowData // non Platform
{
  LS_Window window;
  LS_Window deviceContext;
  LS_Window resourceGL;
  LS_String title;
  i32 width;
  i32 height;
  i32 major;
  i32 minor;
  i32 viewportWidth;
  i32 viewportHeight;
  i32 monitorWidth;
  i32 monitorHeight;
  bool fullscreen;
  bool isRunning;
  bool multiRun;
  bool windowSet;
  LS_String vendorGL;
  LS_String renderGL;
  LS_String versionGL;
  
} WindowData;

// Global Variables
MainArgs gMainArgs;
WindowData gWindowData;

// Internal
void WindowSetData();
void c_glGetString();
i32 CreateMainWindow(void);
i32 CreateWindowGlContext(void);
bool IsAlreadyRunning(void);
LSTATUS GetRegKeyValue(u8* BufferData, HKEY hkey, u8* RegKey, u8* Key);
LRESULT CALLBACK MainWindowProcedures(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam);
HDC GetDeviceContext();

#endif // LS_WIN32_H

///////////////////////////
// EOF
///////////////////////////
