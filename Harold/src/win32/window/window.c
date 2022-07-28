////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 4, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "window_int.h"


/* WindowSetViewport */
LS_HAROLD_API void ls_window_set_viewport(i32 width, i32 height)
{
  if (!g_window_data.window_set) window_set_data();
  if(width > 0 && height > 0)
  {
    g_window_data.viewport_width = width; g_window_data.viewport_height = height;
  }
}


/* WindowGetViewportWidth */
LS_HAROLD_API i32 ls_window_get_viewport_width(void)
{
  if (!g_window_data.window_set) window_set_data();
  return g_window_data.viewport_width;
}


/* WindowGetViewportHeight */
LS_HAROLD_API i32 ls_window_get_viewport_height(void)
{
  if (!g_window_data.window_set) window_set_data();
  return g_window_data.viewport_height;
}


/* WindowCreateGL */
LS_HAROLD_API ls_window ls_window_create_gl(ls_string title, i32 width, i32 height, bool fullscreen)
{
  i32 result = 0;
  if (!g_window_data.window_set) window_set_data();
  
  if(width > 0 && height > 0)
  {
    g_window_data.width = width; g_window_data.height = height;
  }
  g_window_data.fullscreen = fullscreen;
  
  result = create_main_window();
  if (result == 10101)
  {
    g_window_data.is_running = false;
    goto exit;
  }
  if (result != 0) 
  {
    /* error: */
    MessageBoxA(NULL, "failed to get create window!", "error!", MB_ICONEXCLAMATION | MB_OK);
    goto exit;
  }
  
  result = create_window_gl_context();
  if (result != 0) 
  {
    /* error: */
    MessageBoxA(NULL, "failed to get window gl context!", "error!", MB_ICONEXCLAMATION | MB_OK);
    goto exit;
  }
  
exit:
  
  if (result) return (ls_window)(i64)result;
  else return g_window_data.window;
}


/* WindowSetVersionGL */
LS_HAROLD_API void ls_window_set_version_gl(i32 major, i32 minor)
{
  if (!g_window_data.window_set) window_set_data();
  if (major > 0)
  {
    g_window_data.major = major; g_window_data.minor = minor;
  }
}


/* WindowGetVersionGLMajor */
LS_HAROLD_API i32 ls_window_get_version_gl_major(void)
{
  if (!g_window_data.window_set) window_set_data();
  return g_window_data.major;
}


/* WindowGetVersionGLMinor */
LS_HAROLD_API i32 ls_window_get_version_gl_minor(void)
{
  if (!g_window_data.window_set) window_set_data();
  return g_window_data.minor;
}


/* WindowGetVendorGL */
LS_HAROLD_API ls_string ls_window_get_vendor_gl(void)
{
  return g_window_data.vendor_gl;
}


/* WindowGetRenderGL */
LS_HAROLD_API ls_string ls_window_get_render_gl(void)
{
  return g_window_data.render_gl;
}


/* WindowGetVersionGL */
LS_HAROLD_API ls_string ls_window_get_version_gl()
{
  return g_window_data.version_gl;
}


/* IsApplicationRunning */
LS_HAROLD_API bool ls_is_application_running(void)
{
  return g_window_data.is_running;
}


/* SetApplicationRunning */
LS_HAROLD_API void ls_set_application_running(bool running)
{
  g_window_data.is_running = running;
}


/* LogCurrentWindowsVersion */
LS_HAROLD_API void ls_log_current_windows_version(void)
{
  /* dpi awareness is set in the application manifest */
  u8* regkey = "software\\microsoft\\windows nt\\currentversion";
  
  u8 bufferdata0[255];
  get_reg_key_value(&bufferdata0[0], HKEY_LOCAL_MACHINE, regkey, "currentversion");
  f32 version = atof(bufferdata0);
  
  u8 bufferdata1[255];
  get_reg_key_value(&bufferdata1[0], HKEY_LOCAL_MACHINE, regkey, "releaseid");
  i32 release = atoi(bufferdata1);
  
  if (version >= 6.2f)
  {
    /* windows 8.1 */
    if (release < 1607) printf("windows 8.1\n");
    /* windows 10, version 1607 */
    else printf("windows 10, version %i\n", release);
  }
  /* windows vista & 7 */
  else printf("windows vista & 7\n");
}


