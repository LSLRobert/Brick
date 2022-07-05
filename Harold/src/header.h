////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 1, 2022
//
////////////////////////////////////////////////////////////
#ifndef HEADER_H
#define HEADER_H

#define HAROLD_BUILD
#include <harold.h>

#ifdef PLATFORM_WINDOWS
  
  #pragma warning(push, 3)
  #define WINDOWS_LEAN_AND_MEAN
  #include <windows.h>
  //#include <shellscalingapi.h>
  #include "../res/resource.h"
  #pragma warning(pop)
  
  // GL Version 4.5
  #include "glad/glad.h"
  
  #include "main.h"
  #include "window/win32.h"
  
#else // PLATFORM_WINDOWS
  
  // TODO: add other OS's
  // Apple
  // Linux
  // Mobile
  // Web
  
#endif // PLATFORM_WINDOWS

#endif // HEADER_H

///////////////////////////
// EOF
///////////////////////////
