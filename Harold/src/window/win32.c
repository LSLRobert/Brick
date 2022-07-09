////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 4, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "win32.h"


// WindowSetViewport
LS_HAROLD_API void LS_WindowSetViewport(i32 width, i32 height)
{
  if (!gWindowData.windowSet) WindowSetData();
  if(width > 0 && height > 0)
  {
    gWindowData.viewportWidth = width; gWindowData.viewportHeight = height;
  }
}


// WindowGetViewportWidth
LS_HAROLD_API i32 LS_WindowGetViewportWidth()
{
  if (!gWindowData.windowSet) WindowSetData();
  return gWindowData.viewportWidth;
}


// WindowGetViewportHeight
LS_HAROLD_API i32 LS_WindowGetViewportHeight()
{
  if (!gWindowData.windowSet) WindowSetData();
  return gWindowData.viewportHeight;
}


// WindowCreateGL
LS_HAROLD_API LS_Window LS_WindowCreateGL(LS_String title, i32 width, i32 height, bool fullscreen)
{
  i32 Result = 0;
  if (!gWindowData.windowSet) WindowSetData();
  
  if(width > 0 && height > 0)
  {
    gWindowData.width = width; gWindowData.height = height;
  }
  gWindowData.fullscreen = fullscreen;
  
  Result = CreateMainWindow();
  if (Result == 10101)
  {
    gWindowData.isRunning = false;
    goto Exit;
  }
  if (Result != 0) 
  {
    // Error:
    MessageBoxA(NULL, "Failed to get Create Window!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto Exit;
  }
  
  Result = CreateWindowGlContext();
  if (Result != 0) 
  {
    // Error:
    MessageBoxA(NULL, "Failed to get Window GL Context!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto Exit;
  }
  
Exit:
  
  if (Result) return (LS_Window)(i64)Result;
  else return gWindowData.window;
}


// WindowSetVersionGL
LS_HAROLD_API void LS_WindowSetVersionGL(i32 major, i32 minor)
{
  if (!gWindowData.windowSet) WindowSetData();
  if (major > 0)
  {
    gWindowData.major = major; gWindowData.minor = minor;
  }
}


// WindowGetVersionGLMajor
LS_HAROLD_API i32 LS_WindowGetVersionGLMajor()
{
  if (!gWindowData.windowSet) WindowSetData();
  return gWindowData.major;
}


// WindowGetVersionGLMinor
LS_HAROLD_API i32 LS_WindowGetVersionGLMinor()
{
  if (!gWindowData.windowSet) WindowSetData();
  return gWindowData.minor;
}


// WindowGetVendorGL
LS_HAROLD_API LS_String LS_WindowGetVendorGL()
{
  return gWindowData.vendorGL;
}


// WindowGetRenderGL
LS_HAROLD_API LS_String LS_WindowGetRenderGL()
{
  return gWindowData.renderGL;
}


// WindowGetVersionGL
LS_HAROLD_API LS_String LS_WindowGetVersionGL()
{
  return gWindowData.versionGL;
}


// IsApplicationRunning
LS_HAROLD_API bool LS_IsApplicationRunning()
{
  return gWindowData.isRunning;
}


// SetApplicationRunning
LS_HAROLD_API void LS_SetApplicationRunning(bool running)
{
  gWindowData.isRunning = running;
}


// LogCurrentWindowsVersion
LS_HAROLD_API void LS_LogCurrentWindowVersion(void)
{
  // DPI Awareness is set in the Application Manifest
  u8* RegKey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
  
  u8 BufferData0[255];
  GetRegKeyValue(&BufferData0[0], HKEY_LOCAL_MACHINE, RegKey, "CurrentVersion");
  f32 Version = atof(BufferData0);
  
  u8 BufferData1[255];
  GetRegKeyValue(&BufferData1[0], HKEY_LOCAL_MACHINE, RegKey, "ReleaseId");
  i32 Release = atoi(BufferData1);
  
  if (Version >= 6.2f)
  {
    if (Release < 1607) printf("Windows 8.1\n"); // Windows 8.1
    else printf("Windows 10, version %i\n", Release); // Windows 10, version 1607
  }
  else printf("Windows Vista & 7\n"); // Windows Vista & 7
}


///////////////////////////
// Internal
///////////////////////////
void WindowSetData()
{
  gWindowData.window = 0;
  gWindowData.title  = LS_APP_NAME;
  gWindowData.width  = LS_APP_RESOLUTION_WIDTH;
  gWindowData.height = LS_APP_RESOLUTION_HEIGHT;
  gWindowData.major  = 3;
  gWindowData.minor  = 3;
  gWindowData.viewportWidth  = LS_APP_RESOLUTION_WIDTH;
  gWindowData.viewportHeight = LS_APP_RESOLUTION_HEIGHT;
  gWindowData.fullscreen = false;
  gWindowData.isRunning = true;
  gWindowData.multiRun = false;
  gWindowData.windowSet = true;
}


// c_glGetString
void c_glGetString()
{
  const LS_String VendorGL  = (LS_String)(const u8*)glGetString(GL_VENDOR);
  const LS_String RenderGL  = (LS_String)(const u8*)glGetString(GL_RENDERER);
  const LS_String VersionGL = (LS_String)(const u8*)glGetString(GL_VERSION);
  
  gWindowData.vendorGL  = (LS_String)malloc(strlen(VendorGL) + 1);
  gWindowData.renderGL  = (LS_String)malloc(strlen(RenderGL) + 1);
  gWindowData.versionGL = (LS_String)malloc(strlen(VersionGL) + 1);
  
  strcpy(gWindowData.vendorGL, VendorGL);
  strcpy(gWindowData.renderGL, RenderGL);
  strcpy(gWindowData.versionGL, VersionGL);
}


// CreateMainWindow
i32 CreateMainWindow(void)
{
  i32 Result = 0; // ERROR_SUCCESS
  if (IsAlreadyRunning())
  {
    MessageBoxA(NULL, "This Application is Already Running!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    Result = 10101; // Exit NOW!!!
    goto Exit;
  }
  
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
  WindowClass.lpszClassName = LS_APP_NAME "_WINDOWCLASS";
  
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


// CreateWindowGlContext
i32 CreateWindowGlContext(void)
{
  i32 Result = 0;
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
  if (gWindowData.deviceContext == NULL) // Fail = NULL
  {
    Result = -1;
    MessageBoxA(NULL, "Failed to get Device Context!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto Exit;
  }
  
  PixelFormat = ChoosePixelFormat(gWindowData.deviceContext, &PixelFormatDescriptor);
  if (PixelFormat == 0) // Fail = 0, GetLastError
  {
    Result = GetLastError();
    MessageBoxA(NULL, "Failed to Choose Pixel Format!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto Exit;
  }
  
  bool format = SetPixelFormat(gWindowData.deviceContext, PixelFormat, &PixelFormatDescriptor);
  if (format == false) // Fail = false, GetLastError
  {
    Result = GetLastError();
    MessageBoxA(NULL, "Failed to Set Pixel Format!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto Exit;
  }
  
  gWindowData.resourceGL = wglCreateContext(gWindowData.deviceContext);
  if (gWindowData.resourceGL == NULL) // Fail = NULL, GetLastError
  {
    Result = GetLastError();
    MessageBoxA(NULL, "Failed to get GL Resource Context!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto Exit;
  }
  
  bool make = wglMakeCurrent(gWindowData.deviceContext, gWindowData.resourceGL);
  if (make == false) // Fail = false, GetLastError
  {
    Result = GetLastError();
    MessageBoxA(NULL, "Failed Make GL Window Current!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto Exit;
  }
  
  // Load OpenGl w/ gladLoadGL();
  bool load = gladLoadGLVersion(gWindowData.major, gWindowData.minor);
  if (load == 0) // Fail = 0
  {
    Result = -1;
    MessageBoxA(NULL, "Failed to Load OpenGL (glad)!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto Exit;
  }
  
  glViewport(0, 0, LS_APP_RESOLUTION_WIDTH, LS_APP_RESOLUTION_HEIGHT);
  
  c_glGetString();
  printf("Vendor:  %s\n", gWindowData.vendorGL);
  printf("Render:  %s\n", gWindowData.renderGL);
  printf("Version: %s\n", gWindowData.versionGL);
  
Exit:
  
  return Result;
}


// IsAlreadyRunning
bool IsAlreadyRunning(void)
{
  bool Result = false;
  if (!gWindowData.multiRun)
  {
    HANDLE Mutex = NULL;
    Mutex = CreateMutexA(NULL, false, LS_APP_NAME "_GameMutex");
    if (GetLastError() == ERROR_ALREADY_EXISTS) Result = true;
  }
  return Result;
}


// GetRegKeyValue
LSTATUS GetRegKeyValue(u8* BufferData, HKEY hkey, u8* RegKey, u8* Key)
{
	DWORD BufferSize = 8192;
  LSTATUS Status = RegGetValueA(hkey, RegKey, Key, RRF_RT_REG_SZ, NULL, (PVOID)&BufferData[0], &BufferSize);
  
  if (Status != ERROR_SUCCESS) // Fail = system error code, Success = ERROR_SUCCESS
  {
    MessageBoxA(NULL, "Failed to get Registry Key Value!", "Error!", MB_ICONEXCLAMATION | MB_OK);
  }
  
  return Status;
}


// MainWindowProcedures
LRESULT CALLBACK MainWindowProcedures(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
{
  LRESULT Result = 0;
  
  switch (Message)
  {
    case WM_SIZE:
    {
      puts("WM_SIZE  - CALLBACK\n");
      // TODO::TODO::TODO::TODO::TODO::TODO::TODO::
      // resize the window and reset the viewport if needed
      // send a RESIZE event to the EVENT system
      break;
    }
    
    case WM_CLOSE:
    {
      // TODO::TODO::TODO::TODO::TODO::TODO::TODO::
      // send a CLOSE message to the EVENT system
      // shutdown is handled by the APP, not the engine
      gWindowData.isRunning = false;
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


// GetDeviceContext
HDC GetDeviceContext()
{
  return gWindowData.deviceContext;
}


///////////////////////////
// EOF
///////////////////////////
