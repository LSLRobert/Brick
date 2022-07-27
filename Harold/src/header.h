////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 1, 2022
//
////////////////////////////////////////////////////////////
#ifndef LS_HEADER_H
#define LS_HEADER_H

#define LS_HAROLD_BUILD
#include <harold.h>

#ifdef LS_PLATFORM_WINDOWS
  
  #pragma warning(push, 3)
  #define WINDOWS_LEAN_AND_MEAN
  #include <windows.h>
  //#include <shellscalingapi.h>
  #include "../res/resource.h"
  #pragma warning(pop)
  
  // GL Version 4.5
  #include "glad/glad.h"
  
  #include "main.h"
  #include "window/win32_int.h"
  #include "memory/memory32_int.h"
  #include "event/event32_int.h"
  
#else // OTHER_PLATFORMS
  
  // TODO: add other OS's
  // Apple
  // Linux
  // Mobile
  // Web
  
#endif // LS_PLATFORM_WINDOWS

// NON_PLATFORM
#include "array/array_int.h"
#include "render/rendergl_int.h"

#endif // LS_HEADER_H

///////////////////////////
// EOF
///////////////////////////
