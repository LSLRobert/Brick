////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 4, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "win32.h"


// Structures non Platform
typedef struct WindowData
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
  bool windowSet;
  string vendorGL;
  string renderGL;
  string versionGL;
  
} WindowData;

// Global Variables
WindowData gWindowData;


// WindowSetViewport
HAROLD_API void WindowSetViewport(i32 width, i32 height)
{
  if (!gWindowData.windowSet) WindowSetData();
  if(width > 0 && height > 0)
  {
    gWindowData.viewportWidth = width; gWindowData.viewportHeight = height;
  }
}

// WindowGetViewportWidth
HAROLD_API i32 WindowGetViewportWidth()
{
  if (!gWindowData.windowSet) WindowSetData();
  return gWindowData.viewportWidth;
}

// WindowGetViewportHeight
HAROLD_API i32 WindowGetViewportHeight()
{
  if (!gWindowData.windowSet) WindowSetData();
  return gWindowData.viewportHeight;
}


// WindowSetVersionGL
HAROLD_API void WindowSetVersionGL(i32 major, i32 minor)
{
  if (!gWindowData.windowSet) WindowSetData();
  if (major > 0)
  {
    gWindowData.major = major; gWindowData.minor = minor;
  }
}

// WindowGetVersionGLMajor
HAROLD_API i32 WindowGetVersionGLMajor()
{
  if (!gWindowData.windowSet) WindowSetData();
  return gWindowData.major;
}

// WindowGetVersionGLMinor
HAROLD_API i32 WindowGetVersionGLMinor()
{
  if (!gWindowData.windowSet) WindowSetData();
  return gWindowData.minor;
}


// WindowCreateGL
HAROLD_API Window WindowCreateGL(string title, i32 width, i32 height, bool fullscreen)
{
  if (!gWindowData.windowSet) WindowSetData();
//  Window  gWindowData.window;
//  string  gWindowData.title;
//  i32     gWindowData.width;
//  i32     gWindowData.height;
//  i32     gWindowData.major;
//  i32     gWindowData.minor;
//  i32     gWindowData.viewportWidth;
//  i32     gWindowData.viewportHeight;
//  bool    gWindowData.fullscreen;
//  bool    gWindowData.windowSet;
//  string  gWindowData.vendorGL;
//  string  gWindowData.renderGL;
//  string  gWindowData.versionGL;
  
  CreateMainWindow();
  CreateWindowGlContext();
  
  return gWindowData.window;
}


// WindowGetVendorGL
HAROLD_API string WindowGetVendorGL()
{
  return gWindowData.vendorGL;
}

// WindowGetRenderGL
HAROLD_API string WindowGetRenderGL()
{
  return gWindowData.renderGL;
}

// WindowGetVersionGL
HAROLD_API string WindowGetVersionGL()
{
  return gWindowData.versionGL;
}


///////////////////////////
// Internal
///////////////////////////
void WindowSetData()
{
  gWindowData.window = 0;
  gWindowData.title  = APP_NAME;
  gWindowData.width  = APP_RESOLUTION_WIDTH;
  gWindowData.height = APP_RESOLUTION_HEIGHT;
  gWindowData.major  = 3;
  gWindowData.minor  = 3;
  gWindowData.viewportWidth  = APP_RESOLUTION_WIDTH;
  gWindowData.viewportHeight = APP_RESOLUTION_HEIGHT;
  gWindowData.fullscreen = false;
  gWindowData.windowSet = true;
}


