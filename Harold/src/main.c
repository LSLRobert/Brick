#include "header.h"
#include "main.h"


// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
  // TESTING:: BEGIN
  // from Window folder window.c
  CreateOurWindow();
  // from Window folder screen.c
  CreateScreen();
  
  // TESTING:: END
  
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
  
  gDrawingSurface.BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  
  gDrawingSurface.BitmapInfo.bmiHeader.biWidth  = APP_RESOLUTION_WIDTH;
  
  gDrawingSurface.BitmapInfo.bmiHeader.biHeight = APP_RESOLUTION_HEIGHT;
  
  gDrawingSurface.BitmapInfo.bmiHeader.biBitCount = APP_RESOLUTION_BPP;
  
  gDrawingSurface.BitmapInfo.bmiHeader.biCompression = BI_RGB;
  
  gDrawingSurface.BitmapInfo.bmiHeader.biPlanes = 1;
  
  gDrawingSurface.Memory = VirtualAlloc(0, APP_RESOLUTION_MEMORY, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  
  if (gDrawingSurface.Memory == NULL)
  {
    MessageBoxA(NULL, "Window Drawing Surface Memory Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    
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
    case WM_CLOSE:
    {
      gApplicationIsRunning = FALSE;
      
      PostQuitMessage(0);
      
      break;
    }
//    case WM_CREATE:
//    case WM_PAINT:
//    case WM_SIZE:
//    case WM_DESTROY:
    
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
  
  WindowClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
  
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
  
  if (Monitor == 0)
  {
    Result = 0x80261001; // ERROR_MONITOR_NO_DESCRIPTOR
    
    MessageBoxA(NULL, "Failed to get Monitor Info!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    
    goto Exit;
  }
  
  i32 MonitorWidth = gMonitorInfo.rcMonitor.right - gMonitorInfo.rcMonitor.left;
  
  i32 MonitorHeight = gMonitorInfo.rcMonitor.bottom - gMonitorInfo.rcMonitor.top;
  
  printf("MonitorWidth:  %i\n", MonitorWidth);
  printf("MonitorHeight: %i\n", MonitorHeight);
  
  
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
void GetRegKeyValue(char* BufferData, HKEY hkey, char* RegKey, char* Key)
{
	DWORD BufferSize = 8192;
  
  LSTATUS Status = RegGetValueA(hkey, RegKey, Key, RRF_RT_REG_SZ, NULL, (PVOID)&BufferData[0], &BufferSize);
  
  if (Status != ERROR_SUCCESS)
  {
    MessageBoxA(NULL, "Failed to get Registry Key Value!", "Error!", MB_ICONEXCLAMATION | MB_OK);
  }
  
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
  // ---------------------------
  // drawing
  i8* ptr = gDrawingSurface.Memory;
  
  // noise
//  srand((u32)((uint64_t)gDrawingSurface.Memory & 0xFFFFFFFF));
//  for (i32 i = 0; i < APP_RESOLUTION_MEMORY; i++)
//  {
//    ptr[i] = (char)rand()%256;
//  }
  
  // color
  PIXEL32 ClearColor = { 255, 127, 0, 255 }; // orange
  for (i32 i = 0; i < APP_RESOLUTION_MEMORY; i += 4)
  {
    ptr[i + 0] = ClearColor.Blue;
    ptr[i + 1] = ClearColor.Green;
    ptr[i + 2] = ClearColor.Red;
    ptr[i + 3] = ClearColor.Alpha;
  }
  
  // ---------------------------
  HDC DeviceContext = GetDC(gApplicationWindow);
  
  StretchDIBits(DeviceContext, 
  0, // [in] int xDest,
  0, // [in] int yDest,
  APP_WINDOW_WIDTH,  // [in] int DestWidth,
  APP_WINDOW_HEIGHT, // [in] int DestHeight,
  0, // [in] int xSrc,
  0, // [in] int ySrc,
  APP_RESOLUTION_WIDTH,  // [in] int SrcWidth,
  APP_RESOLUTION_HEIGHT, // [in] int SrcHeight,
  // --------------------
  gDrawingSurface.Memory,      // [in] const VOID       *lpBits,
  &gDrawingSurface.BitmapInfo, // [in] const BITMAPINFO *lpbmi,
  DIB_RGB_COLORS,             // [in] UINT             iUsage,
  SRCCOPY                     // [in] DWORD            rop
  );
  
  ReleaseDC(gApplicationWindow, DeviceContext);
}

