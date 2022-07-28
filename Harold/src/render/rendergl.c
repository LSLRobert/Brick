////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 5, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "rendergl_int.h"


// LS_RenderFrameGraphics
LS_HAROLD_API void ls_render_frame_graphics(void)
{
  glClearColor(0.8f, 0.4f, 0.1f, 1.0f);
  
  glClear(GL_COLOR_BUFFER_BIT);
  
  SwapBuffers(get_device_context());
}


///////////////////////////
// EOF
///////////////////////////