///////////////////////////
// Internal
///////////////////////////
void window_set_data(void)
{
  g_window_data.window = 0;
  g_window_data.title  = LS_APP_NAME;
  g_window_data.width  = LS_APP_RESOLUTION_WIDTH;
  g_window_data.height = LS_APP_RESOLUTION_HEIGHT;
  g_window_data.major  = 3;
  g_window_data.minor  = 3;
  g_window_data.viewport_width  = LS_APP_RESOLUTION_WIDTH;
  g_window_data.viewport_height = LS_APP_RESOLUTION_HEIGHT;
  g_window_data.fullscreen = false;
  g_window_data.is_running = true;
  g_window_data.multi_run = false;
  g_window_data.window_set = true;
}


/* c_glGetString */
void c_gl_get_string(void)
{
  const ls_string vendor_gl  = (ls_string)(const u8*)glGetString(GL_VENDOR);
  const ls_string render_gl  = (ls_string)(const u8*)glGetString(GL_RENDERER);
  const ls_string version_gl = (ls_string)(const u8*)glGetString(GL_VERSION);
  
  g_window_data.vendor_gl  = (ls_string)malloc(strlen(vendor_gl) + 1);
  g_window_data.render_gl  = (ls_string)malloc(strlen(render_gl) + 1);
  g_window_data.version_gl = (ls_string)malloc(strlen(version_gl) + 1);
  
  strcpy(g_window_data.vendor_gl, vendor_gl);
  strcpy(g_window_data.render_gl, render_gl);
  strcpy(g_window_data.version_gl, version_gl);
}


