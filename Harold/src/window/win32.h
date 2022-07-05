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

// Global Variables
MainArgs gMainArgs;

// Declaration
HAROLD_API void WindowSetViewport(i32 width, i32 height);
HAROLD_API i32 WindowGetViewportWidth();
HAROLD_API i32 WindowGetViewportHeight();

// OpenGL
HAROLD_API void WindowSetVersionGL(i32 major, i32 minor);
HAROLD_API i32 WindowGetVersionGLMajor();
HAROLD_API i32 WindowGetVersionGLMinor();

HAROLD_API Window WindowCreateGL(string title, i32 width, i32 height, bool fullscreen);

HAROLD_API string WindowGetVendorGL();
HAROLD_API string WindowGetRenderGL();
HAROLD_API string WindowGetVersionGL();

// Internal
void WindowSetData();
int CreateMainWindow(void);
void c_glGetString();
int CreateWindowGlContext(void);
LRESULT CALLBACK MainWindowProcedures(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam);

#endif // WIN32_H


//// Declaration
//DWORD GameIsAlreadyRunning(void);
//
//LSTATUS GetRegKeyValue(char*, HKEY, char*, char*);
//
//void SetDPIAware(void);
//
//void ProcessPlayerInput(void);
//
//void RenderFrameGraphics(void);

///////////////////////////
// EOF
///////////////////////////
