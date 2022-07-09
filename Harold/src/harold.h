////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 1, 2022
//
// include "harold.h"
////////////////////////////////////////////////////////////
#ifndef LS_HAROLD_H
#define LS_HAROLD_H

// defines
#define false   0
#define true    1

// c includes
#include <stdio.h>
#include <stdint.h>

// c types
typedef uint32_t  u32;
typedef int32_t   i32;
typedef uint16_t  u16;
typedef int16_t   i16;
typedef uint8_t   u8;
typedef int8_t    i8;
typedef double    f64;
typedef float     f32;
typedef int32_t   bool;
typedef uint8_t*  LS_String;
typedef uint64_t  u64;
typedef int64_t   i64;

// current platform
#define LS_PLATFORM_WINDOWS

#ifdef LS_PLATFORM_WINDOWS
  #ifdef LS_HAROLD_BUILD
    #define LS_HAROLD_API __declspec( dllexport )
  #else
    #define LS_HAROLD_API __declspec( dllimport )
  #endif
#else
  #error LS Harold currently only support Windows!
  // #elseif future platforms
#endif


// fields
typedef void* LS_Window;

typedef struct LS_Event
{
  i32 type;
  
} LS_Event;

///////////////////////////
// Window - win32.h
///////////////////////////
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

///////////////////////////
// Event - event32.h
///////////////////////////
LS_HAROLD_API bool      LS_PollEvent(LS_Event* event);


///////////////////////////
// Render - rendergl.h
///////////////////////////
LS_HAROLD_API void      LS_RenderFrameGraphics(void);


#endif // LS_HAROLD_H

///////////////////////////
// EOF
///////////////////////////
