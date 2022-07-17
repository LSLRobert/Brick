////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 4, 2022
//
////////////////////////////////////////////////////////////
#ifndef LS_WIN32_H
#define LS_WIN32_H

// fields
typedef void* LS_Window;

LS_HAROLD_API void      LS_WindowSetViewport(i32 width, i32 height);
LS_HAROLD_API i32       LS_WindowGetViewportWidth();
LS_HAROLD_API i32       LS_WindowGetViewportHeight();

LS_HAROLD_API LS_Window LS_WindowCreateGL(LS_String title, i32 width, i32 height, bool fullscreen);

LS_HAROLD_API void      LS_WindowSetVersionGL(i32 major, i32 minor);
LS_HAROLD_API i32       LS_WindowGetVersionGLMajor();
LS_HAROLD_API i32       LS_WindowGetVersionGLMinor();

LS_HAROLD_API LS_String LS_WindowGetVendorGL();
LS_HAROLD_API LS_String LS_WindowGetRenderGL();
LS_HAROLD_API LS_String LS_WindowGetVersionGL();

LS_HAROLD_API bool      LS_IsApplicationRunning();
LS_HAROLD_API void      LS_SetApplicationRunning(bool running);
LS_HAROLD_API void      LS_LogCurrentWindowVersion(void);

#endif // LS_WIN32_H

///////////////////////////
// EOF
///////////////////////////
