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
  
  // windows
  if (Result = CreateMainWindow() != ERROR_SUCCESS)
  {
    goto Exit;
  }
  
  // loop
  MSG Message = { 0 };
  while (GetMessageA(&Message, NULL, 0, 0) > 0)
  {
    // run run run
    TranslateMessage(&Message);
    
    DispatchMessageA(&Message);
    
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
DWORD CreateMainWindow()
{
  DWORD Result = ERROR_SUCCESS;
  
  WNDCLASSEXA WindowClass = { sizeof(WNDCLASSEXA) };
  
  HWND WindowHandle = NULL;
  
  WindowClass.style = 0;
  
  WindowClass.lpfnWndProc = MainWindowProcedures;
  
  WindowClass.cbClsExtra = 0;
  
  WindowClass.cbWndExtra = 0;
  
  WindowClass.hInstance = GetModuleHandleA(NULL);
  
  WindowClass.hIcon = LoadIconA(NULL, IDI_APPLICATION);
  
  WindowClass.hIconSm = LoadIconA(NULL, IDI_APPLICATION);
  
  WindowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);
  
  WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  
  WindowClass.lpszMenuName = NULL;
  
  WindowClass.lpszClassName = GAME_NAME "_WINDOWCLASS";
  
  if (RegisterClassExA(&WindowClass) == 0)
  {
    Result = GetLastError();
    
    MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    
    goto Exit;
  }
  
  WindowHandle = CreateWindowExA(
    WS_EX_CLIENTEDGE, WindowClass.lpszClassName, GAME_WINDOW_TITLE, 
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
    CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, 
    NULL, NULL, GetModuleHandleA(NULL), NULL
  );
  
  if (WindowHandle == NULL)
  {
    Result = -1;
    
    MessageBoxA(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    
    goto Exit;
  }
  
Exit:
  
  return Result;
}


// GameIsAlreadyRunning
DWORD GameIsAlreadyRunning()
{
  DWORD Result = 0;
  
  HANDLE Mutex = NULL;
  
  Mutex = CreateMutexA(NULL, FALSE, GAME_NAME "_GameMutex");
  
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

