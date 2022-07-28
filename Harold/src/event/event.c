////////////////////////////////////////////////////////////
//
// Last Straw Labs, Inc.
// www.laststrawlabs.com
// July 5, 2022
//
////////////////////////////////////////////////////////////
#include "header.h"
#include "event_int.h"


/* PollEvent */
LS_HAROLD_API bool ls_poll_event(ls_event *event)
{
  /* loop */
  MSG msg = { 0 };
  
  while (PeekMessageA(&msg, g_window_data.window, 0, 0, PM_REMOVE))
  {
    switch (msg.message)
    {
      // TODO::TODO::TODO::TODO::TODO::TODO::TODO::TODO::TODO::
      /* setup - Key, Mouse, Controller ... EVENTS
      */
      case WM_KEYDOWN: // TEMP shutdown with Escape Key
        if (msg.wParam == VK_ESCAPE) g_window_data.is_running = false;
        break;
      
      case WM_CLOSE:
        /* the CLOSE should never come through this queue */
        puts("WM_CLOSE - PeekMessage\n");
        break;
      
      case WM_QUIT:
        /* this is inconsistent don't use it */
        puts("WM_QUIT  - PeekMessage\n");
        break;
      
      default:
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
        break;
    }
  }
  
  return false;
}

//    puts("MSG Message\n");
//    printf("Message.hwnd    : %d\n", msg.hwnd);     // HWND
//    printf("Message.message : %d\n", msg.message);  // UINT
//    printf("Message.wParam  : %d\n", msg.wParam);   // WPARAM
//    printf("Message.lParam  : %d\n", msg.lParam);   // LPARAM
//    printf("Message.time    : %d\n", msg.time);     // DWORD
//    printf("Message.pt:   %d, %d\n", msg.pt.x, Message.pt.y); // POINT
//    printf("Message.lPrivate: %d\n", msg.lPrivate); // DWORD
//    puts("\n");


///////////////////////////
// EOF
///////////////////////////
