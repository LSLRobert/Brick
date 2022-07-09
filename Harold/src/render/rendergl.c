////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 5, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "rendergl.h"


LS_HAROLD_API void LS_RenderFrameGraphics(void)
{
  glClearColor(0.8f, 0.4f, 0.1f, 1.0f);
  
  glClear(GL_COLOR_BUFFER_BIT);
  
  SwapBuffers(GetDeviceContext());
}


///////////////////////////
// EOF
///////////////////////////