// CreateMainWindow
int CreateMainWindow(void)
{
  int Result = 0; // ERROR_SUCCESS
  
  WNDCLASSEXA WindowClass = { sizeof(WNDCLASSEXA) };
  WindowClass.style = 0;
  WindowClass.lpfnWndProc = MainWindowProcedures;
  WindowClass.cbClsExtra = 0;
  WindowClass.cbWndExtra = 0;
  WindowClass.hInstance = GetModuleHandleA(NULL);
  WindowClass.hIcon = LoadIconA(NULL, IDI_APPLICATION);
  WindowClass.hIconSm = LoadIconA(NULL, IDI_APPLICATION);
  WindowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);
  WindowClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
  WindowClass.lpszMenuName = NULL;
  WindowClass.lpszClassName = APP_NAME "_WINDOWCLASS";
  
  if (RegisterClassExA(&WindowClass) == 0)
  {
    Result = GetLastError();
    MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto Exit;
  }
  
  gWindowData.window = CreateWindowExA(
    WS_EX_CLIENTEDGE, WindowClass.lpszClassName, gWindowData.title, 
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
    CW_USEDEFAULT, CW_USEDEFAULT, gWindowData.width, gWindowData.height, 
    NULL, NULL, GetModuleHandleA(NULL), NULL
  );
  
  if (gWindowData.window == NULL)
  {
    Result = -1;
    MessageBoxA(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto Exit;
  }
  
  MONITORINFO gMonitorInfo = { sizeof(MONITORINFO) };
  u32 Monitor = GetMonitorInfoA(MonitorFromWindow(gWindowData.window, MONITOR_DEFAULTTOPRIMARY), &gMonitorInfo);
  if (Monitor == 0) // Fail = 0
  {
    Result = 0x80261001; // ERROR_MONITOR_NO_DESCRIPTOR
    MessageBoxA(NULL, "Failed to get Monitor Info!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto Exit;
  }
  
  gWindowData.monitorWidth = gMonitorInfo.rcMonitor.right - gMonitorInfo.rcMonitor.left;
  gWindowData.monitorHeight = gMonitorInfo.rcMonitor.bottom - gMonitorInfo.rcMonitor.top;
  printf("Monitor Width/Height:  %d, %d\n", gWindowData.monitorWidth, gWindowData.monitorHeight);
  
Exit:
  
  return Result;
}

// c_glGetString
void c_glGetString()
{
  const string VendorGL = (string)(const char*)glGetString(GL_VENDOR);
  const string RenderGL = (string)(const char*)glGetString(GL_RENDERER);
  const string VersionGL = (string)(const char*)glGetString(GL_VERSION);
  
  gWindowData.vendorGL = (string)malloc(strlen(VendorGL) + 1);
  gWindowData.renderGL = (string)malloc(strlen(RenderGL) + 1);
  gWindowData.versionGL = (string)malloc(strlen(VersionGL) + 1);
  
  strcpy(gWindowData.vendorGL, VendorGL);
  strcpy(gWindowData.renderGL, RenderGL);
  strcpy(gWindowData.versionGL, VersionGL);
}

// CreateWindowGlContext
int CreateWindowGlContext(void)
{
  int Result = 0;
  u32 PixelFormat;
  
  PIXELFORMATDESCRIPTOR PixelFormatDescriptor =
  {
    sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd
    1,                     // version number
    PFD_DRAW_TO_WINDOW |   // support window
    PFD_SUPPORT_OPENGL |   // support OpenGL
    PFD_DOUBLEBUFFER,      // double buffered
    PFD_TYPE_RGBA,         // RGBA type
    24,                    // 24-bit color depth
    0, 0, 0, 0, 0, 0,      // color bits ignored
    0, 0, 0,               // no alpha buffer, shift bit ignored, no accumulation buffer
    0, 0, 0, 0,            // accum bits ignored
    32,                    // 32-bit z-buffer
    0, 0,                  // no stencil buffer, no auxiliary buffer
    PFD_MAIN_PLANE,        // main layer
    0, 0, 0, 0             // reserved, 3x layer masks ignored
  };
  
  gWindowData.deviceContext = GetDC(gWindowData.window);
  // Fail = NULL
  
  PixelFormat = ChoosePixelFormat(gWindowData.deviceContext, &PixelFormatDescriptor);
  // Fail = 0, GetLastError
  
  Result = SetPixelFormat(gWindowData.deviceContext, PixelFormat, &PixelFormatDescriptor);
  // Fail = FALSE, GetLastError
  
  gWindowData.resourceGL = wglCreateContext(gWindowData.deviceContext);
  // Fail = NULL, GetLastError
  
  wglMakeCurrent(gWindowData.deviceContext, gWindowData.resourceGL);
  // Fail = FALSE, GetLastError
  
//  gladLoadGL();
  gladLoadGLVersion(gWindowData.major, gWindowData.minor);
  // Fail = 0
  
  if (Result == FALSE)
  {
    u32 error = GetLastError();
    MessageBoxA(NULL, "Failed to get Window GL Context!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto Exit;
  }
  
  glViewport(0, 0, APP_RESOLUTION_WIDTH, APP_RESOLUTION_HEIGHT);
  
  c_glGetString();
  printf("Vendor:  %s\n", gWindowData.vendorGL);
  printf("Render:  %s\n", gWindowData.renderGL);
  printf("Version: %s\n", gWindowData.versionGL);
  
Exit:
  
  return Result;
}


// MainWindowProcedures
LRESULT CALLBACK MainWindowProcedures(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
{
  LRESULT Result = 0;
  
  switch (Message)
  {
//    case WM_SIZE:
//  glViewport(0, 0, APP_RESOLUTION_WIDTH, APP_RESOLUTION_HEIGHT);
    
    case WM_CLOSE:
    {
//      gApplicationIsRunning = FALSE;
      PostQuitMessage(0);
      break;
    }
    
    case WM_DESTROY:
    {
      ReleaseDC(gWindowData.window, gWindowData.deviceContext);
      wglDeleteContext(gWindowData.resourceGL);
      break;
    }
    
    default:
    {
      Result = DefWindowProcA(WindowHandle, Message, WParam, LParam);
    }
  }
  
  return Result;
}

///////////////////////////
// EOF
///////////////////////////
