// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
  LRESULT Result = 0;
  
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
    while (PeekMessageA(&Message, gWindowData.window, 0, 0, PM_REMOVE))
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
  
  SwapBuffers(gWindowData.deviceContext);
}




