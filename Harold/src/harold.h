////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 1, 2022
//
// include "harold.h"
////////////////////////////////////////////////////////////
#ifndef HAROLD_H
#define HAROLD_H

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
typedef uint8_t*  string;
typedef uint64_t  u64;
typedef int64_t   i64;

// current platform
#define PLATFORM_WINDOWS

#ifdef PLATFORM_WINDOWS
  #ifdef HAROLD_BUILD
    #define HAROLD_API __declspec( dllexport )
  #else
    #define HAROLD_API __declspec( dllimport )
  #endif
#else
  #error Harold currently only support Windows!
  // #elseif future platforms
#endif


// fields
typedef void* Window;

typedef struct Event
{
  i32 type;
  
} Event;

///////////////////////////
// Window - win32.h
///////////////////////////
HAROLD_API void   WindowSetViewport(i32 width, i32 height);
HAROLD_API i32    WindowGetViewportWidth();
HAROLD_API i32    WindowGetViewportHeight();

HAROLD_API Window WindowCreateGL(string title, i32 width, i32 height, bool fullscreen);

HAROLD_API void   WindowSetVersionGL(i32 major, i32 minor);
HAROLD_API i32    WindowGetVersionGLMajor();
HAROLD_API i32    WindowGetVersionGLMinor();

HAROLD_API string WindowGetVendorGL();
HAROLD_API string WindowGetRenderGL();
HAROLD_API string WindowGetVersionGL();

HAROLD_API bool IsApplicationRunning();
HAROLD_API void SetApplicationRunning(bool running);
HAROLD_API void LogCurrentWindowVersion(void);

///////////////////////////
// Event - event32.h
///////////////////////////
HAROLD_API bool PollEvent(Event* event);


///////////////////////////
// Render - rendergl.h
///////////////////////////
HAROLD_API void RenderFrameGraphics(void);


#endif // HAROLD_H

///////////////////////////
// EOF
///////////////////////////