/* CreateMainWindow */
i32 create_main_window(void)
{
  i32 result = 0; /* ERROR_SUCCESS */
  if (is_already_running())
  {
    MessageBoxA(NULL, "This Application is Already Running!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    result = 10101; /* exit NOW!!! */
    goto exit;
  }
  
  WNDCLASSEXA window_class = { sizeof(WNDCLASSEXA) };
  window_class.style = 0;
  window_class.lpfnWndProc = main_window_procedures;
  window_class.cbClsExtra = 0;
  window_class.cbWndExtra = 0;
  window_class.hInstance = GetModuleHandleA(NULL);
  window_class.hIcon = LoadIconA(NULL, IDI_APPLICATION);
  window_class.hIconSm = LoadIconA(NULL, IDI_APPLICATION);
  window_class.hCursor = LoadCursorA(NULL, IDC_ARROW);
  window_class.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
  window_class.lpszMenuName = NULL;
  window_class.lpszClassName = LS_APP_NAME "_window_class";
  
  if (RegisterClassExA(&window_class) == 0)
  {
    result = GetLastError();
    MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto exit;
  }
  
  g_window_data.window = CreateWindowExA(
    WS_EX_CLIENTEDGE, window_class.lpszClassName, g_window_data.title, 
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
    CW_USEDEFAULT, CW_USEDEFAULT, g_window_data.width, g_window_data.height, 
    NULL, NULL, GetModuleHandleA(NULL), NULL
  );
  
  if (g_window_data.window == NULL)
  {
    result = -1;
    MessageBoxA(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto exit;
  }
  
  ZeroMemory(&g_monitor_info, sizeof(MONITORINFO));
  g_monitor_info.cbSize = sizeof(MONITORINFO);
  u32 Monitor = GetMonitorInfoA(MonitorFromWindow(g_window_data.window, MONITOR_DEFAULTTOPRIMARY), &g_monitor_info);
  if (Monitor == 0) /* Fail = 0 */
  {
    result = 0x80261001; /* ERROR_MONITOR_NO_DESCRIPTOR */
    MessageBoxA(NULL, "Failed to get Monitor Info!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto exit;
  }
  
  g_window_data.monitor_width = g_monitor_info.rcMonitor.right - g_monitor_info.rcMonitor.left;
  g_window_data.monitor_height = g_monitor_info.rcMonitor.bottom - g_monitor_info.rcMonitor.top;
  printf("Monitor Width/Height:  %d, %d\n", g_window_data.monitor_width, g_window_data.monitor_height);
  
exit:
  
  return result;
}


/* CreateWindowGlContext */
i32 create_window_gl_context(void)
{
  i32 result = 0;
  u32 pixel_format;
  
  PIXELFORMATDESCRIPTOR pixel_format_descriptor =
  {
    sizeof(PIXELFORMATDESCRIPTOR),  /* size of this pfd */
    1,                     /* version number */
    PFD_DRAW_TO_WINDOW |   /* support window */
    PFD_SUPPORT_OPENGL |   /* support OpenGL */
    PFD_DOUBLEBUFFER,      /* double buffered */
    PFD_TYPE_RGBA,         /* RGBA type */
    24,                    /* 24-bit color depth */
    0, 0, 0, 0, 0, 0,      /* color bits ignored */
    0, 0, 0,               /* no alpha buffer, shift bit ignored, no accumulation buffer */
    0, 0, 0, 0,            /* accum bits ignored */
    32,                    /* 32-bit z-buffer */
    0, 0,                  /* no stencil buffer, no auxiliary buffer */
    PFD_MAIN_PLANE,        /* main layer */
    0, 0, 0, 0             /* reserved, 3x layer masks ignored */
  };
  
  g_window_data.device_context = GetDC(g_window_data.window);
  if (g_window_data.device_context == NULL) /* Fail = NULL */
  {
    result = -1;
    MessageBoxA(NULL, "Failed to get Device Context!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto exit;
  }
  
  pixel_format = ChoosePixelFormat(g_window_data.device_context, &pixel_format_descriptor);
  if (pixel_format == 0) /* Fail = 0, GetLastError */
  {
    result = GetLastError();
    MessageBoxA(NULL, "Failed to Choose Pixel Format!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto exit;
  }
  
  bool format = SetPixelFormat(g_window_data.device_context, pixel_format, &pixel_format_descriptor);
  if (format == false) /* Fail = false, GetLastError */
  {
    result = GetLastError();
    MessageBoxA(NULL, "Failed to Set Pixel Format!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto exit;
  }
  
  g_window_data.resource_gl = wglCreateContext(g_window_data.device_context);
  if (g_window_data.resource_gl == NULL) /* Fail = NULL, GetLastError */
  {
    result = GetLastError();
    MessageBoxA(NULL, "Failed to get GL Resource Context!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto exit;
  }
  
  bool make = wglMakeCurrent(g_window_data.device_context, g_window_data.resource_gl);
  if (make == false) /* Fail = false, GetLastError */
  {
    result = GetLastError();
    MessageBoxA(NULL, "Failed Make GL Window Current!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto exit;
  }
  
  /* Load OpenGl w/ gladLoadGL(); */
  bool load = gladLoadGLVersion(g_window_data.major, g_window_data.minor);
  if (load == 0) /* Fail = 0 */
  {
    result = -1;
    MessageBoxA(NULL, "Failed to Load OpenGL (glad)!", "Error!", MB_ICONEXCLAMATION | MB_OK);
    goto exit;
  }
  
  glViewport(0, 0, LS_APP_RESOLUTION_WIDTH, LS_APP_RESOLUTION_HEIGHT);
  
  c_gl_get_string();
  printf("Vendor:  %s\n", g_window_data.vendor_gl);
  printf("Render:  %s\n", g_window_data.render_gl);
  printf("Version: %s\n", g_window_data.version_gl);
  
exit:
  
  return result;
}


/* is_already_running */
bool is_already_running(void)
{
  bool result = false;
  if (!g_window_data.multi_run)
  {
    HANDLE mutex = NULL;
    mutex = CreateMutexA(NULL, false, LS_APP_NAME "_GameMutex");
    if (GetLastError() == ERROR_ALREADY_EXISTS) result = true;
  }
  return result;
}


/* GetRegKeyValue */
LSTATUS get_reg_key_value(u8* buffer_data, HKEY hkey, u8* reg_key, u8* Key)
{
  DWORD buffer_size = 8192;
  LSTATUS status = RegGetValueA(hkey, reg_key, Key, RRF_RT_REG_SZ, NULL, (PVOID)&buffer_data[0], &buffer_size);
  
  /* Fail = system error code, Success = ERROR_SUCCESS */
  if (status != ERROR_SUCCESS)
  {
    MessageBoxA(NULL, "Failed to get Registry Key Value!", "Error!", MB_ICONEXCLAMATION | MB_OK);
  }
  
  return status;
}


/* MainWindowProcedures */
LRESULT CALLBACK main_window_procedures(HWND window_handle, UINT message, WPARAM wparam, LPARAM lparam)
{
  LRESULT result = 0;
  
  switch (message)
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
      g_window_data.is_running = false;
      break;
    }
    
    case WM_DESTROY:
    {
      ReleaseDC(g_window_data.window, g_window_data.device_context);
      wglDeleteContext(g_window_data.resource_gl);
      break;
    }
    
    default:
    {
      result = DefWindowProcA(window_handle, message, wparam, lparam);
    }
  }
  
  return result;
}


/* GetDeviceContext */
HDC get_device_context(void)
{
  return g_window_data.device_context;
}


///////////////////////////
// EOF
///////////////////////////
