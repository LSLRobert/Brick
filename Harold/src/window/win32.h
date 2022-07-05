////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 4, 2022
//
////////////////////////////////////////////////////////////
#ifndef WIN32_H
#define WIN32_H

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
  Window window;
  Window deviceContext;
  Window resourceGL;
  string title;
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
  string vendorGL;
  string renderGL;
  string versionGL;
  
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

#endif // WIN32_H

///////////////////////////
// EOF
///////////////////////////
