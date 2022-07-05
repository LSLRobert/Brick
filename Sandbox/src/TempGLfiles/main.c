#include "header.h"
#include "main.h"


// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
  LRESULT Result = 0;
  
  UNREFERENCED_PARAMETER(hInstance);
  
  UNREFERENCED_PARAMETER(hPrevInstance);
  
  UNREFERENCED_PARAMETER(lpCmdLine);
  
  UNREFERENCED_PARAMETER(nCmdShow);
  
  if (GameIsAlreadyRunning() == TRUE) 
  {
    MessageBoxA(NULL, "Another instance of the application is running!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    
    goto Exit;
  }
  
  // Monitor DPI Awareness
  SetDPIAware();
  
  // windows
  if (Result = CreateMainWindow() != ERROR_SUCCESS)
  {
    goto Exit;
  }
  
  // loop
  MSG Message = { 0 };
  gApplicationIsRunning = TRUE;
  
  while (gApplicationIsRunning == TRUE)
  {
    while (PeekMessageA(&Message, gApplicationWindow, 0, 0, PM_REMOVE))
    {
      DispatchMessageA(&Message);
    }
    
    ProcessPlayerInput();
    
    RenderFrameGraphics();
    
    // temp solution
    Sleep(1);
  }
  
  // Exit
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
      gApplicationIsRunning = FALSE;
      
      PostQuitMessage(0);
      
      break;
    }
    
    case WM_DESTROY:
    {
      ReleaseDC(gApplicationWindow, gDeviceContext);
      
      wglDeleteContext(gGlResource);
      
      break;
    }
    
    default:
    {
      Result = DefWindowProcA(WindowHandle, Message, WParam, LParam);
    }
  }
  
  return Result;
}


// CreateMainWindow
DWORD CreateMainWindow(void)
{
  DWORD Result = ERROR_SUCCESS;
  
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
  
  gApplicationWindow = CreateWindowExA(
    WS_EX_CLIENTEDGE, WindowClass.lpszClassName, APP_WINDOW_TITLE, 
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
    CW_USEDEFAULT, CW_USEDEFAULT, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, 
    NULL, NULL, GetModuleHandleA(NULL), NULL
  );
  
  if (gApplicationWindow == NULL)
  {
    Result = -1;
    
    MessageBoxA(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    
    goto Exit;
  }
  
  gMonitorInfo.cbSize = sizeof(MONITORINFO);
  
  u32 Monitor = GetMonitorInfoA(MonitorFromWindow(gApplicationWindow, MONITOR_DEFAULTTOPRIMARY), &gMonitorInfo);
  
  if (Monitor == 0) // Fail = 0
  {
    Result = 0x80261001; // ERROR_MONITOR_NO_DESCRIPTOR
    
    MessageBoxA(NULL, "Failed to get Monitor Info!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    
    goto Exit;
  }
  
  i32 MonitorWidth = gMonitorInfo.rcMonitor.right - gMonitorInfo.rcMonitor.left;
  
  i32 MonitorHeight = gMonitorInfo.rcMonitor.bottom - gMonitorInfo.rcMonitor.top;
  
  printf("MonitorWidth:  %i\n", MonitorWidth);
  printf("MonitorHeight: %i\n", MonitorHeight);
  
  CreateWindowGlContext();
  
Exit:
  
  return Result;
}


// CreateWindowGlContext
DWORD CreateWindowGlContext(void)
{
  DWORD Result = 0;
  
  u32  PixelFormat;
  
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
    0,                     // no alpha buffer
    0,                     // shift bit ignored
    0,                     // no accumulation buffer
    0, 0, 0, 0,            // accum bits ignored
    32,                    // 32-bit z-buffer
    0,                     // no stencil buffer
    0,                     // no auxiliary buffer
    PFD_MAIN_PLANE,        // main layer
    0,                     // reserved
    0, 0, 0                // layer masks ignored
  };
  
  gDeviceContext = GetDC(gApplicationWindow);
  // Fail = NULL
  
  PixelFormat = ChoosePixelFormat(gDeviceContext, &PixelFormatDescriptor);
  // Fail = 0, GetLastError
  
  Result = SetPixelFormat(gDeviceContext, PixelFormat, &PixelFormatDescriptor);
  // Fail = FALSE, GetLastError
  
  gGlResource = wglCreateContext(gDeviceContext);
  // Fail = NULL, GetLastError
  
  wglMakeCurrent(gDeviceContext, gGlResource);
  // Fail = FALSE, GetLastError
  
//  gladLoadGL();
  gladLoadGLVersion(4, 5);
  // Fail = 0
  
  if (Result == FALSE)
  {
    u32 error = GetLastError();
    
    MessageBoxA(NULL, "Failed to get Window GL Context!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    
    goto Exit;
  }
  
  glViewport(0, 0, APP_RESOLUTION_WIDTH, APP_RESOLUTION_HEIGHT);
  
  printf("Vendor:   %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Version:  %s\n", glGetString(GL_VERSION));
  
Exit:
  
  return Result;
}


// GameIsAlreadyRunning
DWORD GameIsAlreadyRunning(void)
{
  DWORD Result = 0;
  
  HANDLE Mutex = NULL;
  
  Mutex = CreateMutexA(NULL, FALSE, APP_NAME "_GameMutex");
  
  if (GetLastError() == ERROR_ALREADY_EXISTS)
  {
    Result = TRUE;
  }
  else
  {
    Result = FALSE;
  }
  
  return Result;
}


// ProcessPlayerInput
void ProcessPlayerInput(void)
{
  i16 EscapeKeyIsDown = GetAsyncKeyState(VK_ESCAPE);
  
  if (EscapeKeyIsDown != FALSE)
  {
    SendMessageA(gApplicationWindow, WM_CLOSE, 0, 0);
  }
  
}


// GetRegKeyValue
LSTATUS GetRegKeyValue(char* BufferData, HKEY hkey, char* RegKey, char* Key)
{
	DWORD BufferSize = 8192;
  
  LSTATUS Status = RegGetValueA(hkey, RegKey, Key, RRF_RT_REG_SZ, NULL, (PVOID)&BufferData[0], &BufferSize);
  
  if (Status != ERROR_SUCCESS) // Fail = system error code, Success = ERROR_SUCCESS
  {
    MessageBoxA(NULL, "Failed to get Registry Key Value!", "Error!", MB_ICONEXCLAMATION | MB_OK);
  }
  
  return Status;
}


// SetDPIAware
void SetDPIAware(void)
{
  // --- Monitor DPI Awareness ---
  char* RegKey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
  
  char BufferData[255];
  
  GetRegKeyValue(&BufferData[0], HKEY_LOCAL_MACHINE, RegKey, "CurrentVersion");
  
  GetRegKeyValue(&BufferData[0], HKEY_LOCAL_MACHINE, RegKey, "ReleaseId");
  
  f32 Version = atof(BufferData);
  
  i32 Release = atoi(BufferData);
  
  // DONE:: set through the Application Manifest
  if (Version >= 6.2f)
  {
    if (Release < 1607) // Windows 8.1
    {
//      SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
      printf("Windows 8.1\n");
    }
    else // Windows 10, version 1607
    {
//      SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
      printf("Windows 10, version %i\n", Release);
    }
  }
  else // Windows Vista & 7
  {
//    SetProcessDPIAware();
    printf("Windows Vista & 7\n");
  }
  
}


// RenderFrameGraphics
void RenderFrameGraphics(void)
{
  glClearColor(0.8f, 0.4f, 0.1f, 1.0f);
  
  glClear(GL_COLOR_BUFFER_BIT);
  
  SwapBuffers(gDeviceContext);
}

